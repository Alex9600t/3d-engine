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
Event::UseMouse Event::UseMouse::cubeMouse;

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
                    // Render::angle += 5.0f;
                }
            } 
            else if (const auto *mouse = event->getIf<sf::Event::MouseMoved>()){
                if (mouse->position.x > Event::UseMouse::cubeMouse.x){
                    Event::UseMouse::cubeMouse.xx += 0.5f;
                } else if (mouse->position.x < Event::UseMouse::cubeMouse.x){
                    Event::UseMouse::cubeMouse.xx -= 0.5f;

                }
                if (mouse->position.y > Event::UseMouse::cubeMouse.y){
                    Event::UseMouse::cubeMouse.yy += 0.5f;
                } else if (mouse->position.y < Event::UseMouse::cubeMouse.y){
                    Event::UseMouse::cubeMouse.yy -= 0.5f;
                }
                Event::UseMouse::cubeMouse.x = mouse->position.x;
                Event::UseMouse::cubeMouse.y = mouse->position.y;

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
            if (!Game::FPS_low.has_value() && !Game::FPS_max.has_value()){
                Game::FPS_low = Game::FPS;
                Game::FPS_max = Game::FPS;
            }
            if (Game::FPS_low.has_value() && Game::FPS_low.value() >= Game::FPS){
                Game::FPS_low = Game::FPS;
            } else if (Game::FPS_max.has_value() && Game::FPS_max.value() <= Game::FPS){
                Game::FPS_max = Game::FPS;
            }
        }
}

    void Event::DebugMenuContent(){
        std::ostringstream name2fps;
            name2fps << Game::FPS;
            std::string name(name2fps.str());
        Material::text.setString("FPS: " + name + "\nPosX: " + std::to_string(Material::triangle0.getPosition().x) + "\nPosY: " + std::to_string(Material::triangle0.getPosition().y));
    }

void Event::trigger0(sf::RenderWindow& window){
    Render::OpenGLCamera::camera.aspect = (float) window.getSize().x / (float) window.getSize().y;
    Material::triangle0.setPosition({100, 100});
    Material::triangle1.setPosition({100, 100});
}