#include "Object.h"

Object::Object(std::string path) {
    loadObject(path);
}

void Object::draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, info.vertexIndices.size(), GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, info.vertexIndices.size());
}

void Object::loadObject(std::string &path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        std::cout << "Failed to open file: " << path << std::endl;
        return;
    }
    else {
        std::string s;
        while(std::getline(file, s)) {
            std::vector<std::string> tokens = split(s, " ");
            if(tokens[0] != "v" && tokens[0] != "vt" && tokens[0] != "vn" && tokens[0] != "f") continue;
            if(tokens[0] == "v") {
                float x, y, z;
                x = std::stof(tokens[1]);
                y = std::stof(tokens[2]);
                z = std::stof(tokens[3]);
                info.vertices.emplace_back(x, y, z);
            }
            else if(tokens[0] == "vt") {
                float x, y;
                x = std::stof(tokens[1]);
                y = std::stof(tokens[2]);
                info.textureCoord.emplace_back(x, y);
            }
            else if(tokens[0] == "vn") {
                float x, y, z;
                x = std::stof(tokens[1]);
                y = std::stof(tokens[2]);
                z = std::stof(tokens[3]);
                info.normal.emplace_back(x, y, z);
            }
            else if(tokens[0] == "f") {
                std::vector<std::string> v1 = split(tokens[1], "/");
                std::vector<std::string> v2 = split(tokens[2], "/");
                std::vector<std::string> v3 = split(tokens[3], "/");
                info.vertexIndices.emplace_back(std::stoi(v1[0]) - 1);
                info.vertexIndices.emplace_back(std::stoi(v2[0]) - 1);
                info.vertexIndices.emplace_back(std::stoi(v3[0]) - 1);
                info.textureIndices.emplace_back(std::stoi(v1[1]) - 1);
                info.textureIndices.emplace_back(std::stoi(v2[1]) - 1);
                info.textureIndices.emplace_back(std::stoi(v3[1]) - 1);
                info.normalIndices.emplace_back(std::stoi(v1[2]) - 1);
                info.normalIndices.emplace_back(std::stoi(v2[2]) - 1);
                info.normalIndices.emplace_back(std::stoi(v3[2]) - 1);
            }
        }
        file.close();

        info.vertexSize = info.vertices.size() * sizeof(glm::vec3);
        info.textureSize = info.textureCoord.size() * sizeof(glm::vec2);
        info.normalSize = info.normal.size() * sizeof(glm::vec3);
        info.vertIndicesSize = info.vertexIndices.size() * sizeof(unsigned int);
        info.texIndicesSize = info.textureIndices.size() * sizeof(unsigned int);
        info.normIndicesSize = info.normalIndices.size() * sizeof(unsigned int);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, info.vertexSize, info.vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.vertIndicesSize, info.vertexIndices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec3), (void*)info.vertexSize);
        // glEnableVertexAttribArray(2);
        // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec3), (void*)(info.vertexSize + info.textureSize));
    }
}

const std::vector<std::string> Object::split(const std::string &str, std::string pattern) {
    std::vector<std::string> res;
    if (pattern.empty()) return res;
    size_t start = 0, index = str.find_first_of(pattern, 0);
    while (index != str.npos) {
        if (start != index) res.push_back(str.substr(start, index - start));
        start = index + 1;
        index = str.find_first_of(pattern, start);
    }
    if (!str.substr(start).empty()) res.push_back(str.substr(start));
    return res;
}