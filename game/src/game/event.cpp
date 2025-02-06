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
            } else if (event->is<sf::Event::Resized>()){
                window.setSize({window.getView().getSize().x, window.getView().getSize().y});
            // } else if(const auto *MouseMoved = event->getIf<sf::Event::MouseMoved>()){
            //     sf::Mouse::setPosition({10, 10}, window);
            //     // std::cout << "x: " << sf::Mouse::getPosition().x << " y: " << sf::Mouse::getPosition().x << "\n";


            //     if (sf::Mouse::getPosition().x && sf::Mouse::getPosition().x > 930){

            //     // std::cout << "x: " << sf::Mouse::getPosition().x << "\n";
            //        std::cout << "Мышка вправо \n"; 
            //     // sf::Mouse::setPosition({10, 10}, window);
            //     } else if (sf::Mouse::getPosition().x && sf::Mouse::getPosition().x < 930){
            //        std::cout << "Мышка влево \n"; 
            //     }
            }else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    window.close();
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::D) {
                    Material::triangle0.setPosition({Material::triangle0.getPosition().x + (5000000.0f * Game::deltaTime), Material::triangle0.getPosition().y});
                    Material::triangle1.setPosition({Material::triangle1.getPosition().x + (5000000.0f * Game::deltaTime), Material::triangle1.getPosition().y});
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::A) {
                    Material::triangle0.setPosition({Material::triangle0.getPosition().x - (5000000.0f * Game::deltaTime), Material::triangle0.getPosition().y});
                    Material::triangle1.setPosition({Material::triangle1.getPosition().x - (5000000.0f * Game::deltaTime), Material::triangle1.getPosition().y});
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::W) {
                    Material::triangle0.setPosition({Material::triangle0.getPosition().x , Material::triangle0.getPosition().y - (5000000.0f * Game::deltaTime)});
                    Material::triangle1.setPosition({Material::triangle1.getPosition().x , Material::triangle1.getPosition().y - (5000000.0f * Game::deltaTime)});
                } else if(keyPressed->scancode == sf::Keyboard::Scancode::S) {
                    Material::triangle0.setPosition({Material::triangle0.getPosition().x , Material::triangle0.getPosition().y + (5000000.0f * Game::deltaTime)});
                    Material::triangle1.setPosition({Material::triangle1.getPosition().x , Material::triangle1.getPosition().y + (5000000.0f * Game::deltaTime)});

                } else if (keyPressed->scancode == sf::Keyboard::Scancode::T){
                    Scene::setPossition(Material::triangle0, 0.f, 0.f, Material::triangle0.getScale().x + 0.1f);
                    Scene::setPossition(Material::triangle1, 0.f, 0.f, Material::triangle0.getScale().x + 0.1f);
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
        Material::text.setString("FPS: " + name + "\nPosX: " + std::to_string(Material::triangle0.getPosition().x) + "\nPosY: " + std::to_string(Material::triangle0.getPosition().y));
    }

void Event::trigger0(sf::RenderWindow& window){
    Material::triangle0.setPosition({100, 100});
    Material::triangle1.setPosition({100, 100});
}