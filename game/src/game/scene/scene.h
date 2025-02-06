#pragma once
#include <SFML/Graphics.hpp>


namespace Scene {
    void renderAll(sf::RenderWindow& window);
    void MaterialInit(sf::RenderWindow& window);
    void changeTriangle(sf::ConvexShape &tringle, float t0x, float t0y, float t1x, float t1y, float t2x, float t2y);
    void debugMenu(sf::RenderWindow& window);
    void setMaterialPreset0(sf::ConvexShape &tringle);
    void setPossition(sf::ConvexShape &tringle, float x, float y, float z);
}