#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Sammon {
public:
    Sammon(std::string filename, int n, double e = 1e-6, double l = 0.9, double a = 0.3);
    Sammon &operator=(const Sammon &rhs);
    Sammon(const Sammon &rhs);
    ~Sammon();
    void draw();
    void readData(std::string filename);
    glm::vec2 midPos;
private:
    void calc_distance();
    void mapping();
    void initGL();
    std::vector<std::vector<double>> data;
    std::vector<std::vector<double>> old_distance;
    std::vector<std::pair<glm::vec2, int>> points; // position, index
    std::vector<float> vbo_data;
    double epsilon;
    double lambda;
    double alpha;
    int N;
    int dataNum;
    int dataDim;
    GLuint VAO, VBO;
};