#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>


namespace Multithreading {
    // std::mutex renderMutex;
    void render(sf::RenderWindow &window);
    void physics(sf::RenderWindow &window);
    void math(sf::RenderWindow &window);
    void audio(sf::RenderWindow &window);
    void event(sf::RenderWindow &window);
}
