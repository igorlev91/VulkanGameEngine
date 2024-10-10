

#pragma once

#include <string>

#include "engine.h"

#define GLFW_INCLUDE_VULKAN
#include "glfw/include/GLFW/glfw3.h"

class Engine
{
public:


public:

    Engine(const std::string& configFilePath);
    ~Engine();

    bool Start();
    void OnUpdate();
    void OnRender();
    void Shutdown();
    void Quit();

    bool IsRunning() const { return m_Running; }
    std::string GetConfigFilePath() const { return m_ConfigFilePath; }

    static Engine* m_Engine;

private:
    static void SignalHandler(int signal);

private:
    
    std::string m_ConfigFilePath;
    GLFWwindow* m_Window;
    bool m_Running;

};
