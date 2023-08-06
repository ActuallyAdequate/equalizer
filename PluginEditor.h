#pragma once

#include "PluginProcessor.h"
#include "ControlSpectrumEditor.h"



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
    std::vector<std::unique_ptr<ControlPanel>>  controlPanels;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EqualizerAudioEditor)
};
