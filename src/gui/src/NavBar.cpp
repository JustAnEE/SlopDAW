#include "NavBar.hpp"

void NavBar::SetupNavBarChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.x * 1.0f, availableSpace.y * 0.04f);

    this->PushStyle();
    ImGui::BeginChild("NavBar", size, this->configuration);
        ImVec2 childSpace = ImGui::GetContentRegionAvail();
        float fontHeight = ImGui::GetFontSize();
        float offsetY = (childSpace.y - fontHeight) / 2.0f;

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);

        ImGui::BeginTable("NavTable", 3, ImGuiTableFlags_SizingFixedFit);
            ImGui::TableNextColumn();
            ImGui::Text("SlopDaw Studios");

            ImGui::TableNextColumn();
            ImGui::Button("Play");

            ImGui::TableNextColumn();
            ImGui::Button("Pause");
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
