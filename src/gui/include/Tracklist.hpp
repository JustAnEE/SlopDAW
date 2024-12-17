#ifndef TRACKLIST_HPP
#define TRACKLIST_HPP

#include "imgui.h"

class Tracklist
{
public:
    Tracklist() = default;
    ~Tracklist() = default;

public:
    void SetupTracklistChild();

private:
    const ImGuiWindowFlags windowConfiguration = 0;

    const ImGuiChildFlags childConfiguration = 0;

private:
    void PushStyle();
    void PopStyle();
};

#endif //!TRACKLIST_HPP
