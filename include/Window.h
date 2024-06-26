#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

class Window{
public:
    Window(unsigned int WIDTH = 800, unsigned int HEIGHT = 600, std::string title = "Window");
    ~Window();

    void setClearColor(float r, float g, float b, float a);
    void clear();
    void swapBuffers();
    bool shouldClose() const { return glfwWindowShouldClose(m_window); }
    void printInfo();
    unsigned int getWidth() { return m_width; }
    unsigned int getHeight() { return m_height; }
    bool isPressed(int key) const;
    GLFWwindow *getWindow() const { return m_window; }
private:
    GLFWwindow *m_window;
    unsigned int m_width, m_height;
    std::string m_title;
    float m_clearColor[4];
    std::vector<bool> keys;

    static void errorCallback(int error, const char* description);
    static void static_framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void static_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void keyboardCallback(int key, int action);
    void framebufferCallback(int width, int height);
    void Init();
};