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
    const ImGuiWindowFlags windowConfiguration = 0;

    const ImGuiChildFlags childConfiguration = 0;

private:
    void PushStyle();
    void PopStyle();
    void ActivateTree(const char* name, void* options);
};

#endif //!FILETREE_HPP
