#pragma once
#include "PluginProcessor.h"


class ControlPanel : public juce::Component {
     using APVTS = juce::AudioProcessorValueTreeState;
        using Attachment = APVTS::SliderAttachment;
    public:
        ControlPanel::ControlPanel(std::vector<juce::String> paramIDs, APVTS& apvts, std::function<void(ControlPanel*)> onMakeVisible);
        juce::Slider& getSlider(juce::String id);
        std::map<juce::String, std::unique_ptr<juce::Slider>> sliders;
        
        void showControlPanel();
    private:
        void paint(juce::Graphics& g) override;
        void resized() override;

        std::function<void(ControlPanel*)> onMakeVisible;
        

       std::vector<std::unique_ptr<Attachment>> attachments;
       

};
