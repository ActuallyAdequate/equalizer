#include "ControlSpectrumEditor.h"

ControlSpectrum::Thumb::Thumb(juce::String id, std::function<void(juce::String)> onSignalControlPanel, std::function<void(juce::Point<double>)> onMove,   std::function<void(Thumb* thumbptr)> onSliderValueChange) : 
id(id), onSignalControlPanel(onSignalControlPanel), onMove(onMove), onSliderValueChange(onSliderValueChange)
{
    constrainer.setMinimumOnscreenAmounts(thumbsize, thumbsize, thumbsize, thumbsize);
}

void ControlSpectrum::Thumb::mouseDown(const juce::MouseEvent &event)
{
    onSignalControlPanel(id);
    dragger.startDraggingComponent(this, event);
}

void ControlSpectrum::Thumb::mouseDrag(const juce::MouseEvent &event)
{
    dragger.dragComponent(this, event, &constrainer);
    onMove(getPosition().toDouble());
}

void ControlSpectrum::Thumb::forceMoveUpdate()
{
    onSliderValueChange(this);
}

void ControlSpectrum::Thumb::sliderValueChanged(juce::Slider *slider)
{
    if(isMouseOverOrDragging(false)) return;
    onSliderValueChange(this);
   
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

void ControlSpectrum::registerControlPanel(juce::String controlId, ControlPanel& controlPanel, juce::String sliderXId, juce::String sliderYId)
{
    juce::Slider& sX = controlPanel.getSlider(sliderXId);
    juce::Slider& sY = controlPanel.getSlider(sliderYId);

    // Change Slider Value when the thumb moves
    std::function<void(juce::Point<double>)> csv = [&](juce::Point<double> point) {
        const auto bounds = getLocalBounds().toDouble();
        const auto w = static_cast<double>(thumbsize);
        sX.setValue(juce::jmap(point.getX(), 0.0, bounds.getWidth()-w, sX.getMinimum(), sX.getMaximum() ));
        sY.setValue(juce::jmap(point.getY(), 0.0, bounds.getHeight()-w, sY.getMinimum(), sY.getMaximum() ));
    } ;  

    // Change Thumb Position when the slider value changes.
    std::function<void(Thumb*)> ctp = [&](Thumb* thumbptr) {
        const auto bounds = getLocalBounds().toDouble();
        const auto w = static_cast<double>(thumbsize);
        auto xPos = juce::jmap(sX.getValue(), sX.getMinimum(), sX.getMaximum(), 0.0, bounds.getWidth()-w);
        auto yPos = juce::jmap(sY.getValue(), sY.getMinimum(), sY.getMaximum(), 0.0, bounds.getHeight()-w);
        thumbptr->setTopLeftPosition(static_cast<int>(xPos), static_cast<int>(yPos));
        repaint();
    };

    //SIgnal Control Panel that this thumb is activated
    std::function<void(juce::String)> scp = [this](juce::String s) {
        auto it = controlPanels.find(s);
        if(it != controlPanels.end()) {
            it->second->showControlPanel();
        }
    
    };

    std::unique_ptr thumb = std::make_unique<Thumb>(controlId, scp, csv, ctp);
    sX.addListener(thumb.get());
    sY.addListener(thumb.get());

    addAndMakeVisible(*thumb);
    thumbs.insert({controlId, std::move(thumb)});
    controlPanels.insert({controlId, &controlPanel});

   
}

ControlSpectrum::ControlSpectrum()
{

}

void ControlSpectrum::paint(juce::Graphics &g)
{
    using namespace juce;
    g.fillAll(Colours::black);
}

void ControlSpectrum::resized()
{
  for(auto& thumbcontrol : thumbs) {
      thumbcontrol.second->setBounds(getLocalBounds().withSizeKeepingCentre(thumbsize, thumbsize));
      thumbcontrol.second->forceMoveUpdate();
  }
}
