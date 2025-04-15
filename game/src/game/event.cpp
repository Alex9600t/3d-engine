#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>
#include "event.h"
#include "game.hpp"
#include "render.h"
#include "renderEvent.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "scene/material.h"
#include "scene/scene.h"
#include "../engine/GameImgui.h"
#include "../engine/lua/luaVar.h"
// #include "../engine/lua/GameLua.h"
#include <GL/glut.h>
#include "../shaders/vertex.h"
#include <math.h>

sf::RenderWindow renderWindow;

// std::vector<float> Game::fpsGraVal(100, 0.0f); 
std::vector<float> Game::fpsGraVal(100, 0.0f);
static int offset = 0;
Event::UseMouse Event::UseMouse::cubeMouse;
std::optional <float> MouseX, MouseY;

void Event::startEventKeyboard(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            window.setSize({ resized->size.x , resized->size.y });
            glViewport(0, 0, resized->size.x, resized->size.y);
        }else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                Game::inGame = false;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::F2) {
                RenderEvent::screenShot(Game::w, Game::h, "sre");
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::W) {
                if (!Game::isMainMenu) {
                    Render::Camera::camera.angle = -Render::Camera::camera.mx / 180 * M_PI;
                    Render::Camera::camera.speed = 0.1f;
                }
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::A) {
                if (!Game::isMainMenu) {
                    Render::Camera::camera.angle = -Render::Camera::camera.mx / 180 * M_PI;
                    Render::Camera::camera.speed = 0.1f;
                    Render::Camera::camera.angle -= M_PI * 0.5f;
                }
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::S) {
                if (!Game::isMainMenu) {
                    Render::Camera::camera.angle = -Render::Camera::camera.mx / 180 * M_PI;
                    Render::Camera::camera.speed = -0.1f;
                }
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::D) {
                if (!Game::isMainMenu) {
                    Render::Camera::camera.angle = -Render::Camera::camera.mx / 180 * M_PI;
                    Render::Camera::camera.speed = 0.1f;
                    Render::Camera::camera.angle += M_PI * 0.5f;
                }
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::T) {
                // Render::angle += 5.0f;
                RenderEvent::isMouseActive = !RenderEvent::isMouseActive;
                std::thread(LuaVar::loadScript, "a").detach();
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Q) {
                Render::Camera::camera.pos.y--;
            }
            else if (keyPressed->scancode == sf::Keyboard::Scancode::Space) {
                RenderEvent::cameraIsJump();
            } else if (keyPressed->scancode == sf::Keyboard::Scancode::Y) {
                LuaVar::callHook("onBlockPlaced", {1, 3, 3});
            }
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyReleased>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::W || keyPressed->scancode == sf::Keyboard::Scancode::A || keyPressed->scancode == sf::Keyboard::Scancode::S || keyPressed->scancode == sf::Keyboard::Scancode::D) {
                Render::Camera::camera.angle = -Render::Camera::camera.mx / 180 * M_PI;
                Render::Camera::camera.speed = 0.0f;
            }
        }
        else if (const auto* mouse = event->getIf<sf::Event::MouseMoved>()) {
            if (!MouseX.has_value() && !MouseY.has_value()) {
                MouseX = mouse->position.x;
                MouseY = mouse->position.y;
            }
            // int mouseX = mouse->position.x - Game::w / 2;
            // Render::Camera::camera.mx += mouseX;
            if (!Game::isMainMenu && RenderEvent::isMouseActive) {
                if (mouse->position.x > MouseX.value()) {
                    Render::Camera::camera.mx -= 1.0f;
                    MouseX = mouse->position.x;
                }
                else if (mouse->position.x < MouseX.value()) {
                    Render::Camera::camera.mx += 1.0f;
                    MouseX = mouse->position.x;
                }
                if (mouse->position.y > MouseY.value()) {
                    Render::Camera::camera.my = ++Render::Camera::camera.my > 0 ? 0 : Render::Camera::camera.my;
                    MouseY = mouse->position.y;
                }
                else if (mouse->position.y < MouseY.value()) {
                    Render::Camera::camera.my = --Render::Camera::camera.my < -180 ? -180 : Render::Camera::camera.my;
                    MouseY = mouse->position.y;
                }
            }

            // if (mouse->position.y > Event::UseMouse::cubeMouse.y){
            //     Event::UseMouse::cubeMouse.yy += 0.5f;
            // } else if (mouse->position.y < Event::UseMouse::cubeMouse.y){
            //     Event::UseMouse::cubeMouse.yy -= 0.5f;
            // }
            // Event::UseMouse::cubeMouse.x = mouse->position.x;
            // Event::UseMouse::cubeMouse.y = mouse->position.y;

        } else if (const auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                LuaVar::callHook("onBlockPlaced", {0, 3, 3});
            } else if (mouseBtn->button == sf::Mouse::Button::Right) {
                LuaVar::callHook("onBlockDestroy", {0, 3, 3});
            }
        }
    }
}

void Event::simpleEvent(sf::RenderWindow& window) {
    while (const std::optional event = window.pollEvent()) {
        ImGui::SFML::ProcessEvent(window, *event);
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
            window.setSize({ resized->size.x , resized->size.y });
            glViewport(0, 0, resized->size.x, resized->size.y);
        }
    }
}

void Event::calculateFPS(sf::RenderWindow& window) {
    Game::frameCount++;
    if (Game::clock.getElapsedTime().asSeconds() >= 1.0f)
    {
        Game::FPS = Game::frameCount / Game::clock.getElapsedTime().asSeconds();
        std::ostringstream name2fps;
        name2fps << Game::FPS;
        std::string name(name2fps.str());
        // std::cout << "FPS: " << name << std::endl;
        window.setTitle("FPS: " + name);
        Game::clock.restart();
        Game::frameCount = 0;
        Game::fpsGraVal[offset] = Game::FPS;
        offset = (offset + 1) % Game::fpsGraVal.size();
        if (!Game::FPS_low.has_value() && !Game::FPS_max.has_value()) {
            Game::FPS_low = Game::FPS;
            Game::FPS_max = Game::FPS;
        }
        if (Game::FPS_low.has_value() && Game::FPS_low.value() >= Game::FPS) {
            Game::FPS_low = Game::FPS;
        }
        else if (Game::FPS_max.has_value() && Game::FPS_max.value() <= Game::FPS) {
            Game::FPS_max = Game::FPS;
        }
    }
}


void Event::trigger0(sf::RenderWindow& window) {
    Render::OpenGLCamera::camera.aspect = (float)window.getSize().x / (float)window.getSize().y;
    Material::triangle0.setPosition({ 100, 100 });
    Material::triangle1.setPosition({ 100, 100 });
}

void Event::iterVoid1(sf::RenderWindow& window) {
    if (Game::isGameClose) window.close();
}

