#include "ControlSpectrumEditor.h"

ControlSpectrum::Thumb::Thumb()
{
    constrainer.setMinimumOnscreenAmounts(thumbsize, thumbsize, thumbsize, thumbsize);
}

void ControlSpectrum::Thumb::mouseDown(const juce::MouseEvent &event)
{
    dragger.startDraggingComponent(this, event);
}

void ControlSpectrum::Thumb::mouseDrag(const juce::MouseEvent &event)
{
    dragger.dragComponent(this, event, &constrainer);
}

void ControlSpectrum::Thumb::paint(juce::Graphics &g)
{
    using namespace juce;
    g.setColour(Colours::white);
    g.fillEllipse(getLocalBounds().toFloat());
}

void ControlSpectrum::Thumb::resized()
{

}

ControlSpectrum::ControlSpectrum()
{
    addAndMakeVisible(thumb);
}

void ControlSpectrum::paint(juce::Graphics &g)
{
    using namespace juce;
    g.fillAll(Colours::black);
}

void ControlSpectrum::resized()
{
    thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbsize, thumbsize));
}
