#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "Window.h"
#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include "Sammon.h"

class Application{
public:
    Application(Window *wnd_ptr);
    Application();
    ~Application();
    void run();
private:
    Window *m_window;
    Object *m_cube;
    Shader *m_shader, *m_som_shader;
    Camera *m_camera;
    void Init();
    void drawTest();
    void processCamera(float delta_time);
    void processInput();
};