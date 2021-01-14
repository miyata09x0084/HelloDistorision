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
}

DistorsionAudioProcessorEditor::~DistorsionAudioProcessorEditor()
{
}

//==============================================================================
void DistorsionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DistorsionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
