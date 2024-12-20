#ifndef TRACKLIST_HPP
#define TRACKLIST_HPP

#include <format>
#include <string>

#include "imgui.h"
#include "MouseEvent.hpp"

class Tracklist
{
public:
    Tracklist() = default;
    ~Tracklist() = default;

public:
    void SetupTracklistChild();

    MouseEvent SendMouseEvent(MouseEvent e);

private:
    const ImGuiWindowFlags windowConfiguration = 0;
    const ImGuiChildFlags childConfiguration = 0;

    ImVec2 posOffset = ImVec2(0, 0);

    bool isItemSelected = false;
    bool isInitalized = false;

private:
    void OnInitialization(ImVec2 initPos);

    // UI IO METHODS
    void HandleMouseClick(MouseEvent e);
    void HandleMouseDrag(MouseEvent e);
    void HandleMouseRelease(MouseEvent e);
    void HandleMouseScroll(MouseEvent e);

    // UI RENDER METHODS
    void PushStyle();
    void PopStyle();

    void RenderGrid(ImVec2 origin, ImVec2 size);
    void RenderTractData();

    void RenderTracklist();
};

#endif //!TRACKLIST_HPP
