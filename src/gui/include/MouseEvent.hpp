#ifndef MOUSEEVENT_HPP
#define MOUSEEVENT_HPP

#include "EventEnum.hpp"

struct MouseEvent
{
public:
    int mouseButtonBitmask = 0;
    EventEnum mouseEventType = EventEnum::NONE;

    int modKeyBitmask = 0;
    EventEnum modEventType = EventEnum::NONE;

    bool stopPropigation = false;

    // Only set for drag events.
    int targetElementId = 0;
    bool stopPropagation = false;
};

#endif //!MOUSEEVENT_HPP
