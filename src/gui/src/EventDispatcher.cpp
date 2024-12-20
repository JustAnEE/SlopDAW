#include "EventDispatcher.hpp"

MouseEvent EventDispatcher::GetMouseEvent()
{
    int mouseButtonBitmask = 0;
    int modKeyBitmask = 0;

    EventEnum mouseEventType = EventEnum::NONE;
    EventEnum modKeyEventType = EventEnum::NONE;

    /* Note: Only one mouse event type can happen each frame. (I hope) */
    for (ImGuiMouseButton button : this->PolledMouseButtons)
    {
        if( (mouseEventType == EventEnum::NONE || mouseEventType == EventEnum::MOUSE_CLICK)
            && ImGui::IsMouseClicked(button))
        {
            AddToMouseButtonBitmask(mouseButtonBitmask, button);
            mouseEventType = EventEnum::MOUSE_CLICK;
        }

        if ((mouseEventType == EventEnum::NONE || mouseEventType == EventEnum::MOUSE_DRAG)
            && ImGui::IsMouseDragging(button))
        {
            AddToMouseButtonBitmask(mouseButtonBitmask, button);
            mouseEventType = EventEnum::MOUSE_DRAG;
        }

        if ((mouseEventType == EventEnum::NONE || mouseEventType == EventEnum::MOUSE_RELEASE)
            && ImGui::IsMouseReleased(button))
        {
            AddToMouseButtonBitmask(mouseButtonBitmask, button);
            mouseEventType = EventEnum::MOUSE_RELEASE;
        }

        // Must Check MOUSE_DOWN Last...
        if ((mouseEventType == EventEnum::NONE || mouseEventType == EventEnum::MOUSE_DOWN)
            && ImGui::IsMouseDown(button))
        {
            AddToMouseButtonBitmask(mouseButtonBitmask, button);
            mouseEventType = EventEnum::MOUSE_DOWN;
        }
    }

    for (ImGuiKey key : this->PolledModKeys)
    {
        if ((modKeyEventType == EventEnum::NONE || modKeyEventType == EventEnum::KEY_DOWN)
            && ImGui::IsKeyDown(key))
        {
            AddToModKeyBitmask(modKeyBitmask, key);
            modKeyEventType = EventEnum::KEY_DOWN;
        }

        if ((modKeyEventType == EventEnum::NONE || modKeyEventType == EventEnum::KEY_PRESSED)
            && ImGui::IsKeyPressed(key))
        {
            AddToModKeyBitmask(modKeyBitmask, key);
            modKeyEventType = EventEnum::KEY_PRESSED;
        }

        if ((modKeyEventType == EventEnum::NONE || modKeyEventType == EventEnum::KEY_RELEASE)
            && ImGui::IsKeyReleased(key))
        {
            AddToModKeyBitmask(modKeyBitmask, key);
            modKeyEventType = EventEnum::KEY_RELEASE;
        }
    }

    return MouseEvent
    {
        mouseButtonBitmask,
        mouseEventType,
        modKeyBitmask,
        modKeyEventType,
        false,
        this->targetElementId,
        false
    };
}

bool EventDispatcher::GetKeyEventInfo()
{
    // TODO: 
    return false;
}

void EventDispatcher::ReserveNextEventFor(int id)
{
    this->targetElementId = id;
}

void EventDispatcher::AddToMouseButtonBitmask(MouseButtonBitmask &bitmask, ImGuiMouseButton button)
{
    switch (button)
    {
        case ImGuiMouseButton_Left:
            bitmask |= 0b1; break;
        case ImGuiMouseButton_Middle:
            bitmask |= 0b10; break;
        case ImGuiMouseButton_Right:
            bitmask |= 0b100; break;
    }
}

void EventDispatcher::AddToModKeyBitmask(ModKeyBitmask &bitmask, ImGuiKey button)
{
    switch (button)
    {
        case ImGuiKey_RightCtrl:
            bitmask |= 0b1; break;
        case ImGuiKey_RightAlt:
            bitmask |= 0b10; break;
        case ImGuiKey_RightShift:
            bitmask |= 0b100; break;
        case ImGuiKey_LeftCtrl:
            bitmask |= 0b1000; break;
        case ImGuiKey_LeftAlt:
            bitmask |= 0b10000; break;
        case ImGuiKey_LeftSuper:
            bitmask |= 0b100000; break;
    }
}
