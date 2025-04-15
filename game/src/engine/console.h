#pragma once
#include "GameImgui.h"
#include "../game/game.hpp"

namespace Console{

    void sent(const std::string &command, std::vector<std::string> &history);
    extern std::vector<std::string> commands;
class ClassConsole{
public:
    void Draw() {
        ImGui::Begin("Console");
        
        for (const auto &line : history)
            ImGui::TextUnformatted(line.c_str());

        ImGui::Separator();

        if (ImGui::InputText("Input", inputBuffer, sizeof(inputBuffer), 
            ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion, 
            &TextEditCallback, this)) {
            ProcessCommand(inputBuffer);
            inputBuffer[0] = '\0';
        }

        ImGui::End();
    }
    std::vector<std::string> history;


private:
static int TextEditCallback(ImGuiInputTextCallbackData* data)
    {
        ClassConsole* console = static_cast<ClassConsole*>(data->UserData);
        if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
        {
            console->AutoCompleteCommand(data);
        }
        return 0;
    }

    void AutoCompleteCommand(ImGuiInputTextCallbackData* data)
    {
        std::string input = data->Buf;
        if (input.empty()) return;

        std::vector<std::string> matches;
        for (const auto &cmd : commands)
        {
            if (cmd.find(input) == 0)
                matches.push_back(cmd);
        }

        if (matches.size() == 1)
        {
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, matches[0].c_str());
        }
        else if (!matches.empty())
        {
            history.push_back("Suggestions: " + Join(matches, ", "));
        }
    }
    void ProcessCommand(const std::string &command){
        history.push_back("> " + command);
        sent(command, history);
        // if (command == "clear")
        //     history.clear();
        // else
        //     history.push_back("Unknown command: " + command);
    }

    static std::string Join(const std::vector<std::string>& vec, const std::string& separator)
    {
        std::string result;
        for (size_t i = 0; i < vec.size(); ++i)
        {
            result += vec[i];
            if (i < vec.size() - 1) result += separator;
        }
        return result;
    }
    char inputBuffer[256] = {0};

};

extern ClassConsole gameConsole;
}