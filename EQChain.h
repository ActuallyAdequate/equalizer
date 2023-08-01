#pragma once

#include <juce_dsp/juce_dsp.h>


//using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>; //Low CUt Peak High Cut

const  int PEAKBANDS = 5;

using Filter = juce::dsp::IIR::Filter<float> ;   
using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
using Coefficients =Filter::CoefficientsPtr;
using Chain = juce::dsp::ProcessorChain<CutFilter, Filter, Filter, Filter, Filter, Filter, CutFilter>;

enum Slope
{
    Slope_12,
    Slope_24,
    Slope_36,
    Slope_48
};


struct PeakSettings {
    float peakFreq {0}, peakGainDecibels{0}, peakQuality {1.f};
};

struct EQSettings {
    PeakSettings peakSettings[5];
    float lowCutFreq{0}, highCutFreq{0};
    Slope lowCutSlope {Slope::Slope_12}, highCutSlope {Slope::Slope_12};
};

inline void updateCoefficients(Coefficients& old, const Coefficients& replacements){
    *old = *replacements;
};

// this will update coefficients and then ensure we a re not bypassing hte filter (used for the cut filters, which have 4 filters)
template<int Index, typename ChainType, typename CoefficientType>
inline void updateCoefficientsUnBypass(ChainType& chain, const CoefficientType coefficients){
    updateCoefficients(chain.template get<Index>().coefficients, coefficients[Index]);
    chain.template setBypassed<Index>(false);
};

inline Coefficients makePeakFilter(const PeakSettings& chainSettings, double sampleRate) {
    return juce::dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, chainSettings.peakFreq, chainSettings.peakQuality,juce::Decibels::decibelsToGain(chainSettings.peakGainDecibels));
};

inline auto makeLowCutFilter(const EQSettings& chainSettings, double sampleRate) {
    return juce::dsp::FilterDesign<float>::designIIRHighpassHighOrderButterworthMethod(chainSettings.lowCutFreq, sampleRate, (chainSettings.lowCutSlope+1)*2);
};

inline auto makeHighCutFilter(const EQSettings& chainSettings, double sampleRate) {
   return juce::dsp::FilterDesign<float>::designIIRLowpassHighOrderButterworthMethod(chainSettings.highCutFreq, sampleRate, (chainSettings.highCutSlope+1)*2);
};



class EQChain {
    public:
        void process(const juce::dsp::ProcessContextReplacing<float> &context);
        void prepare(const juce::dsp::ProcessSpec &spec);
        void update(const EQSettings& settings);
    private:
        Chain chain;
        double sampleRate;

        void updatePeakFilters(const EQSettings &settings);
        void updateLowCutFilters(const EQSettings &settings);
        void updateHighCutFilters(const EQSettings &settings);

        template<typename ChainType, typename CoefficientType>
        void updateCutFilters(ChainType& chain, const CoefficientType& coefficients, const Slope& slope);
 
};