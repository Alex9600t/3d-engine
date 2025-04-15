#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "render.h"
#include "renderEvent.h"
#include "scene/v.h"
#include "game.hpp"
#include "event.h"
#include "mapSystem.h"
#include "../shaders/vertex.h"
#include <GL/glut.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include "../engine/lua/luaVar.h"

float Render::tmpbool = 0.05f;
std::vector<sf::Vector3f> Render::LUALines;
GLuint Render::vbo = 0, Render::vao = 0;
bool Render::debugView = false;
float Render::renderVertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f,
    -0.5f, -2.5f, 0.0f,
    0.5f, -2.5f, 0.0f,
    0.0f,  2.5f, 0.0f
};

float nullFloat3f[] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};

std::vector<Render::BlockData> Render::blockList;
bool Render::isUseVBO = false;

Render::OpenGLCamera Render::OpenGLCamera::camera;
Render::renderOptional Render::renderOptional::renderOpt;

float Render::angle = 0.0f;

// OpenGL

void Render::OpenGLCamSetDefaultSettings(sf::RenderWindow& window, int index) {
    if (index == 0) {
        Render::OpenGLCamera::camera.left = -((0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y);
    }
    else if (index == 1) {
        Render::OpenGLCamera::camera.right = (0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y;
    }
    else if (index == 2) {
        Render::OpenGLCamera::camera.bottom = 0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f);
    }
    else if (index == 3) {
        Render::OpenGLCamera::camera.top = -(0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f));
    }
}

void Render::OpenGLCamDefaultRenderSettings(sf::RenderWindow& window) {
    if (Render::OpenGLCamera::camera.getCameraDataBool(0)) {
        glFrustum(-((0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y), ((0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y), -(0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)), (0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)), 0.1f, 100.0f);
    }
    else {
        glFrustum(Render::OpenGLCamera::camera.left, Render::OpenGLCamera::camera.right, Render::OpenGLCamera::camera.bottom, Render::OpenGLCamera::camera.top, Render::OpenGLCamera::camera.near_val, Render::OpenGLCamera::camera.far_val);
    }
}


// GLUT

void Render::GLUTOpenGLCamSetDefaultSettings(sf::RenderWindow& window, int index) {
    if (index == 0) {
        Render::OpenGLCamera::camera.aspect = (float)window.getSize().x / (float)window.getSize().y;
    }
    else if (index == 1) {
        Render::OpenGLCamera::camera.near_val = 0.1f;
    }
    else if (index == 2) {
        Render::OpenGLCamera::camera.far_val = 100.0f;
    }
}

void Render::GLUTOpenGLCamDefaultRenderSettings(sf::RenderWindow& window) {
    if (Render::OpenGLCamera::camera.getCameraDataBool(0)) {
        gluPerspective(Render::OpenGLCamera::camera.FOV, (float)window.getSize().x / (float)window.getSize().y, 0.1f, 100.0f);
    }
    else {
        gluPerspective(Render::OpenGLCamera::camera.FOV, Render::OpenGLCamera::camera.aspect, Render::OpenGLCamera::camera.near_val, Render::OpenGLCamera::camera.far_val);
    }
}


void drawVBOCube(std::vector<float>& tmpRenderMap, float x, float y, float z, bool rU, bool rD, bool rF, bool rB, bool rL, bool rR) {
    if (rU) {
        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);


        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);
    }
    if (rD) {
        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);


        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);
    }
    if (rF) {
        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);


        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);
    }
    if (rB) {
        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);


        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);
    }
    if (rL) {
        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);


        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(-0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);
    }
    if (rR) {
        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);


        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(0.5f + z);

        tmpRenderMap.push_back(0.5f + x);
        tmpRenderMap.push_back(-0.5f + y);
        tmpRenderMap.push_back(-0.5f + z);
    }
}


void Render::renderMapUpdate() {
    Render::blockList.clear();

    if (!Map::getWorldJson().empty()) {
        const auto& worldJson = Map::getWorldJson();
        const auto& blocks = worldJson["id"];
        std::vector<float> tmpRenderMap;

        for (const auto& [id, block] : blocks.items()) {
            Render::BlockData cube;
            cube.x = block["x"].get<float>();
            cube.y = block["y"].get<float>();
            cube.z = block["z"].get<float>();
            std::string name = block["name"].get<std::string>();

            for (int i = 0; i < 6; i++) {
                cube.faces[i] = Map::duplicate(worldJson, std::stoi(id), i);
                cube.texCoords[i] = Material::getTexCoordByType(name, i);
            }

            drawVBOCube(tmpRenderMap, cube.x, cube.y, cube.z, cube.faces[0], cube.faces[1], cube.faces[2], cube.faces[3], cube.faces[4], cube.faces[5]);

            Render::blockList.push_back(cube);
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, tmpRenderMap.size() * sizeof(float), tmpRenderMap.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        std::cout << Render::blockList.size();
    }
    // if (!Map::MEMMap.empty()) {
    //     for (int id = 0; id < Map::MEMMap[0].chunk.id; id++) {
    //         Render::BlockData cube;
    //         cube.x = Map::MEMMap[0].chunk.
    //     }
    // }
}


sf::Texture texture;
sf::Shader shader;

void Render::renderInit() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Ошибка инициализации GLEW: " << glewGetErrorString(err) << std::endl;
        exit(1);
    }
    if (!glewIsSupported("GL_VERSION_3_3")) {
        std::cerr << "OpenGL 3.3 не поддерживается!" << std::endl;
        exit(1);
    }

    if (!texture.loadFromFile("game/resources/textures/texLib2.png")) {}
    if (!shader.isAvailable()) {}
    // sf::Texture::bind(&texture);

    // if (!shader.loadFromFile("shader.vert", "shader.frag")){}

    static float angle = 0.0f;

    Render::renderMapUpdate();

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 999999, nullptr, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void Render::drawCube(float x, float y, float z, bool rU, bool rD, bool rF, bool rB, bool rL, bool rR, float texU, float texD, float texF, float texB, float texL, float texR) {

    if (rU) {
        // U
        // glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
        glNormal3f(-0.5f + x, 0.5f + y + 3, -0.5f + z);
        glTexCoord2f(0.025f + texU, 0.025f);
        glVertex3f(-0.5f + x, 0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, 0.5f + y + 3, -0.5f + z);
        glTexCoord2f(0.05f + texU, 0.025f);
        glVertex3f(0.5f + x, 0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, 0.5f + y + 3, 0.5f + z);
        glTexCoord2f(0.05f + texU, 0.0f);
        glVertex3f(0.5f + x, 0.5f + y, 0.5f + z);
        glNormal3f(-0.5f + x, 0.5f + y + 3, 0.5f + z);
        glTexCoord2f(0.025f + texU, 0.0f);
        glVertex3f(-0.5f + x, 0.5f + y, 0.5f + z);
    }

    if (rD) {
        // D
        // glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
        glNormal3f(-0.5f + x, -0.5f + y - 3, -0.5f + z);
        glTexCoord2f(0.025f + texD, 0.025f);
        glVertex3f(-0.5f + x, -0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, -0.5f + y - 3, -0.5f + z);
        glTexCoord2f(0.05f + texD, 0.025f);
        glVertex3f(0.5f + x, -0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, -0.5f + y - 3, 0.5f + z);
        glTexCoord2f(0.05f + texD, 0.0f);
        glVertex3f(0.5f + x, -0.5f + y, 0.5f + z);
        glNormal3f(-0.5f + x, -0.5f + y - 3, 0.5f + z);
        glTexCoord2f(0.025f + texD, 0.0f);
        glVertex3f(-0.5f + x, -0.5f + y, 0.5f + z);
    }

    if (rF) {
        // F
        // glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
        glNormal3f(-0.5f + x, -0.5f + y, 0.5f + z + 3);
        glTexCoord2f(0.025f + texF, 0.025f);
        glVertex3f(-0.5f + x, -0.5f + y, 0.5f + z);
        glNormal3f(0.5f + x, -0.5f + y, 0.5f + z + 3);
        glTexCoord2f(0.05f + texF, 0.025f);
        glVertex3f(0.5f + x, -0.5f + y, 0.5f + z);
        glNormal3f(0.5f + x, 0.5f + y, 0.5f + z + 3);
        glTexCoord2f(0.05f + texF, 0.0f);
        glVertex3f(0.5f + x, 0.5f + y, 0.5f + z);
        glNormal3f(-0.5f + x, 0.5f + y, 0.5f + z + 3);
        glTexCoord2f(0.025f + texF, 0.0f);
        glVertex3f(-0.5f + x, 0.5f + y, 0.5f + z);
    }

    if (rB) {
        // B
        // glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
        glNormal3f(-0.5f + x, -0.5f + y, -0.5f + z - 3);
        glTexCoord2f(0.025f + texB, 0.025f);
        glVertex3f(-0.5f + x, -0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, -0.5f + y, -0.5f + z - 3);
        glTexCoord2f(0.05f + texB, 0.025f);
        glVertex3f(0.5f + x, -0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, 0.5f + y, -0.5f + z - 3);
        glTexCoord2f(0.05f + texB, 0.0f);
        glVertex3f(0.5f + x, 0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x, 0.5f + y, -0.5f + z - 3);
        glTexCoord2f(0.025f + texB, 0.0f);
        glVertex3f(-0.5f + x, 0.5f + y, -0.5f + z);
    }

    if (rL) {
        // L
        // glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
        glNormal3f(-0.5f + x - 3, -0.5f + y, -0.5f + z);
        glTexCoord2f(0.025f + texL, 0.025f);
        glVertex3f(-0.5f + x, -0.5f + y, -0.5f + z);
        glNormal3f(-0.5f + x - 3, -0.5f + y, 0.5f + z);
        glTexCoord2f(0.05f + texL, 0.025f);
        glVertex3f(-0.5f + x, -0.5f + y, 0.5f + z);
        glNormal3f(-0.5f + x - 3, 0.5f + y, 0.5f + z);
        glTexCoord2f(0.05f + texL, 0.0f);
        glVertex3f(-0.5f + x, 0.5f + y, 0.5f + z);
        glNormal3f(-0.5f + x - 3, 0.5f + y, -0.5f + z);
        glTexCoord2f(0.025f + texL, 0.0f);
        glVertex3f(-0.5f + x, 0.5f + y, -0.5f + z);
    }

    if (rR) {
        // R
        // glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
        glNormal3f(0.5f + x + 3, -0.5f + y, -0.5f + z);
        glTexCoord2f(0.025f + texR, 0.025f);
        glVertex3f(0.5f + x, -0.5f + y, -0.5f + z);
        glNormal3f(0.5f + x + 3, -0.5f + y, 0.5f + z);
        glTexCoord2f(0.05f + texR, 0.025f);
        glVertex3f(0.5f + x, -0.5f + y, 0.5f + z);
        glNormal3f(0.5f + x + 3, 0.5f + y, 0.5f + z);
        glTexCoord2f(0.05f + texR, 0.0f);
        glVertex3f(0.5f + x, 0.5f + y, 0.5f + z);
        glNormal3f(0.5f + x, 0.5f + y, -0.5f + z);
        glTexCoord2f(0.025f + texR, 0.0f);
        glVertex3f(0.5f + x, 0.5f + y, -0.5f + z);
    }
}
void Render::drawSkybox(float x, float y, float z, int id) {
    // U
    glTexCoord2f(0.0f, 0.575f);
    glVertex3f(-0.5f + x, 0.5f + y, -0.5f + z);
    glTexCoord2f(0.2f, 0.575f);
    glVertex3f(0.5f + x, 0.5f + y, -0.5f + z);
    glTexCoord2f(0.2f, 0.775f);
    glVertex3f(0.5f + x, 0.5f + y, 0.5f + z);
    glTexCoord2f(0.0f, 0.775f);
    glVertex3f(-0.5f + x, 0.5f + y, 0.5f + z);

    // F
    glTexCoord2f(0.6f, 0.775f);
    glVertex3f(-0.5f + x, -0.5f + y, -0.5f + z);
    glTexCoord2f(0.4f, 0.775f);
    glVertex3f(0.5f + x, -0.5f + y, -0.5f + z);
    glTexCoord2f(0.4f, 0.575f);
    glVertex3f(0.5f + x, 0.5f + y, -0.5f + z);
    glTexCoord2f(0.6f, 0.575f);
    glVertex3f(-0.5f + x, 0.5f + y, -0.5f + z);

    // B
    glTexCoord2f(0.0f, 0.975f);
    glVertex3f(-0.5f + x, -0.5f + y, 0.5f + z);
    glTexCoord2f(0.2f, 0.975f);
    glVertex3f(0.5f + x, -0.5f + y, 0.5f + z);
    glTexCoord2f(0.2f, 0.775f);
    glVertex3f(0.5f + x, 0.5f + y, 0.5f + z);
    glTexCoord2f(0.0f, 0.775f);
    glVertex3f(-0.5f + x, 0.5f + y, 0.5f + z);

    // L
    glTexCoord2f(0.2f, 0.975f);
    glVertex3f(-0.5f + x, -0.5f + y, -0.5f + z);
    glTexCoord2f(0.4f, 0.975f);
    glVertex3f(-0.5f + x, -0.5f + y, 0.5f + z);
    glTexCoord2f(0.4f, 0.775f);
    glVertex3f(-0.5f + x, 0.5f + y, 0.5f + z);
    glTexCoord2f(0.2f, 0.775f);
    glVertex3f(-0.5f + x, 0.5f + y, -0.5f + z);

    // R
    glTexCoord2f(0.4f, 0.775f);
    glVertex3f(0.5f + x, -0.5f + y, -0.5f + z);
    glTexCoord2f(0.2f, 0.775f);
    glVertex3f(0.5f + x, -0.5f + y, 0.5f + z);
    glTexCoord2f(0.2f, 0.575f);
    glVertex3f(0.5f + x, 0.5f + y, 0.5f + z);
    glTexCoord2f(0.4f, 0.575f);
    glVertex3f(0.5f + x, 0.5f + y, -0.5f + z);

    glTexCoord2f(0.4f, 0.975f);
    glVertex3f(-0.5f + x, -0.5f + y, -0.5f + z);
    glTexCoord2f(0.6f, 0.975f);
    glVertex3f(0.5f + x, -0.5f + y, -0.5f + z);
    glTexCoord2f(0.6f, 0.775f);
    glVertex3f(0.5f + x, -0.5f + y, 0.5f + z);
    glTexCoord2f(0.4f, 0.775f);
    glVertex3f(-0.5f + x, -0.5f + y, 0.5f + z);
}

sf::Shader vert;
void Render::update(sf::RenderWindow& window) {
    if (!shader.loadFromFile("shader.vert", "shader.frag")){}
    sf::Texture::bind(&texture);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (Render::debugView) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[] = { Render::Camera::camera.pos.x, 120.0f, -Render::Camera::camera.pos.z, 1.0f };
    // glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    sf::Shader::bind(&shader);
    Render::GLUTOpenGLCamDefaultRenderSettings(window);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glTranslatef(0.0f, 0.0f, 0.0f);
    RenderEvent::cameraMove();
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glPushMatrix();
    glRotatef(Render::angle, 1.0f, 0.0f, 0.0f);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glPopMatrix();

    glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    Render::drawSkybox(Render::Camera::camera.pos.x, Render::Camera::camera.pos.y, -Render::Camera::camera.pos.z, 0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();

    if (!isUseVBO) {
        glEnable(GL_DEPTH_TEST);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glBegin(GL_QUADS);
        for (const auto& cube : blockList) {
            Render::drawCube(cube.x, cube.y, cube.z,
                cube.faces[0], cube.faces[1], cube.faces[2],
                cube.faces[3], cube.faces[4], cube.faces[5],
                cube.texCoords[0], cube.texCoords[1], cube.texCoords[2],
                cube.texCoords[3], cube.texCoords[4], cube.texCoords[5]);
        }
        Render::drawSkybox(1, 1, 1, 0);
        glEnd();
    }
    else {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 5000);
        glBindVertexArray(0);
    }

    glPushMatrix();
    // if (!Render::LUALines.empty()) {
    //     glBegin(GL_LINES);
    //     for (int id = 0; id < Render::LUALines.size()/2; id++) {
    //         glColor3f(1, 0, 0);
    //         glVertex3f(Render::LUALines[2 * id].x, Render::LUALines[2 * id].y, Render::LUALines[2 * id].z);
    //         glVertex3f(Render::LUALines[2 * id + 1].x, Render::LUALines[2 * id + 1].y, Render::LUALines[2 * id + 1].z);
    //     };
    //     glColor3f(1, 1, 1);
    //     glEnd();
    // };
    if (!LuaVar::LUALine.empty()) {
        glBegin(GL_LINES);
        for (int id = 0; id < LuaVar::LUALine.size(); id++) {
            glColor3f(LuaVar::LUALine[id].r, LuaVar::LUALine[id].g, LuaVar::LUALine[id].b);
            glVertex3f(LuaVar::LUALine[id].x0, LuaVar::LUALine[id].y0, LuaVar::LUALine[id].z0);
            glVertex3f(LuaVar::LUALine[id].x1, LuaVar::LUALine[id].y1, LuaVar::LUALine[id].z1);
        }
        glColor3f(1, 1, 1);
        glEnd();
    }
    glPopMatrix();



    glPopMatrix();


    // Render::drawCube(0.0f, 2, 1.0f, true, 1 != 1, true, true, true, true, 0.20f, 0.20f, 0.20f, 0.20f, 0.20f, 0.20f);
    sf::Shader::bind(nullptr);
    Render::angle += 0.1;
}







//Уряяяя :3 
//Если ты прочитал этот код, то напиши мне в личку

