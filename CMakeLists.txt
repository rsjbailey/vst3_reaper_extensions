cmake_minimum_required(VERSION 3.22)
project(vst_ext_test VERSION 1.0 LANGUAGES CXX)
add_subdirectory(external/JUCE)

juce_add_plugin(ext_test
        COMPANY_NAME "test.co.uk"
        FORMATS VST3
        IS_SYNTH FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_CODE T30q
        VST3_CATEGORIES Fx)

target_link_libraries(ext_test PRIVATE juce::juce_audio_utils)
target_sources(ext_test PRIVATE processor.cpp)
target_compile_definitions(ext_test
        PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0
        )