#include <SFML/Graphics.hpp>
#include "scene.h"
#include "material.h"

namespace Material {
    sf::ConvexShape triangle0(100.f);
    sf::ConvexShape triangle1(100.f);
    sf::ConvexShape triangle2(100.f);
    sf::ConvexShape triangle3(100.f);
    sf::ConvexShape triangletest(100.f);
    const sf::Font font("arial.ttf");
    sf::Text text(font, "FPS: ", 10);
}
