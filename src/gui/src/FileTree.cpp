#include "FileTree.hpp"

void FileTree::SetupFileTreeChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.x * 0.1f, availableSpace.y * 1.0f);

    this->PushStyle();
    ImGui::BeginChild("FileTree", size, this->childConfiguration, this->windowConfiguration);
        ImGui::Text("filetree");

        ImGui::BeginGroup();
            ImGui::Text("Library");
            this->ActivateTree("All", nullptr);
            this->ActivateTree("Sounds", nullptr);
            this->ActivateTree("Instruments", nullptr);
            this->ActivateTree("Plugins", nullptr);
            this->ActivateTree("Samples", nullptr);
        ImGui::EndGroup();

        ImGui::BeginGroup();
            ImGui::Text("Local Environment");
            this->ActivateTree("Current Project", nullptr);
            this->ActivateTree("Projects", nullptr);
        ImGui::EndGroup();

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

void FileTree::ActivateTree(const char* name, void* options) /* private */
{
    if (ImGui::TreeNode(name))
    {
        for (int i = 0; i < 10; i++)
        {
            ImGui::Text("Test %d", i); // Add options laters.
        }
        ImGui::TreePop();
    }
}
