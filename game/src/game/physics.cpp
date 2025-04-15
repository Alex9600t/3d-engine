#include "physics.h"

Physics::PhysicsObj Physics::PhysicsObj::abc;

float Physics::physicsTickRate = 80.0f;
float Physics::gravity = 9.81f;
bool Physics::isPhysicsEnable = false;
sf::Clock Physics::deltaClock;

void Physics::physicsCalc(Physics::PhysicsObj &obj){
    if (obj.pos.y >= 3) {
    const double fixedDeltaTime = 1.0 / Physics::physicsTickRate;
    obj.velocity += Physics::gravity * fixedDeltaTime;
    obj.pos.y -= obj.velocity * fixedDeltaTime;
    
    }}

void Physics::physicsUpdate() {
    if (Physics::deltaClock.getElapsedTime().asSeconds() >= 1.0f / Physics::physicsTickRate) {
        RenderEvent::cameraWalk();
        // Physics::physicsCalc(Physics::PhysicsObj::abc);
        Physics::deltaClock.restart();
    }
}

bool Physics::isStaticBlock(sf::Vector3f pos) {
    for (const auto& cube : Render::blockList) {
        if (cube.x == pos.x && cube.y == pos.y && cube.z == pos.z) {
            return true;
        }
    }
    return false;
}

bool Physics::isStaticBlockNearby(sf::Vector3f pos) {
    float tolerance = 0.15f;
    for (const auto& cube : Render::blockList) {
        float dx = cube.x - pos.x;
        float dy = cube.y - pos.y;
        float dz = cube.z - pos.z;
        std::cout << "Checking: pos=(" << pos.x << "," << pos.y << "," << pos.z << ")\n";
std::cout << "Block at (" << cube.x << "," << cube.y << "," << cube.z << "): dx=" << dx << " dy=" << dy << " dz=" << dz << "\n";

        
        if (std::abs(dx) <= tolerance && std::abs(dy) <= tolerance && std::abs(dz) <= tolerance) {
            return true;
        }
    }
    return false;
}

bool checkAABBCollision(sf::Vector3f pos0, sf::Vector3f size0, sf::Vector3f pos1, sf::Vector3f size1) {
    return (
        pos0.x < pos1.x + size1.x &&
        pos0.x + size0.x > pos1.x &&
        pos0.y < pos1.y + size1.y &&
        pos0.y + size0.y > pos1.y &&
        pos0.z < pos1.z + size1.z &&
        pos0.z + size0.z > pos1.z
    );
};

bool Physics::checkCollision(sf::Vector3f pos) {
    float tolerance = 0.15f;
    for (const auto& cube : Render::blockList) {
        float dx = cube.x - pos.x;
        float dy = cube.y - pos.y;
        float dz = cube.z - pos.z;
        float distX = std::abs(dx);
        float distY = std::abs(dy);
        float distZ = std::abs(dz);

        // if (distX <= (0.5f + tolerance) && distY <= (0.5f + tolerance) && distZ <= (0.5f + tolerance)) {
        //     return true;
        // }
        if (checkAABBCollision(pos, sf::Vector3f(1, 2, 1), sf::Vector3f(cube.x, cube.y, cube.z), sf::Vector3f(0.75, 0.5, 0.75))) {
            return true;
        }
    }
    return false;
}

