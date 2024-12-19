#ifndef NAVBAR_HPP
#define NAVBAR_HPP

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GlfwApi.hpp"

class NavBar
{
public:
    NavBar() = default;
    ~NavBar() = default;

public:
    void SetupNavBarChild();

private:
    const ImGuiWindowFlags windowConfiguration = 0
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse
        ;

    const ImGuiChildFlags childConfiguration = 0
        //| ImGuiChildFlags_AlwaysAutoResize
        ;

    const ImGuiTableFlags tableConfiguration = 0
        | ImGuiTableFlags_BordersInnerV
        //| ImGuiTableFlags_PadOuterX
        //| ImGuiTableFlags_NoPadInnerX
        | ImGuiTableFlags_SizingStretchProp
        //| ImGuiTableFlags_
        //| ImGuiTableFlags_
        //| ImGuiTableFlags_
        //| ImGuiTableFlags_
        //| ImGuiTableFlags_
        ;

private:
    void PushStyle();
    void PopStyle();
};

#endif //!NAVBAR_HPP
