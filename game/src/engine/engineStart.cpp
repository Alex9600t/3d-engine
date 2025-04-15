#define GLEW_STATIC
#include <glew/glew-2.2.0/include/GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>
#include <optional>
#include <iostream>
#include <sstream>
#include "multithreading.h"
#include "../game/game.hpp"
#include "../game/event.h"
#include "../game/render.h"
#include "../game/scene/scene.h"
#include "../game/scene/material.h"
#include "../game/Audio/audio.h"
#include "GameImgui.h"
#include "mainMenu.h"
#include <GL/glut.h>
#include <stdexcept>
#include <thread>

float Game::h, Game::w;

int main(int argc, char** argv) {
    // glewExperimental = GL_TRUE;
    // if (glewInit() != GLEW_OK) {
    //     std::cout << "Error" << std::endl;
    // }
    
    glutInit(&argc, argv);
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    // settings.antiAliasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "lox", sf::State::Windowed, settings);
    Game::w = window.getSize().x;
    Game::h = window.getSize().y;
    try {GameImgui::imguiInit(window);} catch (const std::exception& e) {return -1;}
    Scene::MaterialInit(window);
    Event::trigger0(window);
    Render::renderInit();


    // Audio::play("PSM_Test");

    // std::thread mathThread(Multithreading::math, std::ref(window));
    // std::thread eventsThread(Multithreading::event , std::ref(window));
    std::thread physicsThread(Multithreading::physics, std::ref(window));
    std::thread audioThread(Multithreading::audio, std::ref(window));
    // std::thread renderThread(Multithreading::render, std::ref(window));

    // std::this_thread::sleep_for(std::chrono::seconds(3));
    
    while (window.isOpen()){

        if (Game::inGame) {
            Event::startEventKeyboard(window);
            Render::update(window);
        } else {
            Event::simpleEvent(window);
        }
        
        GameImgui::imguistart(window);
        Event::calculateFPS(window);
        GameImgui::imguiRender(window);

        window.display();
        if (Game::isGameClose) {window.close();}
    }

    // mathThread.join();
    // eventsThread.join();
    audioThread.join();
    physicsThread.join();
    // renderThread.join();


    GameImgui::shutdown();
    return 0;
}
