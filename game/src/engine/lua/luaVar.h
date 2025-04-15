#pragma once
#include <iostream>

namespace LuaVar {
    struct LUAHitBoxStruc {
        std::string type;
        float x, y, z;
        float sizeX, sizeY, sizeZ; 
    };
    struct LUARenderLineStruc {
        float x0, y0, z0;
        float x1, y1, z1;
        float r, g, b;
    };
    struct LUAHookStruc {
        std::string name, lua;
    };

    extern std::vector<LUAHitBoxStruc> LUAHitbox;
    extern std::vector<LUARenderLineStruc> LUALine;
    extern std::vector<LUAHookStruc> LUAHooks;

    void callHook(std::string name, sf::Vector3f pos); 

    int loadScript(std::string name);
}