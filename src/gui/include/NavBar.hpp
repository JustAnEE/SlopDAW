#ifndef NAVBAR_HPP
#define NAVBAR_HPP

#include "imgui.h"

class NavBar
{
public:
    NavBar() = default;
    ~NavBar() = default;

public:
    void SetupNavBarChild();

private:
    const ImGuiWindowFlags configuration = 0;

private:
    void PushStyle();
    void PopStyle();
};

#endif //!NAVBAR_HPP
