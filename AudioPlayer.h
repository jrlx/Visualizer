#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <SFML/Audio.hpp>
#include <string>

class AudioPlayer {
private:
    sf::SoundBuffer buffer; // holds the audio data in memory
    sf::Sound sound; //controlling playback

public:
    AudioPlayer();
    void loadAudio(const std::string& filepath); // load audio file into buffer
    void play();
    void pause();
    void stop();
    const sf::SoundBuffer& getBuffer() const; // returns reference to sound buffer
    sf::Sound::Status getStatus() const; // returns status of playback
    float getCurrentTime() const; // returns current playback position
    float getTotalTime() const; // returns total time of the sample
};

#endif // AUDIOPLAYER_H
