#pragma once
#include <SFML/Graphics.hpp>
#include "game.hpp"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "physics.h"



namespace Render {
    struct OpenGLCamera{
    bool OpenGLCamIsUseDefaultSettings = true;
    float left = 1;
    float right = 1;
    float bottom = -0.5;
    float top = 0.5;
    float near_val = 0.1;
    float far_val = 100.0;
    float FOV = 90.0f;
    float aspect;

    static OpenGLCamera camera;

    float& getCameraData(int index){
        switch (index) {
            case 0: return left;
            case 1: return right;
            case 2: return bottom;
            case 3: return top;
            case 4: return near_val;
            case 5: return far_val;
            case 6: return FOV;
            default: throw std::out_of_range("Invalid camera parameter index");
        }
    }

    const float& getCameraData(int index) const {
        switch (index) {
            case 0: return left;
            case 1: return right;
            case 2: return bottom;
            case 3: return top;
            case 4: return near_val;
            case 5: return far_val;
            case 6: return FOV;
            default: throw std::out_of_range("Invalid camera parameter index");
        }
    }


    float& getGLUTCameraData(int index){
        switch (index){
            case 0: return aspect;
            case 1: return near_val;
            case 2: return far_val;
            default: throw std::out_of_range("Invalid camera parameter index");
        }
    }


    bool& getCameraDataBool(int index){
        switch (index){
            case 0: return OpenGLCamIsUseDefaultSettings;
            default: throw std::out_of_range("Invalid camera parameter index");
        }
    }

    const bool& getCameraDataBool(int index) const {
        switch (index){
            case 0: return OpenGLCamIsUseDefaultSettings;
            default: throw std::out_of_range("Invalid camera parameter index");
        }
    }
    };
    struct Camera {
        float mx = Game::w / 2;
        float my = Game::h / 2;
        sf::Vector3f pos = sf::Vector3f(0.0f, 0.0f, 0.0f);
        sf::Vector3f velocity = sf::Vector3f(0.0f, 5.0f, 0.0f);
        bool isJumping = false;
        bool isFlying = false;
        float speed = 0;
        float angle = -mx / 180 * M_PI;
        static Camera camera;
    };

    struct renderOptional {
        int selectedRenderType = 0;
        static renderOptional renderOpt;
    };

    extern float angle;

    void OpenGLCamSetDefaultSettings(sf::RenderWindow& window, int index);
    void OpenGLCamDefaultRenderSettings(sf::RenderWindow& window);
    void GLUTOpenGLCamSetDefaultSettings(sf::RenderWindow& window, int index);
    void GLUTOpenGLCamDefaultRenderSettings(sf::RenderWindow& window);
    // void updateCamera(double left, double right, double bottom, double top, double near_val, double far_val, int i /*0 - all, 1 - left, 2 - right, 3 - bottom, 4 - top, 5 - near_val, 6 - far_val*/);
    // void getCameraSettings(int i);

    void update(sf::RenderWindow& window);
    void renderInit();
    void drawCube(float x, float y, float z, bool rU, bool rD, bool rF, bool rB, bool rL, bool rR, float texU, float texD, float texF, float texB, float texL, float texR);
    void drawSkybox(float x, float y, float z, int id);
    void RenderMapFunc();



    struct BlockData {
        float x, y, z;
        // sf::Vector3f position;
        bool faces[6];
        float texCoords[6];
    };
    void renderMapUpdate();
    extern std::vector<BlockData> blockList;
    
    extern bool isUseVBO; 

    void rebuildBuffer();

    extern float tmpbool;
    extern GLuint vbo, vao;
    extern float renderVertices[];
    extern bool debugView;

    extern std::vector<sf::Vector3f> LUALines;
}