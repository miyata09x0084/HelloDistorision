/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistorsionAudioProcessorEditor::DistorsionAudioProcessorEditor (DistorsionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    Gain.setSliderStyle(juce::Slider::LinearBarVertical);
    Gain.setRange(0, 1);
    Gain.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    Gain.setValue(0.708);
    
    Threshold.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    Threshold.setRange(0, 1);
    Threshold.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    Threshold.setValue(1);
    
    Volume.setSliderStyle(juce::Slider::LinearVertical);
    Volume.setRange(0, 1);
    Volume.setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);
    Volume.setValue(0.708);
    
    GainLabel.setFont(juce::Font(13.00f, juce::Font::plain));
    GainLabel.setJustificationType(juce::Justification::centredTop);
    GainLabel.setEditable(false, false, false);
    GainLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    GainLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    GainLabel.setColour(juce::Label::backgroundColourId, juce::Colour(0x00000000));
    GainLabel.setText("Gain\n", juce::dontSendNotification);
    
    ThresholdLabel.setFont(juce::Font(13.00f, juce::Font::plain));
    ThresholdLabel.setJustificationType(juce::Justification::centredTop);
    ThresholdLabel.setEditable(false, false, false);
    ThresholdLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    ThresholdLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    ThresholdLabel.setColour(juce::Label::backgroundColourId, juce::Colour(0x00000000));
    ThresholdLabel.setText("Threshold\n", juce::dontSendNotification);
    
    VolumeLabel.setFont(juce::Font(13.00f, juce::Font::plain));
    VolumeLabel.setJustificationType(juce::Justification::centredTop);
    VolumeLabel.setEditable(false, false, false);
    VolumeLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    VolumeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    VolumeLabel.setColour(juce::Label::backgroundColourId, juce::Colour(0x00000000));
    VolumeLabel.setText("Volume\n", juce::dontSendNotification);
    
    Bypass.setButtonText("Bypass");
    Bypass.setColour(juce::ToggleButton::textColourId, juce::Colours::blue);
    Bypass.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::blue);
    Bypass.setColour(juce::ToggleButton::tickColourId, juce::Colours::blue);
    
    addAndMakeVisible(&Gain);
    addAndMakeVisible(&Threshold);
    addAndMakeVisible(&Volume);

    addAndMakeVisible(&GainLabel);
    addAndMakeVisible(&ThresholdLabel);
    addAndMakeVisible(&VolumeLabel);
    
    addAndMakeVisible(&Bypass);
    
    Gain.addListener(this);
    Threshold.addListener(this);
    Volume.addListener(this);
    Bypass.addListener(this);
}

DistorsionAudioProcessorEditor::~DistorsionAudioProcessorEditor()
{
}

//==============================================================================
void DistorsionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    juce::Image image_bg = juce::ImageCache::getFromMemory(BinaryData::P4284097_JPG,BinaryData::P4284097_JPGSize);
    g.drawImageWithin(image_bg, 0, 0, 400, 300, juce::RectanglePlacement::centred, false);

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DistorsionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    Gain.setBounds(40, 30, 60, 150);
    Threshold.setBounds(140, 30, 120, 150);
    Volume.setBounds(300, 30, 60, 150);
    Bypass.setBounds(getWidth()*0.2f, getHeight() - 60, getWidth()*0.6f, 30);

    GainLabel.setBounds(40, 190, 60, 30);
    ThresholdLabel.setBounds(140, 190, 120, 30);
    VolumeLabel.setBounds(300, 190, 60, 30);
}

void DistorsionAudioProcessorEditor::sliderValueChanged(juce::Slider *changedSlider)
{
    if (changedSlider == &Gain)
    {
        processor.setParameterNotifyingHost(DistorsionAudioProcessor::Gain, Gain.getValue());
        GainLabel.setText("Gain\n" + processor.getParameterText(DistorsionAudioProcessor::Gain), juce::dontSendNotification);
    }
    else if (changedSlider == &Threshold)
    {
        processor.setParameterNotifyingHost(DistorsionAudioProcessor::Threshold, Threshold.getValue());
        ThresholdLabel.setText("Threshold\n" + processor.getParameterText(DistorsionAudioProcessor::Threshold), juce::dontSendNotification);
    }
    else if (changedSlider == &Volume)
    {
        processor.setParameterNotifyingHost(DistorsionAudioProcessor::Volume, Volume.getValue());
        VolumeLabel.setText("Volume\n" + processor.getParameterText(DistorsionAudioProcessor::Volume), juce::dontSendNotification);
    }
}

void DistorsionAudioProcessorEditor::buttonClicked(juce::Button * clickedButton)
{
    if (clickedButton == &Bypass)
    {
        processor.setParameterNotifyingHost(DistorsionAudioProcessor::MasterBypass, Bypass.getToggleState());
    }
}

void DistorsionAudioProcessorEditor::timerCallback()
{
    Gain.setValue(processor.getParameter(DistorsionAudioProcessor::Gain), juce::dontSendNotification);
    Threshold.setValue(processor.getParameter(DistorsionAudioProcessor::Threshold), juce::dontSendNotification);
    Volume.setValue(processor.getParameter(DistorsionAudioProcessor::Volume), juce::dontSendNotification);
    Bypass.setToggleState(processor.getParameter(DistorsionAudioProcessor::MasterBypass) == 1.0f ? true : false, juce::dontSendNotification);

    GainLabel.setText("Gain\n" + processor.getParameterText(DistorsionAudioProcessor::Gain), juce::dontSendNotification);
    ThresholdLabel.setText("Threshold\n" + processor.getParameterText(DistorsionAudioProcessor::Threshold), juce::dontSendNotification);
    VolumeLabel.setText("Volume\n" + processor.getParameterText(DistorsionAudioProcessor::Volume), juce::dontSendNotification);
}
