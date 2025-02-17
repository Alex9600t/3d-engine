#include <SFML/Graphics.hpp>
#include "render.h"
#include "scene/v.h"
#include "../shaders/vertex.h"
#include <glut/include/GL/glut.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>



    // float Render::vert0y;
    // float Render::vert0z;
    // float Render::vert1x;
    // float Render::vert1y;
    // float Render::vert1z;
    // float Render::vert2x;
    // float Render::vert2y;
    // float Render::vert2z;
    Render::OpenGLCamera Render::OpenGLCamera::camera;
    Render::renderOptional Render::renderOptional::renderOpt;

// OpenGL

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


// GLUT

void Render::GLUTOpenGLCamSetDefaultSettings(sf::RenderWindow& window, int index){
    if (index == 0){
        Render::OpenGLCamera::camera.aspect = (float) window.getSize().x / (float) window.getSize().y;
    } else if (index == 1){
        Render::OpenGLCamera::camera.near_val = 0.1f;
    } else if (index == 2){
        Render::OpenGLCamera::camera.far_val = 100.0f;
    }
}

void Render::GLUTOpenGLCamDefaultRenderSettings(sf::RenderWindow& window){
    if (Render::OpenGLCamera::camera.getCameraDataBool(0)){
        gluPerspective(Render::OpenGLCamera::camera.FOV, (float) window.getSize().x / (float) window.getSize().y, 0.1f, 100.0f);
    } else {
        gluPerspective(Render::OpenGLCamera::camera.FOV, Render::OpenGLCamera::camera.aspect, Render::OpenGLCamera::camera.near_val, Render::OpenGLCamera::camera.far_val);
    }
}


void drawCube() {
    glBegin(GL_QUADS);

    // U
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // D
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // F
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // B
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    // L
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    // R
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);

    glEnd();
}


void Render::update(sf::RenderWindow& window){
    static float angle = 0.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Render::GLUTOpenGLCamDefaultRenderSettings(window);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    

    drawCube();
    Vertex::renderTriangle(Vertex::triangle0, 0);

    angle += 0.005f;
    
    // Vertex::renderTriangle(Vertex::triangle1, true);
    // Vertex::renderTriangle(Vertex::triangle2, false);
    // Vertex::renderTriangle(Vertex::triangle3, false);
    glEnd();
}
