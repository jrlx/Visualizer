#include "WaveformVisualizer.h"
#include <iostream>

//
WaveformVisualizer::WaveformVisualizer() {
    background.setSize(sf::Vector2f(800, 300));
    background.setPosition(0, 150);
    background.setFillColor(sf::Color(50, 50, 50));
}
// buffer is the container that holds the audio file; samples are what makes the audio file.

void WaveformVisualizer::update(const AudioPlayer& audioPlayer) {
    const sf::SoundBuffer& buffer = audioPlayer.getBuffer();
    const sf::Int16* samples = buffer.getSamples(); // Get the number of samples stored in the buffer.
    std::size_t sampleCount = buffer.getSampleCount(); // Get the array of audio samples stored in the buffer.

    
    unsigned int channelCount = buffer.getChannelCount(); // Get the number of channels used by the sound; mono (1) or stereo audio (2) 
    unsigned int sampleRate = buffer.getSampleRate(); // The sample rate is the number of samples played per second. 

    if (sampleCount == 0) {
        waveformVertices.clear();
        return;
    }

    waveformVertices.clear();

    // get the current playback position in samples
    float currentTime = audioPlayer.getCurrentTime();
    std::size_t currentSampleIndex = static_cast<std::size_t>(currentTime * sampleRate * channelCount);

    // define the number of samples to display
    std::size_t displaySampleCount = sampleRate * channelCount * 0.1f; // Display 0.1 seconds of audio

    // to ensure we don't go beyond the sample count
    if (currentSampleIndex + displaySampleCount > sampleCount) {
        displaySampleCount = sampleCount - currentSampleIndex;
    }

    // Simplify samples to fit the window width
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 300;
    std::size_t samplesPerPixel = displaySampleCount / windowWidth;

    // the corresponding audio samples per pixel allowed
    // making sure at least one is there
    if (samplesPerPixel == 0) {
        samplesPerPixel = 1;
    }

    for (unsigned int i = 0; i < windowWidth; ++i) {
        std::size_t sampleIndex = currentSampleIndex + i * samplesPerPixel;
        if (sampleIndex >= sampleCount) break;

        sf::Int16 sampleValue = samples[sampleIndex];
        // converting the audio sample to a y-coordinate
        float y = (sampleValue / 32768.f) * (windowHeight / 2) + (windowHeight / 2) + 150;

        waveformVertices.emplace_back(sf::Vector2f(i, y), sf::Color::Green);
    }
}
// drawing out the vertices on the window (i,y)
void WaveformVisualizer::render(sf::RenderWindow& window) {
    // Draw background
    window.draw(background);

    // Draw the waveform
    if (!waveformVertices.empty()) {
        window.draw(&waveformVertices[0], waveformVertices.size(), sf::LineStrip);
    }
}
