#include "Mixer.hpp"


// TODO: Needs to be tied to a track.
void Mixer::SetupMixerChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.y * 0.5f, availableSpace.y);

    this->PushStyle();
    ImGui::BeginChild("Mixer", size, this->childConfiguration, this->windowConfiguration);
        float sliderValue = 0; // Dummy value

        ImVec2 childSpace = ImGui::GetContentRegionAvail();
        ImVec2 sliderSize = ImVec2(childSpace.x * 0.22f, childSpace.y * 0.90f);

        ImGui::Text("Mixer");

        ImGui::BeginTable("MixerTable", 3, ImGuiTableFlags_SizingFixedFit);
            ImGui::TableNextColumn();
            ImGui::BeginGroup();
                ImGui::Text("T1");
                ImGui::Button("Knob");
            ImGui::EndGroup();

            ImGui::TableNextColumn();
            ImGui::VSliderFloat("", sliderSize, &sliderValue, 0, 10, "%.0f", this->sliderConfiguration);

            ImGui::TableNextColumn();
            ImGui::ProgressBar(0.0f, sliderSize);
        ImGui::EndTable();

    ImGui::EndChild();
    this->PopStyle();
}

void Mixer::PushStyle() /* private */
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.68f, 0.6f, 0.85f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void Mixer::PopStyle() /* private */
{
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}
