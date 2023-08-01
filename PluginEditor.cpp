#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EqualizerAudioEditor::EqualizerAudioEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
}

EqualizerAudioEditor::~EqualizerAudioEditor()
{
}

//==============================================================================
void EqualizerAudioEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   // fill the whole window white
    g.fillAll (juce::Colours::white);
 
    // set the current drawing colour to black
    g.setColour (juce::Colours::black);
 
    // set the font size and draw text to the screen
    g.setFont (15.0f);
}

void EqualizerAudioEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

