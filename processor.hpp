//
// Created by Richard Bailey on 28/04/2022.
//

#ifndef VST_EXT_TEST_PROCESSOR_HPP
#define VST_EXT_TEST_PROCESSOR_HPP
#include <juce_audio_processors/juce_audio_processors.h>
#include "reaper_vst3_interfaces.h"

// This declaration is just because I'm lazy and always get function pointer typedefs wrong
// by declaring it here I can use decltype instead.
// There is a reaper API function with this signature that we're trying to get a pointer
// to and call, it creates a "Hello World" message box to let you know you've got a working
// handle to the API.
void APITest();

// Note we derive from juce::VST3ClientExtensions
class ExtTestProcessor : public juce::AudioProcessor, public juce::VST3ClientExtensions {
public:
    ExtTestProcessor() : AudioProcessor(
            BusesProperties().withInput("Input",  juce::AudioChannelSet::stereo(), true).withOutput("Output", juce::AudioChannelSet::stereo(), true)) {}
    ~ExtTestProcessor() override = default;

    int32_t queryIEditController(const char *tuid, void **obj) override {
        // could try casting to IReaperUIEmbedInterface here if we want to embed fx guis directly in reaper
        return VST3ClientExtensions::queryIEditController(tuid, obj);
    }

    void setIHostApplication(Steinberg::FUnknown *unknown) override {
        // if we instantiate the plugin in REAPER, one call to this will point to an instance of IReaperHostApplication
        auto reaperHost = dynamic_cast<IReaperHostApplication*>(unknown);
        if(reaperHost) {
            // this returns a void* that's either null or a type erased pointer to the function we've requested
            auto ptr = reaperHost->getReaperApi("APITest");
            if(ptr) {
                // cast it to the correct function pointer type and call it.
                reinterpret_cast<decltype(&APITest)>(ptr)();
            }
        }
        VST3ClientExtensions::setIHostApplication(unknown);
    }

    // Boilerplate to get a valid plugin
    const juce::String getName() const override;
    void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) override;
    double getTailLengthSeconds() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    juce::AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String &newName) override;
    void getStateInformation(juce::MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;
};
#endif //VST_EXT_TEST_PROCESSOR_HPP
