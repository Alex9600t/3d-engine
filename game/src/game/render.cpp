#include <SFML/Graphics.hpp>
#include "render.h"
#include "scene/material.h"

    void Render::update(sf::RenderWindow& window){
        window.clear();
        window.draw(Material::text);
        window.draw(Material::fringe0);
        window.draw(Material::fringe1);
        window.display();
    }