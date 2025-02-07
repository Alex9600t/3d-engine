#include <SFML/Graphics.hpp>
#include "scene.h"
#include "material.h"
#include <iostream>

namespace Material {
    float vert0x = -0.5;
    float vert0y = -0.5;
    float vert0z = 0.0;
    float vert0R = 1;
    float vert0G = 0;
    float vert0B = 0;

    float vert1x = 0.;
    float vert1y = 0.5;
    float vert1z = 0.;
    float vert1R = 0;
    float vert1G = 1;
    float vert1B = 0;

    sf::ConvexShape triangle0(100.f);
    sf::ConvexShape triangle1(100.f);
    sf::ConvexShape triangle2(100.f);
    sf::ConvexShape triangle3(100.f);
    sf::ConvexShape triangletest(100.f);
    const sf::Font font("arial.ttf");
    sf::Text text(font, "FPS: ", 10);
    float hui;

// void Material::vertexInit(){
//     Material::vertexTriangle vert0;
//     vert0 = {-0.5, -0.5, 0.0, 1.0, 0.0, 0.0};
}