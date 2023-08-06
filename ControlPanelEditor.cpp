#include "ControlPanelEditor.h";

ControlPanel::ControlPanel(std::vector<juce::String> paramIDs, APVTS& apvts, std::function<void(ControlPanel*)> onMakeVisible)
: onMakeVisible(onMakeVisible)
{
    int paramCount = paramIDs.size();
    attachments.reserve(paramCount);
    for(int i=0; i < paramCount; i++) {
        std::unique_ptr slider = std::make_unique<juce::Slider>(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextBoxBelow);
        std::unique_ptr attachment = std::make_unique<Attachment>(apvts, paramIDs[i], *slider);
        addAndMakeVisible(*slider);
        attachments.push_back(std::move(attachment));
        sliders.insert({paramIDs[i], std::move(slider)});
    }

}

/// This Function crashes the program lol
juce::Slider& ControlPanel::getSlider(juce::String id)
{
    auto it = sliders.find(id);
        if(it != sliders.end()) {
            return *(it->second);
        }
}

void ControlPanel::showControlPanel()
{
   onMakeVisible(this);
}

void ControlPanel::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::orange);
}

void ControlPanel::resized()
{
    auto amount = getLocalBounds().getWidth() / sliders.size();
     auto totalbounds = getLocalBounds();
    for(auto& slider: sliders) {
        auto bounds = totalbounds.removeFromLeft(amount);
        slider.second->setBounds(bounds);
    }
}
