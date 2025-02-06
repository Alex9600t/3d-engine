#include <SFML/Graphics.hpp>
#include "render.h"
#include "scene/material.h"
#include <SFML/OpenGL.hpp>

void Render::update(sf::RenderWindow& window){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, -0.5, 0.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0, 0.5, 0.0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5, -0.5, 0.0);
    glEnd();
}