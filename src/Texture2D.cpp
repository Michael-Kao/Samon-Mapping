#include "Texture2D.h"

Texture2D::Texture2D(const char* path) {
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    //set the texture wrapping/filtering options (on the currently bound texture object)
    //set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(path, &m_width, &m_height, &m_nrChannels, 0);
    if(m_data){
        GLenum format;
        if(m_nrChannels == 1)
            format = GL_RED;
        else if(m_nrChannels == 3)
            format = GL_RGB;
        else if(m_nrChannels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(m_data);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &m_ID);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture2D::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}