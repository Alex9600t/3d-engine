#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>
#include "event.h"
#include "game.hpp"
#include "render.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "scene/material.h"
#include "scene/scene.h"
#include "../engine/GameImgui.h"
#include <glut/include/GL/glut.h>
#include "../shaders/vertex.h"

// std::vector<float> Game::fpsGraVal(100, 0.0f); 
extern std::vector<float> Game::fpsGraVal(100, 0.0f);
static int offset = 0;

void Event::startEventKeyboard(sf::RenderWindow& window){
    while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            } else if (const auto* resized = event->getIf<sf::Event::Resized>()){
                window.setSize({resized->size.x , resized->size.y});
                glViewport(0, 0, resized->size.x, resized->size.y);
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
                Game::fpsGraVal[offset] = Game::FPS; 
                offset = (offset + 1) % Game::fpsGraVal.size(); 
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