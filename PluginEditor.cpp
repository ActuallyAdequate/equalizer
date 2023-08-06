#include "PluginEditor.h"

//==============================================================================
EqualizerAudioEditor::EqualizerAudioEditor (EqualizerAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    addAndMakeVisible(controlSpectrum);

    controlPanels.reserve((PEAKBANDS + 2)); //will need to double

    std::function makeVisible = [this](ControlPanel* cpToVisbilise) {
        
        for(auto& controlPanel : controlPanels) {
            controlPanel->setVisible(false);
        }
        cpToVisbilise->setVisible(true);
    };

   // for(auto channelname : channelNames) { 
        juce::String name = "Left";//channelname.second;
        juce::String lowCutName = name + "-Low";
        juce::String highCutName = name +"-High";
        juce::String lowCutFreq = lowCutName + "-CutFreq";  
        juce::String highCutFreq = highCutName + "CutFreq";
        juce::String highSlope = highCutName + "CutSlope";
        juce::String lowSlope = lowCutName + "CutSlope";
        std::vector<juce::String> idLow{lowCutFreq, lowSlope};
        std::vector<juce::String> idHigh{highCutFreq, highSlope};
        std::unique_ptr controlHigh = std::make_unique<ControlPanel>(idHigh, processorRef.apvts, makeVisible);
        std::unique_ptr controlLow  = std::make_unique<ControlPanel>(idLow, processorRef.apvts, makeVisible);
        addChildComponent(*controlHigh);
        addChildComponent(*controlLow);
        controlSpectrum.registerControlPanel(lowCutName, *controlLow, lowCutFreq, lowSlope);
        controlSpectrum.registerControlPanel(highCutName, *controlHigh, highCutFreq, highSlope);
        controlPanels.push_back(std::move(controlLow));
        controlPanels.push_back(std::move(controlHigh));

        for (int i = 0; i < PEAKBANDS; i++) {
            juce::String peakName = name + "-Peak";
            peakName << i;
            juce::String gain = peakName + "Gain";
            juce::String freq = peakName + "Freq";
            juce::String q = peakName + "Q";
            std::vector<juce::String> idPeak{freq, gain, q};
            std::unique_ptr controlPeak = std::make_unique<ControlPanel>(idPeak, processorRef.apvts, makeVisible);
            addChildComponent(*controlPeak);
            controlSpectrum.registerControlPanel(peakName, *controlPeak, freq, gain);
            controlPanels.push_back(std::move(controlPeak));
           
        }
    // }
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

    for(auto& controlPanel : controlPanels) {
        controlPanel->setBounds(bounds);
    }
}

