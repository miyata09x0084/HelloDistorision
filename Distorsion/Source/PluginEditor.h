/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistorsionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistorsionAudioProcessorEditor (DistorsionAudioProcessor&);
    ~DistorsionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistorsionAudioProcessor& audioProcessor;
    
    juce::Slider Gain;
    juce::Slider Threshold;
    juce::Slider Volume;

    juce::Label GainLabel;
    juce::Label ThresholdLabel;
    juce::Label VolumeLabel;

    juce::ToggleButton Bypass;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistorsionAudioProcessorEditor)
};
