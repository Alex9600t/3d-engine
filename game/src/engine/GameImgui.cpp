#include "GameImgui.h"
#include <stdexcept>
#include <SFML/Graphics.hpp>

void GameImgui::imguiInit(sf::RenderWindow& window){
    if (!ImGui::SFML::Init(window)) throw std::runtime_error("Ошибка инициализации ImGui");
}
sf::Clock deltaClock;
void GameImgui::imguistart(sf::RenderWindow& window){
    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::ShowDemoWindow();

    ImGui::Begin("Hello, world!");
    ImGui::Button("Look at this pretty button");
    ImGui::End();
}
void GameImgui::imguiRender(sf::RenderWindow& window){
    ImGui::SFML::Render(window);
}
void GameImgui::shutdown(){
    ImGui::SFML::Shutdown();
}