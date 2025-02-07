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
#include "../game/scene/material.h"
#include "GameImgui.h"
#include <SFML/OpenGL.hpp>
#include <stdexcept>


int main(){
    sf::RenderWindow window(sf::VideoMode({720, 480}), "lox");
    try {GameImgui::imguiInit(window);} catch (const std::exception& e) {return -1;}
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    Scene::MaterialInit(window);
    Event::trigger0(window);

    while (window.isOpen()){

        
        Event::startEventKeyboard(window);
        GameImgui::imguistart(window);
        Event::calculateFPS(window);
        Event::DebugMenuContent();
        Render::update(window);
        GameImgui::imguiRender(window);


        window.display();

    }
    GameImgui::shutdown();
    return 0;
}
