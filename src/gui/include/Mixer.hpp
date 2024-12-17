#ifndef MIXER_HPP
#define MIXER_HPP

#include "imgui.h"

class Mixer
{
public:
    Mixer() = default;
    ~Mixer() = default;

public:
    void SetupMixerChild();

private:
    const ImGuiWindowFlags windowConfiguration = 0
        | ImGuiWindowFlags_NoScrollbar
        ;

    const ImGuiSliderFlags sliderConfiguration = 0
        | ImGuiSliderFlags_Logarithmic
        | ImGuiSliderFlags_ClampOnInput
        | ImGuiSliderFlags_NoInput
        ;

private:
    void PushStyle();
    void PopStyle();
};

#endif //!MIXER_HPP
