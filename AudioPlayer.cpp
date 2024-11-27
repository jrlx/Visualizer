#include "AudioPlayer.h"
#include <iostream>

AudioPlayer::AudioPlayer() {
    // Constructor
}

// attempts to load the audio file
void AudioPlayer::loadAudio(const std::string& filepath) {
    if (!buffer.loadFromFile(filepath)) {
        throw std::runtime_error("Failed to load audio file: " + filepath);
    }
    sound.setBuffer(buffer); // assoicates the buffer with the sound object
}

void AudioPlayer::play() {
    sound.play();
}

void AudioPlayer::pause() {
    sound.pause();
}

void AudioPlayer::stop() {
    sound.stop();
}
// our audio data buffer
const sf::SoundBuffer& AudioPlayer::getBuffer() const {
    return buffer;
}
// our playing,pause,and stop
sf::Sound::Status AudioPlayer::getStatus() const {
    return sound.getStatus();
}

float AudioPlayer::getCurrentTime() const {
    return sound.getPlayingOffset().asSeconds();
}

float AudioPlayer::getTotalTime() const {
    return buffer.getDuration().asSeconds();
}
