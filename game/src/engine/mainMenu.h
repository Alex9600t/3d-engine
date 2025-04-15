#pragma once

#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui-SFML.h"
#include "../game/game.hpp"
#include "../game/mapSystem.h"
#include "../game/render.h"
#include "../game/Audio/audio.h"

namespace MainMenu {
    void renderMainMenu();
    extern int pages;
    extern int type;
    extern std::string newWorldName;
    extern int newWorldSeed;
}