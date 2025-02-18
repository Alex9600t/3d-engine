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
#include <glut/include/GL/glut.h>
#include <stdexcept>

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    sf::ContextSettings settings;
    settings.depthBits = 24;
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "lox", sf::State::Windowed, settings);
    try {GameImgui::imguiInit(window);} catch (const std::exception& e) {return -1;}
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
