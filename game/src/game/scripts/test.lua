-- --PLAYER
local mx = Game.Player:getCamera().x
local my = Game.Player:getCamera().y
-- Player pos
local x = Game.Player:getPos().x
local y = Game.Player:getPos().y
local z = Game.Player:getPos().z
-- Render data
local fov = Game.Render:getCamera().FOV
-- functions
Game.Player.teleport(x, y, z, mx, my)

-- --RENDER
-- functions
Game.Render.drawLine(x, y, z, 0, 0, 0, 1, 0, 0)
if false then
    Game.Render.clearBufferLines()
    print("Buffer clear")
end

-- --CHAT
-- functions
Game.Chat.send("Hello, LUA!")
if false then
    Game.Chat.clear()
    print("Chat clear")
end

-- -- -- log
print("Player MX:", mx)
print("Player MY:", my)
print("Player X:", x)
print("Player Y:", y)
print("Player Z:", z)
print("Render FOV:", fov)

Game.Engine.loadScript("debug/hitbox.lua")
Game.Engine.loadLocalScript("print('Hi')")

-- Game.Server.sv_loadMap("testmap")