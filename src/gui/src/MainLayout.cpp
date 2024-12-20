#include "MainLayout.hpp"

void MainLayout::SetupMainLayout()
{
    ImVec2 size = ImVec2(1920, 1080);
    ImVec2 position = ImVec2(0, 0);

    int activeTracks = 1;

    this->PushStyle();
    ImGui::Begin("TracklistLayout", nullptr, this->configuration);
        ImGui::SetWindowSize(size, ImGuiCond_Always);
        ImGui::SetWindowPos(position, ImGuiCond_Always);
        ImGui::SetCursorPos(ImVec2(0, 0));

        // Layout Content
        this->nav.SetupNavBarChild();
        this->filetree.SetupFileTreeChild();

        ImGui::SameLine();

        ImGui::BeginGroup();
            this->tracklist.SetupTracklistChild();
            this->mixer.SetupMixerChild();
        ImGui::EndGroup();

    ImGui::End();
    this->PopStyle();
}

MouseEvent MainLayout::SendMouseEvent(MouseEvent e)
{
    if (e.targetElementId == 0 && !e.stopPropagation)
    {
        e = this->tracklist.SendMouseEvent(e);
    }

    if(e.targetElementId == 0 && !e.stopPropagation)
    {
        // TODO: IMPLEMENT
        //e = this->mixer.SendMouseEvent(e);
    }

    return e;
}

void MainLayout::PushStyle() /* private */
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void MainLayout::PopStyle() /* private */
{
    ImGui::PopStyleVar();
}
