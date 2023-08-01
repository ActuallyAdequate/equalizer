#pragma once
#include "PluginProcessor.h"



class ControlSpectrum : public juce::Component{
    public:

        class Thumb : public juce::Component {
            public:
                Thumb::Thumb();
                void mouseDown(const juce::MouseEvent& event) override;
                void mouseDrag(const juce::MouseEvent& event) override;
            private:
                juce::ComponentDragger dragger;
                juce::ComponentBoundsConstrainer constrainer;

                void paint(juce::Graphics& g) override;
                void resized() override;
        };


        ControlSpectrum::ControlSpectrum();
        static const int thumbsize = 20;
    private:
        void paint(juce::Graphics& g) override;
        void resized() override;

        Thumb thumb;
};

