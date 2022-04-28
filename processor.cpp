#include "processor.hpp"
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ExtTestProcessor();
}

const juce::String ExtTestProcessor::getName() const {
    return "ext_test";
}

void ExtTestProcessor::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) {

}

void ExtTestProcessor::releaseResources() {

}

void ExtTestProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {

}

double ExtTestProcessor::getTailLengthSeconds() const {
    return 0;
}

bool ExtTestProcessor::acceptsMidi() const {
    return false;
}

bool ExtTestProcessor::producesMidi() const {
    return false;
}

juce::AudioProcessorEditor *ExtTestProcessor::createEditor() {
    return nullptr;
}

bool ExtTestProcessor::hasEditor() const {
    return false;
}

int ExtTestProcessor::getNumPrograms() {
    return 0;
}

int ExtTestProcessor::getCurrentProgram() {
    return 0;
}

void ExtTestProcessor::setCurrentProgram(int index) {

}

const juce::String ExtTestProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void ExtTestProcessor::changeProgramName(int index, const juce::String &newName) {

}

void ExtTestProcessor::getStateInformation(juce::MemoryBlock &destData) {

}

void ExtTestProcessor::setStateInformation(const void *data, int sizeInBytes) {

}
