#pragma once 
#include <iostream>

#include "../../game/game.hpp"

namespace Lua {
    int loadLocalLua(std::string script);
    int loadLua(std::string name);
    void reg(lua_State* L);
}
