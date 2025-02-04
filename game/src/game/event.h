#pragma once
#include <SFML/Graphics.hpp>


namespace Event {
    void startEventKeyboard(sf::RenderWindow& window);
    void calculateFPS(sf::RenderWindow& window);
    void DebugMenuContent();
    void eventClose();
    void trigger0(sf::RenderWindow& window);
}