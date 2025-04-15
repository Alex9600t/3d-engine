#include "console.h"
#include <lua.hpp>
#include "../game/physics.h"
#include "lua/GameLua.h"
#include <iostream>
#include <thread>

std::vector<std::string> Console::commands = {"loadScript('"};
std::string commandDescription[] = {"Clear console", "Display menu with tooltips", "menu", "a", "Exit", "Start physics sim"};

void Console::sent(const std::string &command, std::vector<std::string> &history){
    Lua::loadLocalLua(command);
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    Lua::reg(L);

    if (luaL_dofile(L, "game/src/game/scripts/console/console.lua") != LUA_OK) {
        std::runtime_error("Console.lua don't loaded");
    }

    lua_getglobal(L, "console");
    if (!lua_isfunction(L, -1)) {
        std::runtime_error("console.lua: 3: function console is not found");
    }

    lua_pushstring(L, std::string(command).c_str());
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        history.push_back(lua_tostring(L, -1));
        lua_pop(L, 1);
    }

    lua_close(L);


    // } else if (command == commands[7]) {
    //     // Map::gen(832434321);
    //     Map::createNewWorld("test", 5, 4, 3);
    // } else if (command == commands[8]){
    //     Map::loadMapFromFile("testmap");
    //     Render::renderMapUpdate();
    //     // Render::Camera::camera.pos.y = 40.0f;
    // } else if (command == commands[9]){
    //     Lua::loadLua("test.lua");
    // } else {
    //     history.push_back("Unknown command: " + command);
    // }
}