#pragma once
#include <SFML/Graphics.hpp>
#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui-SFML.h"



namespace GameImgui {
    void imguiInit(sf::RenderWindow& window);
    void imguistart(sf::RenderWindow& window);
    void shutdown();
    void imguiRender(sf::RenderWindow& window);
}