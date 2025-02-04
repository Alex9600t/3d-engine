#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

namespace Game {
    extern float FPS;
    extern sf::Clock clock;
    extern sf::Clock clockDelta;
    extern int frameCount;
    extern float deltaTime;
}

#endif