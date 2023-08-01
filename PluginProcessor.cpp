#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
EqualizerAudioProcessor::EqualizerAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
}

EqualizerAudioProcessor::~EqualizerAudioProcessor()
{
}

#pragma region Attirbutes
const juce::String EqualizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EqualizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EqualizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EqualizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EqualizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EqualizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EqualizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EqualizerAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String EqualizerAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void EqualizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

#pragma endregion

//==============================================================================
void EqualizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void EqualizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool EqualizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void EqualizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                             juce::MidiBuffer& midiMessages)
{
    
}

//==============================================================================
bool EqualizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EqualizerAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
    //return new EqualizerAudioEditor (*this);
}

//==============================================================================
void EqualizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void EqualizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//============================================================================================

juce::AudioProcessorValueTreeState::ParameterLayout EqualizerAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    

    for(auto channelname : channelNames) { 
        auto name = channelname.second;
        juce::String lowCutFreq = name + "-LowCutFreq";  
        juce::String highCutFreq = name + "-HighCutFreq";  
        layout.add(std::make_unique<juce::AudioParameterFloat>(lowCutFreq,lowCutFreq, juce::NormalisableRange<float>(20.0f, 20000.0f, 1.f, 0.25f),20.f));
        layout.add(std::make_unique<juce::AudioParameterFloat>(highCutFreq,highCutFreq, juce::NormalisableRange<float>(20.0f, 20000.0f, 1.f, 0.25f),20000.f));

        for (int i = 0; i < PEAKBANDS; i++) {
            juce::String peakName = name + "-Peak";
            peakName << i;
            juce::String gain = peakName + "Gain";
            juce::String freq = peakName + "Freq";
            juce::String q = peakName + "Q";      
            layout.add(std::make_unique<juce::AudioParameterFloat>(gain,gain, juce::NormalisableRange<float>(-24.0f, 24.0f, 0.5f, 1.f), 0.0f));
            layout.add(std::make_unique<juce::AudioParameterFloat>(freq,freq, juce::NormalisableRange<float>(20.0f, 20000.0f, 1.f, 0.25f), 250.f * i * i + 250.f));
            layout.add(std::make_unique<juce::AudioParameterFloat>(q,q, juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f), 1.f));
        }
   
        juce::StringArray stringArray;
        for (int i= 0; i<4; ++i){
            juce::String str;
            str << (12+ i * 12);
            str << "db/Oct";
            stringArray.add(str);
        }

        juce::String highSlope = name + "-HighCutSlope";
        juce::String lowSlope = name + "-LowCutSlope";
        layout.add(std::make_unique<juce::AudioParameterChoice>(lowSlope, lowSlope, stringArray, 0));
        layout.add(std::make_unique<juce::AudioParameterChoice>(highSlope, highSlope, stringArray, 0));
    }
    
    return layout;
}

ChainSettings EqualizerAudioProcessor::loadChainSettings()
{
    ChainSettings settings;
    for (auto channelname : channelNames) {
        juce::String name = channelname.second;
        EQSettings eqSettings;

        juce::String lowCutFreq = name + "-LowCutFreq";  
        juce::String highCutFreq = name + "-HighCutFreq"; 
        eqSettings.highCutFreq = apvts.getRawParameterValue(highCutFreq)->load();
        eqSettings.lowCutFreq = apvts.getRawParameterValue(lowCutFreq)->load();
        juce::String highSlope = name + "-HighCutSlope";
        juce::String lowSlope = name + "-LowCutSlope";   
        eqSettings.lowCutSlope = static_cast<Slope>(apvts.getRawParameterValue(lowSlope)->load());
        eqSettings.highCutSlope = static_cast<Slope>(apvts.getRawParameterValue(highSlope)->load());

        for (int i = 0; i < PEAKBANDS; i++) {
            PeakSettings peakSettings;

            juce::String peakName = name + "-Peak";
            peakName << i;
            juce::String gain = peakName + "Gain";
            juce::String freq = peakName + "Freq";
            juce::String q = peakName + "Q";

            peakSettings.peakFreq = apvts.getRawParameterValue(freq)->load();
            peakSettings.peakGainDecibels = apvts.getRawParameterValue(gain)->load();
            peakSettings.peakQuality = apvts.getRawParameterValue(q)->load();

            eqSettings.peakSettings[i] = peakSettings;

        }

        settings.channelEQSettings[channelname.first] = eqSettings;
    }


    

    return settings;
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EqualizerAudioProcessor();
}
