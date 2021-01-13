/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistorsionAudioProcessor::DistorsionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    UserParams[MasterBypass] = 0.0f;
    UserParams[Gain] = 0.7f;
    UserParams[Threshold] = 1.0f;
    UserParams[Volume] = 0.7f;
}

DistorsionAudioProcessor::~DistorsionAudioProcessor()
{
}

//==============================================================================
const juce::String DistorsionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistorsionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistorsionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistorsionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistorsionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistorsionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistorsionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistorsionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistorsionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistorsionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistorsionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistorsionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistorsionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistorsionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (UserParams[MasterBypass] == 1.0f) return;
    
    buffer.applyGain(pow(UserParams[Gain], 2) * 2.0f);
    float threshold = pow(UserParams[Threshold], 2);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        for (long buffNum = 0; buffNum<buffer.getNumSamples(); buffNum++)
        {
            if (channelData[buffNum] >= threshold)
            {
                channelData[buffNum] = threshold;
            }
            else if (channelData[buffNum] <= -threshold)
            {
                channelData[buffNum] = -threshold;
            }
        }
    }
    buffer.applyGain(pow(UserParams[Volume], 2) * 2.0f);
}

//==============================================================================
bool DistorsionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistorsionAudioProcessor::createEditor()
{
    return new DistorsionAudioProcessorEditor (*this);
}

//==============================================================================
void DistorsionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistorsionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistorsionAudioProcessor();
}

int DistorsionAudioProcessor::getNumParameters() { return totalNumParam; }

float DistorsionAudioProcessor::getParameter(int index){
    if (index >= 0 && index < totalNumParam)
    {
        return UserParams[index];
    }
    else return 0;
}

void DistorsionAudioProcessor::setParameter(int index, float value)
{
    switch (index) {
        case MasterBypass:
            UserParams[MasterBypass] = value;
            break;
        case Gain:
            UserParams[Gain] = value;
            break;
        case Threshold:
            UserParams[Threshold] = value;
            break;
        case Volume:
            UserParams[Volume] = value;
            break;
        default: return;
    }
}

const juce::String DistorsionAudioProcessor::getParameterName(int index)
{
    switch (index)
    {
    case MasterBypass: return "Master Bypass";
    case Gain: return "Gain";
    case Threshold: return "Threshold";
    case Volume: return "Volume";
        default:return juce::String();
    }
}

const juce::String DistorsionAudioProcessor::getParameterText(int index)
{
    switch (index)
    {
    case MasterBypass:
        return UserParams[MasterBypass] == 1.0f ? "BYPASS" : "EFFECT";
    case Gain:
        return juce::String(juce::Decibels::gainToDecibels(pow(UserParams[Gain], 2)*2.0f), 1)+"dB";
    case Threshold:
        return juce::String(juce::Decibels::gainToDecibels(pow(UserParams[Threshold], 2)), 1)+"dB";
    case Volume:
        return juce::String(juce::Decibels::gainToDecibels(pow(UserParams[Volume], 2)*2.0f), 1)+"dB";
        default:return juce::String();
    }
}

