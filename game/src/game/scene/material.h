#pragma once
#include <SFML/Graphics.hpp>

namespace Material {
    extern sf::ConvexShape triangle0;
    extern sf::ConvexShape triangle1;
    extern sf::ConvexShape triangle2;
    extern sf::ConvexShape triangle3;
    extern sf::ConvexShape triangletest;
    extern const sf::Font font;
    void vertexInit();
    extern sf::Text text;
    class vertexTriangle {
    public:
    float x, y, z, red, green, blue;
};

    extern float vert0x;
    extern float vert0y;
    extern float vert0z;
    extern float vert0R;
    extern float vert0G;
    extern float vert0B;
    extern float vert1x;
    extern float vert1y;
    extern float vert1z;
    extern float vert1R;
    extern float vert1G;
    extern float vert1B;
    // vertexTriangle vert0 (-0.5, -0.5, 0.0, 1.0, 0.0, 0.0);
    // vertexTriangle vert1;
    // vertexTriangle vert2;













    float getTexCoordByType(std::string type, int index);
}