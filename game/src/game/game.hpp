#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>

namespace Game {
    extern float FPS;
    extern std::optional<float> FPS_low;
    extern std::optional<float> FPS_max;
    extern sf::Clock clock;
    extern sf::Clock clockDelta;
    extern int frameCount;
    extern float deltaTime;
    extern std::vector<float> fpsGraVal;
}

#endif