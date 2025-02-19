#include <SFML/Graphics.hpp>
#include "render.h"
#include "scene/v.h"
#include "event.h"
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

float Render::angle = 0.0f;

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

    sf::Texture texture;
void Render::renderInit(){
    if (!texture.loadFromFile("game/resources/textures/texLib.png")){
            
        }
    static float angle = 0.0f;
}

void drawCube() {
    glBegin(GL_QUADS);

    // U
    // glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glTexCoord2f(0.20f, 0.05f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.25f, 0.05f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.25f, 0.0f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.20f, 0.0f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // D
    // glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glTexCoord2f(0.10f, 0.05f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.15f, 0.05f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.15f, 0.0f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.10f, 0.0f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    // F
    // glColor4f(0.1f, 0.1f, 0.1f, 0.5f);
    glTexCoord2f(0.15f, 0.05f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.20f, 0.05f);
    glVertex3f( 0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.20f, 0.0f);
    glVertex3f( 0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.15f, 0.0f);
    glVertex3f(-0.5f,  0.5f,  0.5f);

    // B
    // glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glTexCoord2f(0.15f, 0.05f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.20f, 0.05f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.20f, 0.0f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glTexCoord2f(0.15f, 0.0f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    // L
    // glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
    glTexCoord2f(0.15f, 0.05f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.20f, 0.05f);
    glVertex3f(-0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.20f, 0.0f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.15f, 0.0f);
    glVertex3f(-0.5f,  0.5f, -0.5f);

    // R
    // glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glTexCoord2f(0.15f, 0.05f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.20f, 0.05f);
    glVertex3f(0.5f, -0.5f,  0.5f);
    glTexCoord2f(0.20f, 0.0f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glTexCoord2f(0.15f, 0.0f);
    glVertex3f(0.5f,  0.5f, -0.5f);
}



void Render::update(sf::RenderWindow& window){
    sf::Texture::bind(&texture);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    // glEnable(GL_CULL_FACE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    Render::GLUTOpenGLCamDefaultRenderSettings(window);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(Event::UseMouse::cubeMouse.xx, 0.0f, 1.0f, 0.0f);
    glRotatef(Event::UseMouse::cubeMouse.yy, 1.0f, 0.0f, 0.0f);
    drawCube();
    // Render::angle += 0.05f;

    if (Render::angle >= 360.0f){
        Render::angle = -360.0f;
    } else if (Render::angle <= -360.0f){
        Render::angle = 360.0f;
    }
    glEnd();
}
