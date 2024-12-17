#include "Tracklist.hpp"

void Tracklist::SetupTracklistChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.x * 1.0f, availableSpace.y * 0.75f);

    this->PushStyle();
    ImGui::BeginChild("Tracklist", size, this->childConfiguration, this->windowConfiguration);
        ImGui::Text("Tracklist");
    ImGui::EndChild();
    this->PopStyle();
}

void Tracklist::PushStyle() /* private */
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void Tracklist::PopStyle() /* private */
{
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}