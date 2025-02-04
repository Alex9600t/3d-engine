#include <SFML/Graphics.hpp>
#include "scene.h"
#include "material.h"

namespace Material {
    sf::ConvexShape fringe0(100.f);
    sf::ConvexShape fringe1(100.f);
    const sf::Font font("arial.ttf");
    sf::Text text(font, "FPS: ", 10);
}
