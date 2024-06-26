#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

struct ObjectInfo{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoord;
    std::vector<glm::vec3> normal;
    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> textureIndices;
    std::vector<unsigned int> normalIndices;
    size_t vertexSize;
    size_t textureSize;
    size_t normalSize;
    size_t vertIndicesSize;
    size_t texIndicesSize;
    size_t normIndicesSize;
};

class Object{
public:
    Object(std::string path);
    GLuint vbo, ebo;
    struct ObjectInfo info;
    void draw() const;
private:
    void loadObject(std::string &path);
    const std::vector<std::string> split(const std::string &str, std::string pattern);
    GLuint vao;
};