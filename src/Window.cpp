#include "Window.h"

Window::Window(unsigned int WIDTH, unsigned int HEIGHT, std::string title)
    :   m_width(WIDTH), m_height(HEIGHT), m_title(title) {
    glfwSetErrorCallback(errorCallback);
    Init();
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Window::clear() {
    glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::printInfo() {
    std::cout << "-----------------------------------------------\n";
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Window size: " << m_width << "x" << m_height << "\n";
    std::cout << "-----------------------------------------------\n";
}

void Window::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

    //window checking
    if(m_window == nullptr) {
        std::cout << "Failed to create GLFW widow\n";
        return;
    }

    glfwMakeContextCurrent(m_window);

    //set callback
    glfwSetFramebufferSizeCallback(m_window, static_framebuffer_size_callback);
    glfwSetKeyCallback(m_window, static_keyboard_callback);
    //set user pointer
    glfwSetWindowUserPointer(m_window, this);

    //glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }
    keys = std::vector<bool>(GLFW_KEY_LAST + 1, false);
}

void Window::setClearColor(float r, float g, float b, float a) {
    m_clearColor[0] = r;
    m_clearColor[1] = g;
    m_clearColor[2] = b;
    m_clearColor[3] = a;
}

void Window::errorCallback(int error, const char* description) {
    std::cout << "GLFW Error: " << description << "\n";
}

void Window::static_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    Window *wnd = (Window*)glfwGetWindowUserPointer(window);
    if(wnd)
        wnd->framebufferCallback(width, height);
    else
        std::cout << "FramebufferCallback Casting Error\n";
}

void Window::static_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window *wnd = (Window*)glfwGetWindowUserPointer(window);
    if(wnd)
        wnd->keyboardCallback(key, action);
    else
        std::cout << "FramebufferCallback Casting Error\n";
}

void Window::keyboardCallback(int key, int action) {
    if(action == GLFW_PRESS) {
        keys[key] = true;
    }
    else if(action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

void Window::framebufferCallback(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
    // glViewport(0, 0, m_width/2, m_height/2);
    // glViewport(m_width/2, m_height/2, m_width/2, m_height/2);
    // glViewport(m_width/2, 0, m_width/2, m_height/2);
    // glViewport(0, m_height/2, m_width/2, m_height/2);
}

bool Window::isPressed(int key) const {
    return keys[key];
}