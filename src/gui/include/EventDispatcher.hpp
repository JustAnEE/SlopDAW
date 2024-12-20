#ifndef EVENTDISPATCHER_HPP
#define EVENTDISPATCHER_HPP

#include "imgui.h"

#include "MouseEvent.hpp"
#include "MouseEventEnum.hpp"
#include "EventEnum.hpp"

typedef int MouseButtonBitmask;
typedef int ModKeyBitmask;

/* ~~~~~ MouseButtonBitmask ~~~~~
 * ZEROS = NULL
 * 1st bit = LEFT MOUSE
 * 2nd bit = MIDDLE MOUSE
 * 3rd bit = RIGHT MOUSE
 * 4th bit = NOTHING....
 * 5th bit = NOTHING....
 *      etc...
*/

/* ~~~~~ ModKeyBitmask ~~~~~
 * ZEROS = NULL
 * 1st bit = RIGHT SHIFT
 * 2nd bit = RIGHT ALT
 * 3rd bit = RIGHT CTRL
 * 4th bit = LEFT SHIFT
 * 5th bit = LEFT ALT
 * 6th bit = LEFT CTRL
 *      etc...
*/

class EventDispatcher
{
public:
    EventDispatcher() = default;
    ~EventDispatcher() = default;

public:
    MouseEvent GetMouseEvent();

    bool GetKeyEventInfo();

    void ReserveNextEventFor(int id);

private:
    int targetElementId = 0; // NO-ONE

    ImGuiMouseButton PolledMouseButtons[3]
    {
        ImGuiMouseButton_Left,
        ImGuiMouseButton_Middle,
        ImGuiMouseButton_Right
    };

    ImGuiKey PolledModKeys[6]
    {
        ImGuiKey_RightCtrl,
        ImGuiKey_RightAlt,
        ImGuiKey_RightShift,
        ImGuiKey_LeftCtrl,
        ImGuiKey_LeftAlt,
        ImGuiKey_LeftSuper
    };

private:
    void AddToMouseButtonBitmask(MouseButtonBitmask &bitmask, ImGuiMouseButton button);

    void AddToModKeyBitmask(ModKeyBitmask &bitmask, ImGuiKey button);
};

#endif //!EVENTDISPATCHER
