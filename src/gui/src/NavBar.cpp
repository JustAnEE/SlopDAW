#include "NavBar.hpp"
#include <filesystem>

void NavBar::SetupNavBarChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.x * 1.0f, availableSpace.y * 0.04f);

    this->PushStyle();
    ImGui::BeginChild("NavBar", size, this->childConfiguration, this->windowConfiguration);
        ImVec2 childSpace = ImGui::GetContentRegionAvail();
        float fontHeight = ImGui::GetFontSize();
        float offsetY = (childSpace.y - fontHeight) / 2.0f;
        float center = ImGui::GetCursorPosY() + offsetY;

        // TODO: load once....
        //int logo = GlfwApi::LoadTexture("..\\..\\SlopDAW\\content\\SDLogo.png");

        ImGui::SetCursorPosY(center);

        ImGui::BeginTable("NavTable", 4, this->tableConfiguration);
            ImGui::TableNextColumn();
            ImGui::BeginGroup();
                ImGui::SetCursorPosY(0);
                //ImGui::Image(logo, ImVec2(50, 50));
                ImGui::SameLine();
                ImGui::SetCursorPosY(center);
                ImGui::Text("SlopDaw Studios");
            ImGui::EndGroup();

            ImGui::TableNextColumn();
            ImGui::BeginGroup();
                ImGui::Button("Play");
                ImGui::SameLine();
                ImGui::Button("Pause");
                ImGui::SameLine();
                ImGui::Text("00:00:00.00");
            ImGui::EndGroup();

            ImGui::TableNextColumn();
            ImGui::Text("BPM 140");

            ImGui::TableNextColumn();
            ImGui::Text("metronome");
        ImGui::EndTable();
    ImGui::EndChild();
    this->PopStyle();
}

void NavBar::PushStyle() /* private */
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 0.6f, 0.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void NavBar::PopStyle() /* private */
{
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}
