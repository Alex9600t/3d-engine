#pragma once
#include <SFML/Graphics.hpp>


namespace Event {
    void startEventKeyboard(sf::RenderWindow& window);
    void simpleEvent(sf::RenderWindow& window);
    void calculateFPS(sf::RenderWindow& window);
    void iterVoid1(sf::RenderWindow&);
    void eventClose();
    void trigger0(sf::RenderWindow& window);

    struct UseMouse{
        float x = 0.0f;
        float y = 0.0f;
        float xx = 0.0f;
        float yy = 0.0f;

        static UseMouse cubeMouse;
    };
}