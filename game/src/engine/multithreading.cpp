#include "multithreading.h"
#include "../game/game.hpp"
#include "../game/event.h"
#include "../game/Audio/audio.h"
#include "../game/render.h"
#include "../game/scene/scene.h"
#include "../game/scene/material.h"
#include "GameImgui.h"
#include <iostream>

void Multithreading::render(sf::RenderWindow &window) {
    while (window.isOpen()){
        Render::update(window);
        GameImgui::imguiRender(window);
        window.display();
    }
}
void Multithreading::physics(sf::RenderWindow &window) {
    while (window.isOpen()){
        if (Game::inGame) {
            
            Physics::physicsUpdate();
        }
    }
}
void Multithreading::math(sf::RenderWindow &window) {
    while (window.isOpen()){
        // Event::iterVoid1(window);
        Event::calculateFPS(window);

    }
}
void Multithreading::audio(sf::RenderWindow &window) {
    sf::Music music;
    if (!music.openFromFile("game/resources/music/PSM_Test.wav")){}

    music.setLooping(true);
    music.setVolume(Audio::volume);
    music.play();

    while (music.getStatus() == sf::SoundSource::Status::Playing && window.isOpen()) {
        music.setVolume(Audio::volume);
    }
}

void Multithreading::event(sf::RenderWindow &window) {
    // std::lock_guard<std::mutex> lock(Multithreading::renderMutex);
    while (window.isOpen()){
        // Event::startEventKeyboard(window);
        // GameImgui::imguistart(window);
        Event::calculateFPS(window);
        // std::cout << "Hello, world!";
    }
}
