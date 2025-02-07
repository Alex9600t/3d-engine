#include "GameImgui.h"
// #include "../game/scene/material.h"
#include "../game/scene/v.h"
// #include "../shaders/vertex.h"
#include "../game/game.hpp"
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <iostream>

static int offset = 0;
static std::vector<float> MsGraVal(100, 0.0f); 

void GameImgui::imguiInit(sf::RenderWindow& window){
    // Vertex::vert0 = {-0.5, -0.5, 0.0, 1.0, 0.0, 0.0};
    if (!ImGui::SFML::Init(window)) throw std::runtime_error("Ошибка инициализации ImGui");
    
}
sf::Clock deltaClock;
void GameImgui::imguistart(sf::RenderWindow& window){
    ImGui::SFML::Update(window, deltaClock.restart());

    GameImgui::showDebugMenu();
}
void GameImgui::imguiRender(sf::RenderWindow& window){
    ImGui::SFML::Render(window);
}
void GameImgui::shutdown(){
    ImGui::SFML::Shutdown();
}
void GameImgui::showDebugMenu(){
        std::ostringstream name2fps;
        name2fps << Game::FPS;
        std::string name("FPS: " + name2fps.str());
        const char * fps = name.c_str();


        std::ostringstream name2ms;
        name2ms << 1.f / Game::FPS * 1000.f;
        std::string ms("Ms: " + name2ms.str());
        const char * Ms = ms.c_str();

        MsGraVal[offset] = 1.f / Game::FPS * 1000.f; 
        offset = (offset + 1) % MsGraVal.size(); 



    ImGui::Begin("debug");

    ImGui::Text(fps);
    ImGui::PlotLines("FPS##GraVis", Game::fpsGraVal.data(), Game::fpsGraVal.size());

    ImGui::Text(Ms);
    ImGui::PlotLines("Ms##GraVis", MsGraVal.data(), MsGraVal.size());


    ImGui::Text("Background");
    ImGui::Text("Vertex 0");

    ImGui::SliderFloat("x##posvert0x", &Material::vert0x, -10.0f, 10.0f);
    ImGui::SliderFloat("y##posvert0y", &Material::vert0y, -10.0f, 10.0f);
    ImGui::SliderFloat("z##posvert0z", &Material::vert0z, -10.0f, 10.0f);

    static float colVert0[3] = {Material::vert0R, Material::vert0G, Material::vert0B};
    ImGui::ColorEdit3("Color##colvert0", colVert0);
    Material::vert0R = colVert0[0]; Material::vert0G = colVert0[1]; Material::vert0B = colVert0[2];

    ImGui::Text("Vertex 1");
    
    ImGui::SliderFloat("x##posvert1x", &Material::vert1x, -10.0f, 10.0f);
    ImGui::SliderFloat("y##posvert1y", &Material::vert1y, -10.0f, 10.0f);
    ImGui::SliderFloat("z##posvert1z", &Material::vert1z, -10.0f, 10.0f);

    static float colVert1[3] = {Material::vert1R, Material::vert1G, Material::vert1B};
    ImGui::ColorEdit3("Color##colvert1", colVert1);
    Material::vert1R = colVert1[0]; Material::vert1G = colVert1[1]; Material::vert1B = colVert1[2];

    ImGui::End();
}