#include "Sammon.h"

Sammon::Sammon(std::string filename, int n, double e, double l, double a)
    :dataNum(0), dataDim(0), N(n), epsilon(e), lambda(l), alpha(a){
    readData(filename);
}

Sammon::~Sammon() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

Sammon::Sammon(const Sammon &rhs) {
    data = rhs.data;
    old_distance = rhs.old_distance;
    points = rhs.points;
    vbo_data = rhs.vbo_data;
    epsilon = rhs.epsilon;
    lambda = rhs.lambda;
    alpha = rhs.alpha;
    N = rhs.N;
    dataNum = rhs.dataNum;
    dataDim = rhs.dataDim;
    VAO = rhs.VAO;
    VBO = rhs.VBO;
    mapping();
}

Sammon &Sammon::operator=(const Sammon &rhs) {
    if(this == &rhs) return *this;
    data = rhs.data;
    old_distance = rhs.old_distance;
    points = rhs.points;
    vbo_data = rhs.vbo_data;
    epsilon = rhs.epsilon;
    lambda = rhs.lambda;
    alpha = rhs.alpha;
    N = rhs.N;
    dataNum = rhs.dataNum;
    dataDim = rhs.dataDim;
    VAO = rhs.VAO;
    VBO = rhs.VBO;
    mapping();
    return *this;
}

void Sammon::readData(std::string filename) {
    std::string f = "assets\\" + filename;
    std::ifstream file(f);
    if(!file.is_open()) {
        std::cerr << "Error: file not found" << std::endl;
        return;
    }
    
    std::string firstLine;
    std::getline(file, firstLine);
    int end = firstLine.find_first_of(',');
    dataNum = std::stoi(firstLine.substr(0, end));
    int start = end + 1;
    end = firstLine.find_first_of(',', start);
    dataDim = std::stoi(firstLine.substr(start, end - start));
    
    assert(dataNum > 0 && dataDim > 0);
    data.resize(dataNum, std::vector<double>(dataDim, 0.0));
    
    std::string str;
    int idx = 0;
    while(std::getline(file, str)) {
        std::istringstream line(str);
        std::string token;
        int dimIdx = 0;
        while(std::getline(line, token, ',')) {
            data[idx][dimIdx] = std::stod(token);
            dimIdx += 1;
        }
        idx += 1;
    }
    file.close();
    calc_distance();
}

void Sammon::calc_distance() {
    old_distance.resize(dataNum, std::vector<double>(dataNum, 0.0));
    for(int i = 0; i < dataNum; i++) {
        for(int j = i + 1; j < dataNum; j++) {
            double dist = 0.0;
            for(int k = 0; k < dataDim - 1; k++) {
                dist += (data[i][k] - data[j][k]) * (data[i][k] - data[j][k]);
            }
            dist = std::sqrt(dist);
            old_distance[i][j] = dist;
            old_distance[j][i] = dist;
        }
    }
    mapping();
}

void Sammon::mapping() {
    std::unordered_set<int> chosen;

    // Initialize Q
    srand(time(NULL));
    for(int i = 0; i < N; ++i) {
        int idx = rand() % dataNum;
        while(chosen.find(idx) != chosen.end()) {
            idx = rand() % dataNum;
        }
        chosen.insert(idx);
        glm::vec2 pos(rand() % N, rand() % N);
        points.push_back(std::make_pair(pos, idx));
    }

    double total_dist = 0.0;
    double new_total_dist = 0.0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            total_dist += sqrt(points[i].first.x * points[j].first.x + points[i].first.y * points[j].first.y);
        }
    }

    while(abs(total_dist - new_total_dist) > epsilon) {
        total_dist = new_total_dist;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                if(i == j) continue;

                double dist = sqrt(
                    (points[i].first.x - points[j].first.x) * (points[i].first.x - points[j].first.x) +
                    (points[i].first.y - points[j].first.y) * (points[i].first.y - points[j].first.y)
                );

                if(dist < epsilon) dist = epsilon;

                double delta = lambda * (old_distance[points[i].second][points[j].second] - dist) / dist;
                glm::vec2 delta_ipos = glm::vec2(
                    delta * (points[i].first.x - points[j].first.x),
                    delta * (points[i].first.y - points[j].first.y)
                );
                glm::vec2 delta_jpos = -delta_ipos;

                points[i].first += delta_ipos;
                points[j].first += delta_jpos;
            }
        }

        new_total_dist = 0.0;
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                new_total_dist += sqrt(points[i].first.x * points[j].first.x + points[i].first.y * points[j].first.y);
            }
        }

        lambda *= alpha;
    }
    std::cout << "Mapping is done\n";
    initGL();
}

void Sammon::initGL() {

    glm::vec2 minPos(1e9, 1e9), maxPos(-1e9, -1e9);

    vbo_data.resize(points.size() * 3);
    for(int i = 0; i < N; ++i) {
        vbo_data[i * 3] = points[i].first.x;
        vbo_data[i * 3 + 1] = points[i].first.y;
        vbo_data[i * 3 + 2] = data[points[i].second][dataDim - 1];
        minPos.x = std::min(minPos.x, points[i].first.x);
        minPos.y = std::min(minPos.y, points[i].first.y);
        maxPos.x = std::max(maxPos.x, points[i].first.x);
        maxPos.y = std::max(maxPos.y, points[i].first.y);
    }

    midPos = (minPos + maxPos) / 2.0f;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vbo_data.size() * sizeof(float), vbo_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sammon::draw() {
    glPointSize(5.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, N);
    glBindVertexArray(0);
}