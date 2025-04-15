#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "renderEvent.h"
#include "render.h"
#include "../../../stb/stb_image_write.h"
#include <math.h>

Render::Camera Render::Camera::camera;

bool RenderEvent::isMouseActive = true;


void RenderEvent::cameraMove(){

    // if (Render::Camera::camera.speed != 0){
    //     const double fixedDeltaTime = 1.0 / Physics::physicsTickRate;
    //     Render::Camera::camera.pos.x += sin(Render::Camera::camera.angle) * Render::Camera::camera.speed * fixedDeltaTime;
    //     Render::Camera::camera.pos.z += cos(Render::Camera::camera.angle) * Render::Camera::camera.speed * fixedDeltaTime;
    // }

    glRotatef(Render::Camera::camera.my, 1.0f, 0.0f, 0.0f);
    glRotatef(-Render::Camera::camera.mx, 0.0f, 0.0f, 1.0f);
    glTranslatef(-Render::Camera::camera.pos.x, -Render::Camera::camera.pos.z, -Render::Camera::camera.pos.y);
}
void RenderEvent::cameraWalk(){
    if (!Render::Camera::camera.isFlying) {
        if (Render::Camera::camera.speed != 0) {
            if (!Physics::checkCollision(sf::Vector3f(
                Render::Camera::camera.pos.x + sin(Render::Camera::camera.angle) * Render::Camera::camera.speed,
                Render::Camera::camera.pos.y - 1,
                -Render::Camera::camera.pos.z
            )) && !Physics::checkCollision(sf::Vector3f(
                Render::Camera::camera.pos.x + sin(Render::Camera::camera.angle) * Render::Camera::camera.speed,
                Render::Camera::camera.pos.y,
                -Render::Camera::camera.pos.z
            ))) {
                Render::Camera::camera.pos.x += sin(Render::Camera::camera.angle) * Render::Camera::camera.speed;
            }
            
            if (!Physics::checkCollision(sf::Vector3f(
                Render::Camera::camera.pos.x,
                Render::Camera::camera.pos.y - 1,
                -Render::Camera::camera.pos.z - cos(Render::Camera::camera.angle) * Render::Camera::camera.speed
            )) && !Physics::checkCollision(sf::Vector3f(
                Render::Camera::camera.pos.x,
                Render::Camera::camera.pos.y,
                -Render::Camera::camera.pos.z - cos(Render::Camera::camera.angle) * Render::Camera::camera.speed
            ))) {
                Render::Camera::camera.pos.z += cos(Render::Camera::camera.angle) * Render::Camera::camera.speed;
            }
        }
    
        if (Render::Camera::camera.isJumping) {
            const double fixedDeltaTime = 1.0 / Physics::physicsTickRate;
            Render::Camera::camera.velocity.y += Physics::gravity * fixedDeltaTime * 20;
            Render::Camera::camera.pos.y += Render::Camera::camera.velocity.y * fixedDeltaTime;
            std::cout << Render::Camera::camera.velocity.y << std::endl;
            if (Render::Camera::camera.velocity.y >= 7.0f) {
                Render::Camera::camera.isJumping = false;
            }
            
        } else if (!Render::Camera::camera.isJumping) {
            // if (!Physics::isStaticBlock(sf::Vector3f(std::round(Render::Camera::camera.pos.x), std::round(Render::Camera::camera.pos.y - 2), std::round(-Render::Camera::camera.pos.z)))) {
            if (!Physics::checkCollision(sf::Vector3f(
                Render::Camera::camera.pos.x,
                Render::Camera::camera.pos.y -1.5,
                -Render::Camera::camera.pos.z))) {
                const double fixedDeltaTime = 1.0 / Physics::physicsTickRate;
            Render::Camera::camera.velocity.y -= Physics::gravity * fixedDeltaTime * 2;
            Render::Camera::camera.pos.y += Render::Camera::camera.velocity.y * fixedDeltaTime;
            } 
            // else if (Physics::isStaticBlock(sf::Vector3f(std::round(Render::Camera::camera.pos.x), std::round(Render::Camera::camera.pos.y - 2), std::round(-Render::Camera::camera.pos.z)))) {
            else if (Physics::checkCollision(sf::Vector3f(
                Render::Camera::camera.pos.x,
                Render::Camera::camera.pos.y -1.5,
                -Render::Camera::camera.pos.z))) {
                Render::Camera::camera.velocity.y = 0.0f;
                // Render::Camera::camera.pos.y = std::round(Render::Camera::camera.pos.y);
            }
        }

    } else {
        
    if (Render::Camera::camera.speed != 0) {
            Render::Camera::camera.pos.x += sin(Render::Camera::camera.angle) * Render::Camera::camera.speed;
            Render::Camera::camera.pos.z += cos(Render::Camera::camera.angle) * Render::Camera::camera.speed;
    }

    if (Render::Camera::camera.isJumping) {
        Render::Camera::camera.pos.y++;
            Render::Camera::camera.isJumping = false;
    }
}
}

void RenderEvent::cameraIsJump() {
    // if (Physics::isStaticBlock(sf::Vector3f(std::round(Render::Camera::camera.pos.x), std::round(Render::Camera::camera.pos.y - 2), std::round(-Render::Camera::camera.pos.z)))) {
        if (Physics::checkCollision(sf::Vector3f(
            Render::Camera::camera.pos.x,
            Render::Camera::camera.pos.y -1.5,
            -Render::Camera::camera.pos.z))) {
        Render::Camera::camera.isJumping = true;
    }
}


void RenderEvent::screenShot(int width, int height, std::string name) {

    unsigned char* pixels = new unsigned char[width * height * 3];
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    unsigned char* flipped = new unsigned char[width * height * 3];
    for (int y = 0; y < height; y++) {
        memcpy(flipped + y * width * 3, 
               pixels + (height - y - 1) * width * 3, 
               width * 3);
    }

    stbi_write_png(std::string(name + ".png").c_str(), width, height, 3, flipped, width * 3);

    delete[] pixels;
    delete[] flipped;
}