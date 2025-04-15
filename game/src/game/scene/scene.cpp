#include <SFML/Graphics.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include "scene.h"
#include <iostream>
#include "v.h"

    void Scene::changeTriangle(sf::ConvexShape &tringle, float t0x, float t0y, float t1x, float t1y, float t2x, float t2y){
        tringle.setPoint(0, {t0x, t0y});
        tringle.setPoint(1, {t1x, t1y});
        tringle.setPoint(2, {t2x, t2y});
    }

void Scene::setMaterialPreset0(sf::ConvexShape &tringle){
    tringle.setFillColor(sf::Color(255, 255, 255, 0));
    tringle.setOutlineColor(sf::Color::White);
    tringle.setOutlineThickness(1.f);
    tringle.setPointCount(3);
    Scene::setPossition(Material::triangle2, 0.f, 0.f, 0.5f);
    Scene::setPossition(Material::triangle3, 0.f, 0.f, 0.5f);
}

void Scene::MaterialInit(sf::RenderWindow& window){

    // std::cout << Material::vert0.x << "\n";
    // glClearColor(0.0, 0.0, 0.0, 1.0);


    Material::triangletest.setFillColor(sf::Color(255, 255, 255, 0));
    Material::triangletest.setOutlineColor(sf::Color::White);
    Material::triangletest.setOutlineThickness(1.f);
    Material::triangletest.setPointCount(24);
    Material::triangletest.setPoint(0, {0.f, 0.f});
    Material::triangletest.setPoint(1, {50.f, 0.f});
    Material::triangletest.setPoint(2, {50.f, 50.f});
    Material::triangletest.setPoint(3, {0.f, 50.f});
    Material::triangletest.setPoint(4, {0.f, 0.f});
    Material::triangletest.setPoint(5, {12.5f, 12.5f});
    Material::triangletest.setPoint(6, {12.5f, 37.5f});
    Material::triangletest.setPoint(7, {0.f, 50.f});
    Material::triangletest.setPoint(8, {12.5f, 37.5f});
    Material::triangletest.setPoint(9, {37.5f, 37.5f});
    Material::triangletest.setPoint(10, {50.f, 50.f});
    Material::triangletest.setPoint(11, {37.5f, 37.5f});
    Material::triangletest.setPoint(12, {37.5f, 12.5f});
    Material::triangletest.setPoint(13, {50.f, 0.f});
    Material::triangletest.setPoint(14, {37.5f, 12.5f});
    Material::triangletest.setPoint(15, {12.5f, 12.5f});
    Material::triangletest.setPoint(16, {0.f, 0.f});
    Material::triangletest.setPoint(17, {12.5f, 37.5f});
    Material::triangletest.setPoint(18, {37.5f, 37.5f});
    Material::triangletest.setPoint(19, {0.f, 50.f});
    Material::triangletest.setPoint(20, {37.5f, 12.5f});
    Material::triangletest.setPoint(21, {37.5f, 37.5f});
    Material::triangletest.setPoint(22, {50.f, 0.f});
    Material::triangletest.setPoint(23, {37.5f, 12.5f});

    Material::triangletest.setPosition({50, 50});

        Scene::setMaterialPreset0(Material::triangle0);
        Scene::setMaterialPreset0(Material::triangle1);
        Scene::setMaterialPreset0(Material::triangle2);
        Scene::setMaterialPreset0(Material::triangle3);
        Scene::changeTriangle(Material::triangle0, 0.f, 50.f, 50.f, 0.f, 50.f, 50.f);
        Scene::changeTriangle(Material::triangle1, 0.f, 0.f, 50.f, 0.f, 0.f, 50.f);
        Scene::changeTriangle(Material::triangle2, 0.f, 50.f, 50.f, 0.f, 50.f, 50.f);
        Scene::changeTriangle(Material::triangle3, 0.f, 0.f, 50.f, 0.f, 0.f, 50.f);

}

void Scene::setPossition(sf::ConvexShape &tringle, float x, float y, float z){
    // tringle.setPosition({x, y});
    tringle.setScale({z, z});
}