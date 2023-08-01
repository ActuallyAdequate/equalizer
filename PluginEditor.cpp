#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EqualizerAudioEditor::EqualizerAudioEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    addAndMakeVisible(controlSpectrum);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    setResizable(true, true);
}

EqualizerAudioEditor::~EqualizerAudioEditor()
{
    
}

//==============================================================================
void EqualizerAudioEditor::paint (juce::Graphics& g)
{
     using namespace juce;
    g.fillAll(Colours::grey);
}

void EqualizerAudioEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    auto spectrumControlArea = bounds.removeFromTop(bounds.getHeight() * 0.66);
    controlSpectrum.setBounds(spectrumControlArea);
}

