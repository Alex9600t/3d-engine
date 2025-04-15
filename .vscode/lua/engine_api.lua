---@class Vec2
---@field x number
---@field y number

---@class Vec3
---@field x number
---@field y number
---@field z number

---@class Player
local Player = {}

---@return Vec3
function Player:getCamera() end

---@return Vec3
function Player:getPos() end

---@param x number
---@param y number
---@param z number
---@param mx number
---@param my number
function Player.teleport(x, y, z, mx, my) end

---@class RenderCamera
---@field FOV number

---@class Render
local Render = {}

---@return RenderCamera
function Render:getCamera() end

---@param x1 number
---@param y1 number
---@param z1 number
---@param x2 number
---@param y2 number
---@param z2 number
---@param r number
---@param g number
---@param b number
function Render.drawLine(x1, y1, z1, x2, y2, z2, r, g, b) end

---@param name number
function Render.newScreenshot(name) end

function Render.clearBufferLines() end

function Render.setFOV(FOV) end

---@class Chat
local Chat = {}

---@param msg string
function Chat.send(msg) end

function Chat.clear() end

---@class Engine
local Engine = {}

---@param msg string
---@param script string
function Engine.loadScript(msg) end

function Engine.loadLocalScript(script) end

---@class Server
local Server = {}

---@param map string
function Server.sv_loadMap(map) end


---@class GameClass
---@field Player Player
---@field Render Render
---@field Chat Chat
---@field Engine Engine
---@field Server Server

---@type GameClass
Game = {}
