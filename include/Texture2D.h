#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

class Texture2D{
public:
    Texture2D(const char* path);
    ~Texture2D();
    void bind() const;
    void unbind() const;
private:
    unsigned int m_ID;
    int m_width, m_height, m_nrChannels;
    unsigned char* m_data;
};