Game.Render.clearBufferLines()

local x = Game.Player:getPos().x
local y = Game.Player:getPos().y
local z = Game.Player:getPos().z

local mx = Game.Player:getCamera().x
local my = Game.Player:getCamera().y

Game.Render.drawLine(x, y, z, x + 5, y, z, 1, 0, 0)
Game.Render.drawLine(x, y, z, x, y, z + 5, 0, 1, 0)

Game.Render.drawLine(x + 0.5, y - 1.5, z + 0.5, x + 0.5, y - 1.5, z - 0.5, 1, 1, 0)
Game.Render.drawLine(x - 0.5, y - 1.5, z + 0.5, x - 0.5, y - 1.5, z - 0.5, 1, 1, 0)
Game.Render.drawLine(x + 0.5, y - 1.5, z + 0.5, x - 0.5, y - 1.5, z + 0.5, 1, 1, 0)
Game.Render.drawLine(x + 0.5, y - 1.5, z - 0.5, x - 0.5, y - 1.5, z - 0.5, 1, 1, 0)

Game.Render.drawLine(x + 0.5, y + 0.5, z + 0.5, x + 0.5, y + 0.5, z - 0.5, 1, 1, 0)
Game.Render.drawLine(x - 0.5, y + 0.5, z + 0.5, x - 0.5, y + 0.5, z - 0.5, 1, 1, 0)
Game.Render.drawLine(x + 0.5, y + 0.5, z + 0.5, x - 0.5, y + 0.5, z + 0.5, 1, 1, 0)
Game.Render.drawLine(x + 0.5, y + 0.5, z - 0.5, x - 0.5, y + 0.5, z - 0.5, 1, 1, 0)

Game.Render.drawLine(x + 0.5, y - 1.5, z + 0.5, x + 0.5, y + 0.5, z + 0.5, 1, 1, 0)
Game.Render.drawLine(x - 0.5, y - 1.5, z + 0.5, x - 0.5, y + 0.5, z + 0.5, 1, 1, 0)
Game.Render.drawLine(x + 0.5, y - 1.5, z - 0.5, x + 0.5, y + 0.5, z - 0.5, 1, 1, 0)
Game.Render.drawLine(x - 0.5, y - 1.5, z - 0.5, x - 0.5, y + 0.5, z - 0.5, 1, 1, 0)

print(mx .. " test " .. my)