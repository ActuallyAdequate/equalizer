#include "EQChain.h"


void EQChain::prepare(const juce::dsp::ProcessSpec &spec)
{
    sampleRate = spec.sampleRate;
    chain.prepare(spec);
}

void EQChain::process(const juce::dsp::ProcessContextReplacing<float> &context)
{
    chain.process(context);
}


void EQChain::update(const EQSettings& settings)
{
    updateLowCutFilters(settings);
    updatePeakFilters(settings);
    updateHighCutFilters(settings);
}

void EQChain::updatePeakFilters(const EQSettings &settings){

    Filter* peakFilters[5] { //have to do it this way because get index is a compile time setting
        &chain.get<1>(),
        &chain.get<2>(),
        &chain.get<3>(),
        &chain.get<4>(),
        &chain.get<5>()
    };

    for(int i=0; i< PEAKBANDS; i++) {
         auto peakCoefficients = makePeakFilter(settings.peakSettings[i], sampleRate);
         updateCoefficients(peakFilters[i]->coefficients, peakCoefficients);
    }
}

void EQChain::updateLowCutFilters(const EQSettings& cutSettings){
    auto lowCutCoefficients = makeLowCutFilter(cutSettings, sampleRate);
    auto& lowCut = chain.get<0>();
    updateCutFilters(lowCut, lowCutCoefficients, cutSettings.lowCutSlope);

}

void EQChain::updateHighCutFilters(const EQSettings& cutSettings){
    auto highCutCoefficients = makeHighCutFilter(cutSettings, sampleRate);
    auto& highCut = chain.get<6>();
    updateCutFilters(highCut, highCutCoefficients, cutSettings.highCutSlope);

}

template<typename ChainType, typename CoefficientType>
void EQChain::updateCutFilters(ChainType& chain, const CoefficientType& coefficients, const Slope& slope){
    chain.template setBypassed<0>(true);
    chain.template setBypassed<1>(true);
    chain.template setBypassed<2>(true);
    chain.template setBypassed<3>(true);

    switch(slope) {
        case Slope_48:
            updateCoefficientsUnBypass<3>(chain, coefficients);
        case Slope_36:
            updateCoefficientsUnBypass<2>(chain, coefficients);
        case Slope_24:
            updateCoefficientsUnBypass<1>(chain, coefficients);
        case Slope_12:
            updateCoefficientsUnBypass<0>(chain, coefficients);
    }
}

