#include <SFML/Graphics.hpp>
#include "render.h"
#include "scene/v.h"
#include "../shaders/vertex.h"
#include <glut/include/GL/glut.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <glut/include/GL/glut.h>

    // float Render::vert0y;
    // float Render::vert0z;
    // float Render::vert1x;
    // float Render::vert1y;
    // float Render::vert1z;
    // float Render::vert2x;
    // float Render::vert2y;
    // float Render::vert2z;
    Render::OpenGLCamera Render::OpenGLCamera::camera;

void Render::OpenGLCamSetDefaultSettings(sf::RenderWindow& window, int index){
    if (index == 0){
        Render::OpenGLCamera::camera.left = -((0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y);
    } else if (index == 1){
        Render::OpenGLCamera::camera.right = (0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y;
    } else if (index == 2){
        Render::OpenGLCamera::camera.bottom = 0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f);
    } else if (index == 3){
        Render::OpenGLCamera::camera.top = -(0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f));
    }
}

void Render::OpenGLCamDefaultRenderSettings(sf::RenderWindow& window){
    if (Render::OpenGLCamera::camera.getCameraDataBool(0)){
        glFrustum(-((0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y), ((0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y), -(0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)), (0.1f * tanf(Render::OpenGLCamera::camera.FOV * M_PI / 360.0f)), 0.1f, 100.0f);
    } else {
        glFrustum(Render::OpenGLCamera::camera.left, Render::OpenGLCamera::camera.right, Render::OpenGLCamera::camera.bottom, Render::OpenGLCamera::camera.top, Render::OpenGLCamera::camera.near_val, Render::OpenGLCamera::camera.far_val);
    }
}


void Render::update(sf::RenderWindow& window){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    // Render::OpenGLCamDefaultRenderSettings(window);


    gluPerspective(45.0f, (float) window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    
    Vertex::renderTriangle(Vertex::triangle0, 0);
    // Vertex::renderTriangle(Vertex::triangle1, true);
    // Vertex::renderTriangle(Vertex::triangle2, false);
    // Vertex::renderTriangle(Vertex::triangle3, false);
    glEnd();
}
