#pragma once
#include "render.h"
#include "renderEvent.h"


namespace Physics{
    extern float physicsTickRate; /*DO NOT CHANGE!!!! 80 tick */
    extern float gravity; /*DO NOT CHANGE!!!! 9.81 */
    extern bool isPhysicsEnable;
    extern sf::Clock deltaClock;
    class PhysicsObj {
        public:
            int id = 1;
            float mass = 10;
            float velocity = 0.0f;
            sf::Vector3f pos = sf::Vector3f(0.0f, 10.0f, 0.0f);
            static PhysicsObj abc;
    };
    void physicsCalc(PhysicsObj&);

    bool isStaticBlock(sf::Vector3f pos);
    bool isStaticBlockNearby(sf::Vector3f pos);
    bool checkCollision(sf::Vector3f pos);

    void physicsUpdate();
}
