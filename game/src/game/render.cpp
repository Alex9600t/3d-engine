#include <SFML/Graphics.hpp>
#include "render.h"
#include "scene/v.h"
#include "../shaders/vertex.h"
#include <SFML/OpenGL.hpp>
#include <iostream>
    // float Render::vert0y;
    // float Render::vert0z;
    // float Render::vert1x;
    // float Render::vert1y;
    // float Render::vert1z;
    // float Render::vert2x;
    // float Render::vert2y;
    // float Render::vert2z;


void Render::update(sf::RenderWindow& window){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(Material::vert0R, Material::vert0G, Material::vert0B);
    glVertex3f(Vertex::triangle0.getVertexData(0).x, Vertex::triangle0.getVertexData(0).y, Vertex::triangle0.getVertexData(0).z);
    // glVertex3f(Material::vert0x, Material::vert0y, Material::vert0z);
    glColor3f(Material::vert1R, Material::vert1G, Material::vert1B);
    glVertex3f(Vertex::triangle0.getVertexData(1).x, Vertex::triangle0.getVertexData(1).y, Vertex::triangle0.getVertexData(1).z);
    // glVertex3f(Material::vert1x, Material::vert1y, Material::vert1z);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(Vertex::triangle0.getVertexData(2).x, Vertex::triangle0.getVertexData(2).y, Vertex::triangle0.getVertexData(2).z);
    // glVertex3f(0.5, -0.5, 0.0);
    glEnd();
}