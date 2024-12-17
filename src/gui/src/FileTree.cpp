#include "FileTree.hpp"

void FileTree::SetupFileTreeChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.x * 0.1f, availableSpace.y * 1.0f);

    this->PushStyle();
    ImGui::BeginChild("FileTree", size, this->configuration);
        ImGui::Text("filetree");
    ImGui::EndChild();
    this->PopStyle();
}

void FileTree::PushStyle() /* private */
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void FileTree::PopStyle() /* private */
{
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}
