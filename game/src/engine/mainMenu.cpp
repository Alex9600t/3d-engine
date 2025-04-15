#include "mainMenu.h"
#include <random>

int MainMenu::pages = 0;
int MainMenu::type = 0;
std::string MainMenu::newWorldName = "";
int MainMenu::newWorldSeed = 0;

void MainMenu::renderMainMenu() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
    ImGui::Begin("MainMenu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);
    float buttonWidth = ImGui::GetContentRegionAvail().x * 0.8f;
    float buttonHeight = 40.0f;
    float itemSpacing = 15.0f;
    ImVec2 windowAvail = ImGui::GetContentRegionAvail();

    // Main menu
    if (MainMenu::pages == 0) {
        float totalHeight = (buttonHeight * 3) + ImGui::GetTextLineHeight() + (itemSpacing * 3);
        float startY = (windowAvail.y - totalHeight) * 0.5f;

        // Text
        ImGui::SetCursorPosY(startY);
        ImVec2 text_size = ImGui::CalcTextSize("3D Engine");
        ImGui::SetCursorPosX((windowAvail.x - text_size.x) * 0.5f);
        ImGui::Text("3D Engine");
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Start"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Start Game"), ImVec2(buttonWidth, buttonHeight))) {
            MainMenu::pages = 1;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Settings"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Settings"), ImVec2(buttonWidth, buttonHeight))) {
            MainMenu::pages = 2;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Start"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Exit"), ImVec2(buttonWidth, buttonHeight))) {
            Game::isGameClose = true;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);
    }

    // Worlds menu
    if (MainMenu::pages == 1) {
        int constWorld = Map::getAllMap().size();
        float totalHeight = (buttonHeight * 3) + ImGui::GetTextLineHeight() + (itemSpacing * (3 + constWorld));
        float startY = (windowAvail.y - totalHeight) * 0.5f;

        // Text
        ImGui::SetCursorPosY(startY);
        ImVec2 text_size = ImGui::CalcTextSize("Select world");
        ImGui::SetCursorPosX((windowAvail.x - text_size.x) * 0.5f);
        ImGui::Text("Select world");
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // All world
        for (int i = 0; i < constWorld; i++) {
            std::string tmpWorldName = Map::getAllMap()[i]["name"].get<std::string>().c_str();
            ImGui::Separator();
            ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
            // ImGui::Text((tmpWorldName.c_str()), ImVec2(buttonWidth, buttonHeight));
            if (ImGui::Button((tmpWorldName.c_str()), ImVec2(buttonWidth, buttonHeight))) {
                Map::loadMapFromFile(std::string(tmpWorldName));
                Render::renderMapUpdate();
                Render::Camera::camera.pos.y = 90;
                Game::inGame = true;
            }
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);
            ImGui::Separator();
        }

        // BTN "New world"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("New world"), ImVec2(buttonWidth, buttonHeight))) {
            // Game::inGame = true;
            // MainMenu::type = 1;
            MainMenu::pages = 3;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Cancel"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Cancel"), ImVec2(buttonWidth, buttonHeight))) {
            MainMenu::pages = 0;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);
    }

    // Settings menu
    if (MainMenu::pages == 2) {
        float totalHeight = (buttonHeight * 3) + ImGui::GetTextLineHeight() + (itemSpacing * 3);
        float startY = (windowAvail.y - totalHeight) * 0.5f;

        // Text
        ImGui::SetCursorPosY(startY);
        ImVec2 text_size = ImGui::CalcTextSize("Settings");
        ImGui::SetCursorPosX((windowAvail.x - text_size.x) * 0.5f);
        ImGui::Text("Settings");
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // SLD "FOW"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        ImGui::SliderFloat("FOV", &Render::OpenGLCamera::camera.FOV, 45.0f, 180.0f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // SLD "Volume"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        ImGui::SliderFloat("Volume", &Audio::volume, 0.0f, 100.0f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // CHB "VBO"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        ImGui::Checkbox(("Use VBO (Don't work)"), &Render::isUseVBO);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // CHB "Debug view"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        ImGui::Checkbox(("Debug view"), &Render::debugView);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Cancel"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Cancel"), ImVec2(buttonWidth, buttonHeight))) {
            if (MainMenu::type == 1) {
                MainMenu::pages = 5;
            }
            else {
                MainMenu::pages = 0;
            }
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);
    }

    // New world menu
    if (MainMenu::pages == 3) {
        float totalHeight = (buttonHeight * 3) + ImGui::GetTextLineHeight() + (itemSpacing * 3);
        float startY = (windowAvail.y - totalHeight) * 0.5f;

        // Text
        ImGui::SetCursorPosY(startY);
        ImVec2 text_size = ImGui::CalcTextSize("New world");
        ImGui::SetCursorPosX((windowAvail.x - text_size.x) * 0.5f);
        ImGui::Text("New world");
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // TIN "Name"
        static char newWorldNameBuffer[256] = "";
        if (!MainMenu::newWorldName.empty()) {
            strncpy(newWorldNameBuffer, MainMenu::newWorldName.c_str(), sizeof(newWorldNameBuffer));
        }
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::InputText("Name", newWorldNameBuffer, sizeof(newWorldNameBuffer))) {
            MainMenu::newWorldName = newWorldNameBuffer;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // IIN "Seed"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::InputInt("Seed", &MainMenu::newWorldSeed)) {
            MainMenu::newWorldName = newWorldNameBuffer;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Create"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Create"), ImVec2(buttonWidth, buttonHeight))) {
            std::string tmpWorldName = MainMenu::newWorldName;
            if (tmpWorldName != "" || !Map::worldHasExist(tmpWorldName)) {
                std::random_device dev;
                Map::createNewWorld(tmpWorldName, MainMenu::newWorldSeed == 0 ? dev() % 1000 : MainMenu::newWorldSeed, 0, 0);
                Map::loadMapFromFile(tmpWorldName);
                Render::renderMapUpdate();
                Game::inGame = true;
            }
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);

        // BTN "Cancel"
        ImGui::SetCursorPosX((windowAvail.x - buttonWidth) * 0.5f);
        if (ImGui::Button(("Cancel"), ImVec2(buttonWidth, buttonHeight))) {
            MainMenu::pages = 1;
        }
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + itemSpacing);
    }


    ImGui::End();
}