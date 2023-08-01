#include "EQChain.h"

void EQChain::update(EQSettings& settings)
{
    // updateLowCutFilters(settings);
    // updatePeakFilters(settings);
    // updateHighCutFilters(settings);
}

void EQChain::process(const juce::dsp::ProcessContextReplacing<float> &context)
{
    chain.process(context);
}

void EQChain::prepare(const juce::dsp::ProcessSpec &spec)
{
    chain.prepare(spec);
}
