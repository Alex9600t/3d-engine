#include "vertex.h"
#include <stdexcept>
#include <glut/include/GL/glut.h>
#include <SFML/Graphics.hpp>


namespace Vertex{
Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
    : vertex0(v0), vertex1(v1), vertex2(v2) {};

Vertex& Triangle::getVertexData(int index) {
    switch (index) {
        case 0: return vertex0;
        case 1: return vertex1;
        case 2: return vertex2;
        default: throw std::out_of_range("Invalid vertex index");
    }
}
const Vertex& Triangle::getVertexData(int index) const{
    switch (index) {
        case 0: return vertex0;
        case 1: return vertex1;
        case 2: return vertex2;
        default: throw std::out_of_range("Invalid vertex index");
    }
}

void renderTriangle(const Triangle& triangle, int drawDebug /*0 - No, 1 - debug color, 2 - lines */){
    glBegin(GL_TRIANGLES);
    if (drawDebug == 0){
        glColor4f(triangle.getVertexData(0).R, triangle.getVertexData(0).G, triangle.getVertexData(0).B, 0.5f);
        glVertex3f(triangle.getVertexData(0).x, triangle.getVertexData(0).y, triangle.getVertexData(0).z);
        glColor4f(triangle.getVertexData(1).R, triangle.getVertexData(1).G, triangle.getVertexData(1).B, 0.5f);
        glVertex3f(triangle.getVertexData(1).x, triangle.getVertexData(1).y, triangle.getVertexData(1).z);
        glColor4f(triangle.getVertexData(2).R, triangle.getVertexData(2).G, triangle.getVertexData(2).B, 0.5f);
        glVertex3f(triangle.getVertexData(2).x, triangle.getVertexData(2).y, triangle.getVertexData(2).z);
    } else if (drawDebug == 1){
        glColor3f(triangle.getVertexData(0).R, triangle.getVertexData(0).G, triangle.getVertexData(0).B);
        glVertex3f(triangle.getVertexData(0).x, triangle.getVertexData(0).y, triangle.getVertexData(0).z);
        glColor3f(triangle.getVertexData(1).R, triangle.getVertexData(1).G, triangle.getVertexData(1).B);
        glVertex3f(triangle.getVertexData(1).x, triangle.getVertexData(1).y, triangle.getVertexData(1).z);
        glColor3f(triangle.getVertexData(2).R, triangle.getVertexData(2).G, triangle.getVertexData(2).B);
        glVertex3f(triangle.getVertexData(2).x, triangle.getVertexData(2).y, triangle.getVertexData(2).z);
    } else if (drawDebug == 2){
        
    }
}
}
