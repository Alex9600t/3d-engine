#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>
#include "event.h"
#include "game.hpp"
#include <iostream>
#include "scene/material.h"
#include "scene/scene.h"

void Event::startEventKeyboard(sf::RenderWindow& window){
    while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    Material::fringe0.setPosition({Material::fringe0.getPosition().x + (5000000.0f * Game::deltaTime), Material::fringe0.getPosition().y});
                    Material::fringe1.setPosition({Material::fringe1.getPosition().x + (5000000.0f * Game::deltaTime), Material::fringe1.getPosition().y});
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    Material::fringe0.setPosition({Material::fringe0.getPosition().x - (5000000.0f * Game::deltaTime), Material::fringe0.getPosition().y});
                    Material::fringe1.setPosition({Material::fringe1.getPosition().x - (5000000.0f * Game::deltaTime), Material::fringe1.getPosition().y});
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::W) {
                    Material::fringe0.setPosition({Material::fringe0.getPosition().x , Material::fringe0.getPosition().y - (5000000.0f * Game::deltaTime)});
                    Material::fringe1.setPosition({Material::fringe1.getPosition().x , Material::fringe1.getPosition().y - (5000000.0f * Game::deltaTime)});
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    Material::fringe0.setPosition({Material::fringe0.getPosition().x , Material::fringe0.getPosition().y + (5000000.0f * Game::deltaTime)});
                    Material::fringe1.setPosition({Material::fringe1.getPosition().x , Material::fringe1.getPosition().y + (5000000.0f * Game::deltaTime)});

                } else if (keyPressed->scancode == sf::Keyboard::Scancode::T){
                    window.setSize({1920, 1080});
                }
            }
        }
}

void Event::calculateFPS(sf::RenderWindow& window){
        Game::frameCount++;
        if (Game::clock.getElapsedTime().asSeconds() >= 1.0f)
        {
            Game::FPS = Game::frameCount / Game::clock.getElapsedTime().asSeconds();
            std::ostringstream name2fps;
            name2fps << Game::FPS;
            std::string name(name2fps.str());
            std::cout << "FPS: " << name << std::endl;
            window.setTitle("FPS: " + name);
            Game::clock.restart();
            Game::frameCount = 0;
        }
}

    void Event::DebugMenuContent(){
        std::ostringstream name2fps;
            name2fps << Game::FPS;
            std::string name(name2fps.str());
        Material::text.setString("FPS: " + name + "\nPosX: " + std::to_string(Material::fringe0.getPosition().x) + "\nPosY: " + std::to_string(Material::fringe0.getPosition().y));
    }

void Event::trigger0(sf::RenderWindow& window){
    Material::fringe0.setPosition({100, 100});
    Material::fringe1.setPosition({100, 100});
}