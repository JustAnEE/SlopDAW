#ifndef MAINLAYOUT_HPP
#define MAINLAYOUT_HPP

#include "imgui.h"

#include "NavBar.hpp"
#include "FileTree.hpp"
#include "Tracklist.hpp"
#include "Mixer.hpp"

class MainLayout
{
public:
    MainLayout() = default;
    ~MainLayout() = default;

public:
    void SetupMainLayout();

private:
    const ImGuiWindowFlags configuration = 0
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse
        | ImGuiWindowFlags_NoCollapse
        //| ImGuiWindowFlags_NoBackground
        | ImGuiWindowFlags_NoNavInputs
        | ImGuiWindowFlags_NoNav
        ;

    FileTree filetree;
    NavBar nav;
    Tracklist tracklist;
    Mixer mixer;

private:
    void PushStyle();
    void PopStyle();
};

#endif //!MAINLAYOUT_HPP
