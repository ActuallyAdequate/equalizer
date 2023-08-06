#pragma once
#include "PluginProcessor.h"
#include "ControlPanelEditor.h"

class ControlSpectrum : public juce::Component{
    public:
        
        class Thumb : public juce::Component, public juce::Slider::Listener {
            public:
                Thumb::Thumb(juce::String id, std::function<void(juce::String)> onSignalControlPanel, std::function<void(juce::Point<double>)> onMove,   std::function<void(Thumb* thumbptr)> onSliderValueChange);
                void mouseDown(const juce::MouseEvent& event) override;
                void mouseDrag(const juce::MouseEvent& event) override;
                void forceMoveUpdate();
            private:
                juce::String id;
                juce::ComponentDragger dragger;
                juce::ComponentBoundsConstrainer constrainer;
                std::function<void(juce::String)> onSignalControlPanel;
                std::function<void(juce::Point<double>)> onMove;
                std::function<void(Thumb* thumbptr)> onSliderValueChange;

                void sliderValueChanged(juce::Slider* slider);

                void paint(juce::Graphics& g) override;
                void resized() override;
        };

        void registerControlPanel(juce::String controlId, ControlPanel& controlPanel, juce::String sliderXId, juce::String sliderYId);

        ControlSpectrum::ControlSpectrum();
        static const int thumbsize = 20;
    private:
        void paint(juce::Graphics& g) override;
        void resized() override;

        std::map<juce::String, std::unique_ptr<Thumb>> thumbs;
        std::map<juce::String, ControlPanel*> controlPanels;
};

