#include <SFML/Graphics.hpp>
#include "scene.h"
#include "material.h"

    void scene::changeTriangle(sf::ConvexShape &tringle, float t0x, float t0y, float t1x, float t1y, float t2x, float t2y){
        tringle.setPoint(0, {t0x, t0y});
        tringle.setPoint(1, {t1x, t1y});
        tringle.setPoint(2, {t2x, t2y});
    }
void scene::MaterialInit(sf::RenderWindow& window){
        Material::fringe0.setFillColor(sf::Color(255, 255, 255, 0));
        Material::fringe0.setOutlineColor(sf::Color::White);
        Material::fringe0.setOutlineThickness(1.f);
        Material::fringe0.setPointCount(3);
                Material::fringe1.setFillColor(sf::Color(255, 255, 255, 0));
        Material::fringe1.setOutlineColor(sf::Color::White);
        Material::fringe1.setOutlineThickness(1.f);
        Material::fringe1.setPointCount(3);
        scene::changeTriangle(Material::fringe0, 0.f, 50.f, 50.f, 0.f, 50.f, 50.f);
        scene::changeTriangle(Material::fringe1, 0.f, 0.f, 50.f, 0.f, 0.f, 50.f);

}
