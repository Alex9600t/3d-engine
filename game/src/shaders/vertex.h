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
        Vertex& getVertexData(int index);
        const Vertex& getVertexData(int index) const;
    private:
        Vertex vertex0, vertex1, vertex2;
};

void renderTriangle(const Triangle& triangle);

inline Triangle triangle0(Vertex(-0.5, -0.5, 0, 1.f, 0.f, 0.f), Vertex(-0.5, 0.5, 0, 0.f, 1, 0.f), Vertex(0.25, 0.5, 0, 0.f, 0.f, 1));
inline Triangle triangle1(Vertex(-0.5, -0.5, 0, 1.f, 0.f, 0.f), Vertex(0, 0.5, 0, 0.f, 1, 0.f), Vertex(0.5, -0.5, 0, 0.f, 0.f, 1));

}

#endif