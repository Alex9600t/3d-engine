#pragma once
#include "physics.h"

namespace RenderEvent {
    extern bool isMouseActive;
    void cameraMove();
    void cameraWalk();
    void cameraIsJump();
    void screenShot(int width, int height, std::string name);
}
