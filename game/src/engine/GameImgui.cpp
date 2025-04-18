#include "GameImgui.h"
// #include "../game/scene/material.h"
#include "../game/scene/v.h"
#include "../shaders/vertex.h"
#include "../game/game.hpp"
#include "../game/render.h"
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "console.h"
#include "mainMenu.h"

static int offset = 0;
static std::vector<float> MsGraVal(100, 0.0f); 

const char* RenderTypesText[] = {"OpenGL(GLUT)", "OpenGL",  "Vulkan"};
const char* OpenGLCamText[] = {"left", "right", "bottom", "top", "near_val", "far_val"};
const char* GLUTOpenGLCamText[] = {"aspect", "zNear", "zFar"};
const char* GLUTOpenGLCamTextIsNewOptText[] = {"window.x / window.h", "Min distance from the camera to the object (Cannot be < 0)", "Max distance from the camera to the object (Cannot be < zNear)"};
bool OpenGLCamTextIsNewOptBool[] = {true, true, true, true, false, false};
const char* OpenGLCamTextIsNewOptText[] = {"-((0.1f * tan(FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y)", "(0.1f * tan(FOV * M_PI / 360.0f)) * (float)window.getSize().x / (float)window.getSize().y", "0.1f * tanf(FOV * M_PI / 360.0f)", "-(0.1f * tanf(FOV * M_PI / 360.0f))", "far_val"};

void GameImgui::imguiInit(sf::RenderWindow& window){
    if (!ImGui::SFML::Init(window)) throw std::runtime_error("Ошибка инициализации ImGui");
    
}
sf::Clock deltaClock;
void GameImgui::imguistart(sf::RenderWindow& window){
    ImGui::SFML::Update(window, deltaClock.restart());

    GameImgui::showDebugMenu(window);
    if (!Game::inGame) {

        MainMenu::renderMainMenu();
    }
    // if (GameImgui::isConsoleOpen){
        // GameImgui::showDebugConsole(window);
    // }
}
void GameImgui::imguiRender(sf::RenderWindow& window){
    ImGui::SFML::Render(window);
}
void GameImgui::shutdown(){
    ImGui::SFML::Shutdown();
}
void imSubTabColor(){
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.1f, 0.2f, 0.3f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.1f, 0.2f, 0.3f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.1f, 0.2f, 0.3f, 0.7f));
}
void imStyleRes(){
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
}
void imDis(bool b){
    if (b == 1){
        ImGui::BeginDisabled(true);
    }
}
void imDisRes(bool b){
    if (b == 1){
        ImGui::EndDisabled();
    }
}



Console::ClassConsole Console::gameConsole;
void GameImgui::showDebugMenu(sf::RenderWindow& window){
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

    if (ImGui::CollapsingHeader("Info")) {
    ImGui::Text(fps);
    ImGui::PlotLines("FPS##GraVis", Game::fpsGraVal.data(), Game::fpsGraVal.size());
    ImGui::Text(("FPS max: " + std::to_string(Game::FPS_max.value_or(0.0f))).c_str());
    ImGui::Text(("FPS low: " + std::to_string(Game::FPS_low.value_or(0.0f))).c_str());


    ImGui::Text(Ms);
    ImGui::PlotLines("Ms##GraVis", MsGraVal.data(), MsGraVal.size());

    ImGui::Text("Pos");
    imSubTabColor();
    if (ImGui::CollapsingHeader("Camera pos")){
        for (int i = 0; i < 6; i++){
            ImGui::Text((std::string(OpenGLCamText[i]) + ": " + std::to_string(Render::OpenGLCamera::camera.getCameraData(i))).c_str());
            // ImGui::SliderFloat(OpenGLCamText[i], &camera.getCameraData(i), -10.0f, 10.0f);
        }
    }   
    imStyleRes();
    }

    if (ImGui::CollapsingHeader("Camera")){
        if (ImGui::Button("Load test map")) {
            Map::loadMapFromFile("testmap");
            Render::renderMapUpdate();

            Render::Camera::camera.isFlying = true;
        }
        ImGui::SliderFloat("fd", &Render::tmpbool, 0.f, 10.0f);
        ImGui::Text(std::string("x: " + std::to_string(Render::Camera::camera.pos.x)).c_str());
        ImGui::Text(std::string("y: " + std::to_string(Render::Camera::camera.pos.y)).c_str());
        ImGui::Text(std::string("z: " + std::to_string(-Render::Camera::camera.pos.z)).c_str());
        ImGui::Separator();
        ImGui::Text(std::string("y velocity: " + std::to_string(Render::Camera::camera.velocity.y)).c_str());
        ImGui::Separator();
        ImGui::Checkbox("Fly", &Render::Camera::camera.isFlying);
        ImGui::Separator();
        ImGui::Text("FOV");
        ImGui::SliderFloat("Field of view", &Render::OpenGLCamera::camera.FOV, 45.0f, 180.0f);
        ImGui::Separator();
        bool lool = false;
        ImGui::Checkbox("DLSS (Delivers Lag, Stutters, and Smearing)", &lool);
        ImGui::Separator();
        ImGui::Checkbox("Use VBO", &Render::isUseVBO);
        ImGui::Separator();
        ImGui::Checkbox("Use default camera settings", &Render::OpenGLCamera::camera.getCameraDataBool(0));
        if (Render::renderOptional::renderOpt.selectedRenderType != 0){
        ImGui::Text("Debug: These are the settings for the older version of rendering. New version in development");
        ImGui::Text("Debug: Trying to change anything here will get you nowhere");
        }
        ImGui::Combo("Select Render utils", &Render::renderOptional::renderOpt.selectedRenderType, RenderTypesText, IM_ARRAYSIZE(RenderTypesText));
        ImGui::Separator();
        if (Render::renderOptional::renderOpt.selectedRenderType == 0){
            for (int i = 0; i < 3; i++){
                imDis(Render::OpenGLCamera::camera.getCameraDataBool(0));
                    if (ImGui::Button((std::string("Set default (") + std::string(GLUTOpenGLCamText[i]) + ")").c_str())){
                        Render::GLUTOpenGLCamSetDefaultSettings(window, i);
                    }
                    ImGui::Text(GLUTOpenGLCamTextIsNewOptText[i]);
                    ImGui::SliderFloat(GLUTOpenGLCamText[i], &Render::OpenGLCamera::camera.getGLUTCameraData(i), -10.0f, 200.0f);
                    ImGui::Separator();
                imDisRes(Render::OpenGLCamera::camera.getCameraDataBool(0));
            }
        } else if (Render::renderOptional::renderOpt.selectedRenderType == 1){
            ImGui::Text("WARNING: The selected render type is not supported by the engine/not made!\nI do not recommend to set this type of renderer");
            float temp[5]; 
            for (int i = 0; i < 6; i++){
                imDis(Render::OpenGLCamera::camera.getCameraDataBool(0));
                if (OpenGLCamTextIsNewOptBool[i]){
                    if (ImGui::Button((std::string("Set default (") + std::string(OpenGLCamText[i]) + ")").c_str())){
                        Render::OpenGLCamSetDefaultSettings(window, i);
                    }
                    ImGui::Text((std::string("'") + std::string(OpenGLCamText[i]) + "' ( " + std::string(OpenGLCamTextIsNewOptText[i]) + " )").c_str());
                }
                temp[i] = (Render::OpenGLCamera::camera.getCameraData(i));
                ImGui::SliderFloat(OpenGLCamText[i], &temp[i], -200.0f, 200.0f);
                Render::OpenGLCamera::camera.getCameraData(i) = temp[i];
                ImGui::Separator();
                    imDisRes(Render::OpenGLCamera::camera.getCameraDataBool(0));
            }
        } else if (Render::renderOptional::renderOpt.selectedRenderType == 2){
            ImGui::Text("WARNING: The selected render type is not supported by the engine/not made!\nI do not recommend to set this type of renderer");
        }
    }
    if (ImGui::CollapsingHeader("Physics")) {
        if (ImGui::Button("Set default (Physics TickRate)")){
            Physics::physicsTickRate = 80.0f;
        }
        ImGui::SliderFloat("Physics TickRate", &Physics::physicsTickRate, 0.01f, 500.0f);
    }

    if (ImGui::CollapsingHeader("Triangle")) {
    for (int i = 0; i < 3; i++){
        ImGui::Text(("Point " + std::to_string(i)).c_str());

        ImGui::SliderFloat(("x##posvertX" + std::to_string(i)).c_str(), &Vertex::triangle0.getVertexData(i).x, -10.0f, 10.0f);
        ImGui::SliderFloat(("y##posvertY" + std::to_string(i)).c_str(), &Vertex::triangle0.getVertexData(i).y, -10.0f, 10.0f);
        ImGui::SliderFloat(("z##posvertZ" + std::to_string(i)).c_str(), &Vertex::triangle0.getVertexData(i).z, -10.0f, 10.0f);

        static float colVert0[3] = {Material::vert0R, Material::vert0G, Material::vert0B};
        ImGui::ColorEdit3(("Color##colvert" + std::to_string(i)).c_str(), colVert0);
        Material::vert0R = colVert0[0]; Material::vert0G = colVert0[1]; Material::vert0B = colVert0[2];
    }
    }
    ImGui::End();
    Console::gameConsole.Draw();

}
