#include <lua.hpp>
#include "../../game/render.h"
#include "../console.h"
#include <thread>

#include "GameLua.h"
#include "luaVar.h"

std::vector<LuaVar::LUAHitBoxStruc> LuaVar::LUAHitbox;
std::vector<LuaVar::LUARenderLineStruc> LuaVar::LUALine;
std::vector<LuaVar::LUAHookStruc> LuaVar::LUAHooks;


// Render

int setFOV(lua_State* L) {
    double fov = luaL_checknumber(L, 1);
    Render::OpenGLCamera::camera.FOV = fov;

    return 0;
}

int getCameraData(lua_State* L) {
    lua_newtable(L);
    lua_pushnumber(L, Render::OpenGLCamera::camera.FOV);
    lua_setfield(L, -2, "FOV");

    return 1;
}

int drawLine(lua_State* L) {
    LuaVar::LUARenderLineStruc tmp{
        static_cast<float>(luaL_checknumber(L, 1)),
        static_cast<float>(luaL_checknumber(L, 2)),
        static_cast<float>(luaL_checknumber(L, 3)),
        static_cast<float>(luaL_checknumber(L, 4)),
        static_cast<float>(luaL_checknumber(L, 5)),
        static_cast<float>(luaL_checknumber(L, 6)),
        static_cast<float>(luaL_checknumber(L, 7)),
        static_cast<float>(luaL_checknumber(L, 8)),
        static_cast<float>(luaL_checknumber(L, 9))
    };

    LuaVar::LUALine.push_back(tmp);

    // Render::LUALines.push_back(sf::Vector3f(x, y, z));
    // Render::LUALines.push_back(sf::Vector3f(x1, y1, z1));

    return 0;
}

int createScreenShot(lua_State* L) {
    std::string name = luaL_checkstring(L, 1);
    RenderEvent::screenShot(Game::w, Game::h, name);

    return 0;
};

int clearBufferLines(lua_State* L) {
    LuaVar::LUALine.clear();
    return 0;
}

// Player

int getPos(lua_State* L) {
    sf::Vector3f pos = Render::Camera::camera.pos;
    lua_newtable(L);
    lua_pushnumber(L, pos.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, pos.y);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, -pos.z);
    lua_setfield(L, -2, "z");

    return 1;
}

int teleport(lua_State* L) {
    double x = luaL_checknumber(L, 1);
    double y = luaL_checknumber(L, 2);
    double z = luaL_checknumber(L, 3);
    double mx = luaL_checknumber(L, 4);
    double my = luaL_checknumber(L, 5);

    Render::Camera::camera.pos = sf::Vector3f(x, y, -z);
    Render::Camera::camera.mx = mx;
    Render::Camera::camera.my = my;
    return 0;
}

int getCamera(lua_State* L) {
    sf::Vector2f camera = sf::Vector2f(Render::Camera::camera.mx, Render::Camera::camera.my);
    lua_newtable(L);
    lua_pushnumber(L, camera.x);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, camera.y);
    lua_setfield(L, -2, "y");

    return 1;
}

// Chat

int send(lua_State* L) {
    std::string msg = luaL_checkstring(L, 1);
    Console::gameConsole.history.push_back(msg);

    return 0;
}

int chatClear(lua_State* L) {
    Console::gameConsole.history.clear();

    return 0;
}

// Engine

int loadLUAScripts(lua_State* L) {
    std::string src = luaL_checkstring(L, 1);
    Lua::loadLua(src);

    return 0;
};

int loadLocalLUAScript(lua_State* L) {
    std::string script = luaL_checkstring(L, 1);
    Lua::loadLocalLua(script);

    return 0;
};

int loadMap(lua_State* L) {
    std::string name = luaL_checkstring(L, 1);
    Map::loadMapFromFile(name);
    Render::renderMapUpdate();
    Game::inGame = true;

    return 0;
};

int quitLUA(lua_State* L) {
    Game::isGameClose = true;

    return 0;
};

int menuLUA(lua_State* L) {
    Game::isMainMenu = !Game::isMainMenu;

    return 0;
}

// Hook

void registerHook(std::string name, std::string lua) {
    LuaVar::LUAHooks.push_back({name, lua});
}

int LUAGetHook(lua_State* L) {
    lua_newtable(L);
    lua_pushnumber(L, 1);
    lua_setfield(L, -2, "x");
    lua_pushnumber(L, 100);
    lua_setfield(L, -2, "y");
    lua_pushnumber(L, 3);
    lua_setfield(L, -2, "z");
};

void LuaVar::callHook(std::string name, sf::Vector3f pos) {
    if (LuaVar::LUAHooks.size() == 0) {
        return;
    }
    for (int id = 0; id < LuaVar::LUAHooks.size(); id++) {
        if (LuaVar::LUAHooks[id].name == name) {
            Lua::loadLua(LuaVar::LUAHooks[id].lua);
        }
    }
}

int LUARegisterHook(lua_State* L) {
    std::string hookName = lua_tostring(L, 1);
    std::string lua = lua_tostring(L, 2);
    registerHook(hookName, lua);

    return 0;
};


void Lua::reg(lua_State* L) {
    // Render
    lua_newtable(L);
    lua_pushcfunction(L, setFOV);
    lua_setfield(L, -2, "setFOV");

    lua_pushcfunction(L, getCameraData);
    lua_setfield(L, -2, "getCamera");

    lua_pushcfunction(L, drawLine);
    lua_setfield(L, -2, "drawLine");

    lua_pushcfunction(L, createScreenShot);
    lua_setfield(L, -2, "newScreenshot");

    lua_pushcfunction(L, clearBufferLines);
    lua_setfield(L, -2, "clearBufferLines");

    lua_newtable(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, [](lua_State* L) -> int {
        return luaL_error(L, "Cannot modify Player");
        });
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "__Render");

    // Player
    lua_newtable(L);
    lua_pushcfunction(L, getPos);
    lua_setfield(L, -2, "getPos");

    lua_pushcfunction(L, getCamera);
    lua_setfield(L, -2, "getCamera");

    lua_pushcfunction(L, teleport);
    lua_setfield(L, -2, "teleport");

    lua_newtable(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, [](lua_State* L) -> int {
        return luaL_error(L, "Cannot modify Player");
        });
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "__Player");

    // Chat
    lua_newtable(L);
    lua_pushcfunction(L, send);
    lua_setfield(L, -2, "send");

    lua_pushcfunction(L, chatClear);
    lua_setfield(L, -2, "clear");

    lua_pushcfunction(L, teleport);
    lua_setfield(L, -2, "teleport");

    lua_newtable(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, [](lua_State* L) -> int {
        return luaL_error(L, "Cannot modify Player");
        });
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "__Chat");

    // Engine
    lua_newtable(L);
    lua_pushcfunction(L, loadLUAScripts);
    lua_setfield(L, -2, "loadScript");

    lua_pushcfunction(L, loadLocalLUAScript);
    lua_setfield(L, -2, "loadLocalScript");

    lua_pushcfunction(L, loadMap);
    lua_setfield(L, -2, "loadMap");

    lua_pushcfunction(L, quitLUA);
    lua_setfield(L, -2, "quit");

    lua_pushcfunction(L, menuLUA);
    lua_setfield(L, -2, "menu");

    lua_newtable(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, [](lua_State* L) -> int {
        return luaL_error(L, "Cannot modify Player");
        });
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "__Engine");

    // Server
    lua_newtable(L);
    lua_pushcfunction(L, loadMap);
    lua_setfield(L, -2, "sv_loadMap");

    lua_newtable(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, [](lua_State* L) -> int {
        return luaL_error(L, "Cannot modify Player");
        });
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "__Server");

    // Hook
    lua_newtable(L);
    lua_pushcfunction(L, LUARegisterHook);
    lua_setfield(L, -2, "hook");

    lua_pushcfunction(L, LUAGetHook);
    lua_setfield(L, -2, "getData");

    lua_newtable(L);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, [](lua_State* L) -> int {
        return luaL_error(L, "Cannot modify Player");
        });
    lua_settable(L, -3);
    lua_setmetatable(L, -2);
    lua_setglobal(L, "__Hook");


    // Init
    lua_newtable(L);
    lua_getglobal(L, "__Player");
    lua_setfield(L, -2, "Player");
    lua_getglobal(L, "__Render");
    lua_setfield(L, -2, "Render");
    lua_getglobal(L, "__Chat");
    lua_setfield(L, -2, "Chat");
    lua_getglobal(L, "__Engine");
    lua_setfield(L, -2, "Engine");
    lua_getglobal(L, "__Server");
    lua_setfield(L, -2, "Server");
    lua_getglobal(L, "__Hook");
    lua_setfield(L, -2, "Hook");

    lua_setglobal(L, "Game");
}

int Lua::loadLua(std::string name) {
    lua_State* script = luaL_newstate();
    luaL_openlibs(script);
    Lua::reg(script);


    std::cout << "-----------------" << name << "---------------------" << std::endl;
    luaL_dofile(script, std::string("game/src/game/scripts/" + name).c_str());
    std::cout << "-----------------End-" << name << "-----------------" << std::endl;
    lua_close(script);
    return 0;
};

int Lua::loadLocalLua(std::string script) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    Lua::reg(L);
    std::cout << "-----------------_tmp-script_-----------------" << std::endl;
    if (luaL_dostring(L, script.c_str())) {}
    std::cout << "-----------------End-_tmp-script_-------------" << std::endl;
    lua_close(L);
    return 0;
};

int LuaVar::loadScript(std::string name) {
    Lua::loadLua(name);
    return 0;
}