#include "vertex.h"
#include <stdexcept>

namespace Vertex{
Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
    : vertex0(v0), vertex1(v1), vertex2(v2) {};

Vertex Triangle::getVertex(int index) const {
    switch (index) {
        case 0: return vertex0;
        case 1: return vertex1;
        case 2: return vertex2;
        default: throw std::out_of_range("Invalid vertex index");
    }
}
}
