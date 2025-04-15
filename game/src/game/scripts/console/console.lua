commandClass = {[0]="Player", [1]="Engine", [2]="Console", [3]="Render", [4]="Server", [5]="Client"}

function console(script)
    funcBase, args = script:match("([^(]+)%((.*)%)")
    if not funcBase then
        Game.Chat.send("Invalid script format")
        return
    end

    for i = 0, #commandClass, 1 do
        obj = _G.Game and Game[commandClass[i]]
        if obj and type(obj[funcBase]) == "function" then
            print(#commandClass)
            Game.Engine.loadLocalScript("Game." .. commandClass[i] .. "." .. script)
            return true
        else
            if i == #commandClass then
                Game.Chat.send("Unknown command: " .. script)
            end
        end
    end
end