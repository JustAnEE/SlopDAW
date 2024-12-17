#ifndef FILETREE_HPP
#define FILETREE_HPP

#include "imgui.h"

class FileTree
{
public:
    FileTree() = default;
    ~FileTree() = default;

public:
    void SetupFileTreeChild();

private:
    const ImGuiWindowFlags configuration = 0;

private:
    void PushStyle();
    void PopStyle();
};

#endif //!FILETREE_HPP
