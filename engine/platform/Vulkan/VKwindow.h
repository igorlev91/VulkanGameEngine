

#pragma once

#include "engine.h"
#include "window.h"
#include "VKdevice.h"
#include "VKpipeline.h"
#include "VKswapChain.h"
#include "VKmodel.h"

#define GLFW_INCLUDE_VULKAN
#include "glfw/include/GLFW/glfw3.h"

struct VK_SimplePushConstantData
{
    glm::vec2 m_Offset;
    alignas(16) glm::vec3 m_Color;
};

class VK_Window : public Window
{

public:

    VK_Window(const WindowProperties& props);
    ~VK_Window() override;

    VK_Window(const VK_Window&) = delete;
    VK_Window& operator=(const VK_Window&) = delete;

    //
    bool InitGLFW();
    void Shutdown();
    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
    VkExtent2D GetExtend() { return {static_cast<uint>(m_WindowProperties.m_Width), static_cast<uint>(m_WindowProperties.m_Height)}; }
    void* GetWindow() const override { return (void*)m_Window; }
    //std::shared_ptr<GraphicsContext> GetGraphicsContent() const override { return m_GraphicsContext; }
    void OnUpdate() override;    
    uint GetWidth()  const override { return m_WindowProperties.m_Width; }
    uint GetHeight() const override { return m_WindowProperties.m_Height; }
    //
    void SetEventCallback(const EventCallbackFunction& callback) override;
    //void SetVSync(int interval) override;
    void ToggleFullscreen() override;
    bool IsFullscreen() override { return m_IsFullscreen; }
    bool IsOK() const override { return m_OK; }
    void SetWindowAspectRatio() override;
    void SetWindowAspectRatio(int numer, int denom) override;
    float GetWindowAspectRatio() const override { return m_WindowProperties.m_Width / (1.0f * m_WindowProperties.m_Height); }
    double GetTime() const override { return glfwGetTime(); }

    static void OnError(int errorCode, const char* description);

    void EnableMousePointer() override;
    void DisableMousePointer() override;
    virtual void AllowCursor() override;
    virtual void DisallowCursor() override;

protected:

private:

    void DrawFrame();
    void CreateWindow();
    void CreatePipeline();
    void CreatePipelineLayout();
    void CreateCommandBuffers();
    void FreeCommandBuffers();
    void LoadModels();

    void RecreateSwapChain();
    void RecordCommandBuffer(int imageIndex);

    bool WasResized() const { return m_WindowProperties.m_FramebufferResized; }
    void ResetWindowResizedFlag() { m_WindowProperties.m_FramebufferResized = false; }

private:

    GLFWwindow* m_Window;

    struct WindowData
    {
        std::string m_Title;
        int m_Width;
        int m_Height;
        //int m_VSync;
        EventCallbackFunction m_EventCallback;
        //double m_MousePosX;
        //double m_MousePosY;
        bool m_FramebufferResized;
    };

    static bool m_GLFWIsInitialized;
    //
    bool m_OK;

    WindowData m_WindowProperties;
    std::shared_ptr<VK_Device> m_Device;
    std::unique_ptr<VK_Pipeline> m_Pipeline;
    std::unique_ptr<VK_SwapChain> m_SwapChain;
    std::shared_ptr<VK_Model> m_Model;
    VkPipelineLayout m_PipelineLayout;
    std::vector<VkCommandBuffer> m_CommandBuffers;

    uint m_RefreshRate;
    bool m_IsFullscreen;

    int m_WindowedWidth, m_WindowedHeight;
    int m_WindowPositionX, m_WindowPositionY;
    bool m_AllowCursor;

};
