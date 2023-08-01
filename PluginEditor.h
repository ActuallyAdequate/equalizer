#pragma once

#include "PluginProcessor.h"
#include "ControlSpectrumEditor.h"




// class ControlPanel : juce::Component {
//  public:
//     private:
//         void paint(juce::Graphics& g) override;
//         void resized() override;
// };



//==============================================================================
class EqualizerAudioEditor  : public juce::AudioProcessorEditor
{
public:
    explicit EqualizerAudioEditor (EqualizerAudioProcessor&);
    ~EqualizerAudioEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EqualizerAudioProcessor& processorRef;

    ControlSpectrum controlSpectrum;
   // ControlPanel controlPanel;
    // std::vector<ControlPanel> controlPanels[7];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioEditor)
};
