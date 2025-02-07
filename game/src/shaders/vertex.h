#pragma once
#ifndef VERTEX_H
#define VERTEX_H
namespace Vertex{
struct Vertex {
    public:
    float x, y, z;
    float R, G, B;
    Vertex(float x, float y, float z, float R, float G, float B): x(x), y(y), z(z), R(R), G(G), B(B) {};
};

class Triangle{
    public: 
        Triangle(Vertex v0, Vertex v1, Vertex v2);
        Vertex getVertex(int index) const;
    private:
        Vertex vertex0, vertex1, vertex2;
};

inline Triangle triangle0(Vertex(-0.5, -0.5, 0, 0.5, 0.5, 0.5), Vertex(0, 0.5, 0, 1, 1, 1), Vertex(0.5, -0.5, 0, 0, 0, 0));
}

#endif