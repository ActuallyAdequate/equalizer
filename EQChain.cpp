#include "EQChain.h"

void EQChain::update(EQChainSettings &settings)
{
    updateLowCutFilters(settings);
    updatePeakFilters(settings);
    updateHighCutFilters(settings);
}