#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include <iostream>
#include <sstream>
#include "../game/game.hpp"
#include "../game/event.h"
#include "../game/render.h"
#include "../game/scene/scene.h"


int main(){
    sf::RenderWindow window(sf::VideoMode({720, 440}), "lox");
    scene::MaterialInit(window);
    Event::trigger0(window);
    while (window.isOpen()){

        Event::startEventKeyboard(window);
        Event::calculateFPS(window);
        Event::DebugMenuContent();
        
        Render::update(window);
    }
    return 0;
}
