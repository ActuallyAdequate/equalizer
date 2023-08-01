#include "juce_dsp/juce_dsp.h"


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

class EQChain {
    public:
        void update(EQSettings& settings);
    private:
        Chain chain;
};