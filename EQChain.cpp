#include "EQChain.h"

void EQChain::update(const EQSettings& settings)
{
    // updateLowCutFilters(settings);
    updatePeakFilters(settings);
    // updateHighCutFilters(settings);
}

void EQChain::process(const juce::dsp::ProcessContextReplacing<float> &context)
{
    chain.process(context);
}

void EQChain::prepare(const juce::dsp::ProcessSpec &spec)
{
    sampleRate = spec.sampleRate;
    chain.prepare(spec);
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

