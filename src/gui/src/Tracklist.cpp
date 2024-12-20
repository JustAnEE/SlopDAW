#include "Tracklist.hpp"

void Tracklist::SetupTracklistChild()
{
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();
    ImVec2 size = ImVec2(availableSpace.x * 1.0f, availableSpace.y * 0.75f);

    this->PushStyle();
    ImGui::BeginChild("Tracklist", size, this->childConfiguration, this->windowConfiguration);
        if(!this->isInitalized)
        {
            this->OnInitialization(ImVec2(0, 0));
        }

        this->RenderTracklist();

    ImGui::EndChild();
    this->PopStyle();
}

MouseEvent Tracklist::SendMouseEvent(MouseEvent e)
{
    // Propagate to TrackData

    if (e.targetElementId == 0 && !e.stopPropagation && e.mouseEventType == EventEnum::MOUSE_CLICK)
    {
        this->HandleMouseClick(e);
    }
    if ((e.targetElementId == 0 || e.targetElementId == 1) // TODO: Refactor Elements base classes
        && !e.stopPropagation
        && e.mouseEventType == EventEnum::MOUSE_DRAG)
    {
        this->HandleMouseDrag(e);
    }
    
    //if (e.targetElementId == 0 && !e.stopPropagation&& e.mouseEventType == EventEnum::SCROLL)
    //{
    //    this->HandleMouseScroll();
    //}

    return e;
}

void Tracklist::OnInitialization(ImVec2 initPos)
{
    isInitalized = true;
    this->posOffset = initPos;
}

void Tracklist::HandleMouseClick(MouseEvent e)
{
    // TODO:
}

void Tracklist::HandleMouseDrag(MouseEvent e)
{
    ImVec2 windowPos = ImGui::GetWindowPos();
    float sensitivity = -1.0f;

    // Persistant Event.
    e.targetElementId = 1;

    // Place Pattern in Grid
    if (e.mouseButtonBitmask & 0b100) // Right Mouse
    {
        // TODO:
    }

    // Move Around Grid
    if (e.mouseButtonBitmask & 0b1) // Left Mouse
    {
        ImVec2 dragDelta = ImGui::GetMouseDragDelta(); // Add to event.
        float x = std::max(0.0f, this->posOffset.x + (dragDelta.x * sensitivity));
        float y = std::max(0.0f, this->posOffset.y + (dragDelta.y * sensitivity));

        this->posOffset = ImVec2(x, y);
        ImGui::ResetMouseDragDelta(); // Add flag to event.
    }
}

void Tracklist::HandleMouseRelease(MouseEvent e)
{
    e.targetElementId = 0;
}

void Tracklist::HandleMouseScroll(MouseEvent e)
{
    // TODO:
    ImGuiIO& io = ImGui::GetIO();
    bool isZoomingIn = io.MouseWheel > 0.0f;
    bool isZoomingOut = io.MouseWheel < 0.0f;

    // Vertical Zoom in
    if (ImGui::IsKeyDown(ImGuiKey_LeftShift) && isZoomingIn)
    {

    }

    // VerticalZoom out
    if (ImGui::IsKeyDown(ImGuiKey_LeftShift) && !isZoomingOut)
    {

    }

    // Horizontal Zoom in
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && isZoomingIn)
    {

    }

    // Horizontal out
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) && !isZoomingOut)
    {

    }
}

void Tracklist::PushStyle() /* private */
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
}

void Tracklist::PopStyle() /* private */
{
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void Tracklist::RenderGrid(ImVec2 origin, ImVec2 size)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    // temp
    int trackCount = 50;
    int barCount = 4;
    int beatsPerBar = 4;

    float labelWidthOffset = 100.0f;
    float barNumberHeightOffset = 20.0f;
    float trackHeight = 50.0f;

    float barTotalWidth = (size.x - labelWidthOffset);
    float barLength = barTotalWidth / barCount;
    float beatOffset = barLength / beatsPerBar;

    float borderLineThickness = 3.0f;

    ImVec2 usersGridOffset = ImVec2(this->posOffset.x + labelWidthOffset, this->posOffset.y);

    ImU32 black = IM_COL32(10, 10, 10, 255);
    ImU32 darkGrey = IM_COL32(77, 77, 77, 255);

    ImU32 oceanBlue = IM_COL32(100, 151, 177, 255);
    ImU32 stoneBlue = IM_COL32(149, 175, 194, 255);

    // Bar Sections
    for (int i = 0; i < 4; i++)
    {
        ImU32 color = i % 2 == 0 ? oceanBlue : stoneBlue;

        int bar = i * 4;

        std::string str = std::format("{}", bar);
        const char* cstr = str.c_str();
        ImVec2 textSize = ImGui::CalcTextSize(cstr);

        float x1 = std::max(origin.x + labelWidthOffset, origin.x + labelWidthOffset + (barLength * i) - this->posOffset.x);
        float y1 = origin.y + barNumberHeightOffset;

        float x2 = origin.x + labelWidthOffset + (barLength * (i + 1)) - this->posOffset.x;
        float y2 = origin.y + size.y;

        float tx = origin.x + labelWidthOffset + (barLength * i) - this->posOffset.x - textSize.x / 2.0f;
        float ty = y1 - textSize.y - 2.0f;

        if(x2 > origin.x + labelWidthOffset)
        {
            drawList->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), color);
        }

        if(tx > origin.x + labelWidthOffset - textSize.x)
        {
            drawList->AddText(ImVec2(tx, ty), black, cstr);
        }
    }

    // Window Borders
    drawList->AddLine(ImVec2(origin.x, origin.y),                   ImVec2(origin.x + size.x, origin.y),          black, borderLineThickness);
    drawList->AddLine(ImVec2(origin.x + size.x, origin.y),          ImVec2(origin.x + size.x, origin.y + size.y), black, borderLineThickness);
    drawList->AddLine(ImVec2(origin.x + size.x, origin.y + size.y), ImVec2(origin.x, origin.y + size.y),          black, borderLineThickness);
    drawList->AddLine(ImVec2(origin.x, origin.y + size.y),          ImVec2(origin.x, origin.y),                   black, borderLineThickness);

    // Grid Borders
    drawList->AddLine(ImVec2(origin.x, origin.y + barNumberHeightOffset),                    ImVec2(origin.x + labelWidthOffset + barTotalWidth, origin.y + barNumberHeightOffset), black, borderLineThickness);
    drawList->AddLine(ImVec2(origin.x + labelWidthOffset, origin.y + barNumberHeightOffset), ImVec2(origin.x + labelWidthOffset, origin.y + size.y),                                black, borderLineThickness);

    // Track Lines and Labels
    for(int i = 0; i <= trackCount; i ++)
    {
        std::string str = std::format("Track {}", i);
        const char* cstr = str.c_str();
        ImVec2 textSize = ImGui::CalcTextSize(cstr);

        float x1 = origin.x;
        float x2 = origin.x + labelWidthOffset + barTotalWidth;

        float y = origin.y + barNumberHeightOffset + (trackHeight * (i + 1)) - this->posOffset.y;

        float tx = x1 + textSize.x / 2.0f;
        float ty = y - textSize.y - 2.0f;

        if (y > origin.y + barNumberHeightOffset + borderLineThickness)
        {
            drawList->AddLine(ImVec2(x1, y), ImVec2(x2, y), black, borderLineThickness);
        }

        if(y > origin.y + barNumberHeightOffset + textSize.y)
        {
            drawList->AddText(ImVec2(tx, ty), black, cstr);
        }
    }

    // Beat Lines
    for (int i = 0; i <= barCount * beatsPerBar; i++)
    {
        ImU32 color = (i % 4 == 0) ? black : darkGrey;
        float thickness = (i % 4 == 0) ? borderLineThickness : 1.0f;

        float x = origin.x + labelWidthOffset + (beatOffset * i) - this->posOffset.x;

        float y1 = origin.y + barNumberHeightOffset;
        float y2 = origin.y + size.y;

        if (x > origin.x + labelWidthOffset + borderLineThickness)
        {
            drawList->AddLine(ImVec2(x, y1), ImVec2(x, y2), color, thickness);
        }
    }
}

void Tracklist::RenderTractData()
{
    // Label

    // Data
}

void Tracklist::RenderTracklist()
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    this->RenderGrid(ImGui::GetWindowPos(), ImGui::GetWindowSize());
    this->RenderTractData();
}
