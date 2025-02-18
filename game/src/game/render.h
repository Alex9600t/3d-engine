#pragma once
#include <SFML/Graphics.hpp>
#include <glut/include/GL/glut.h>



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
    // float vert0y;
    // float vert0z;
    // float vert1x;
    // float vert1y;
    // float vert1z;
    // float vert2x;
    // float vert2y;
    // float vert2z;
}