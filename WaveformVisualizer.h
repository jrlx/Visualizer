#ifndef WAVEFORMVISUALIZER_H
#define WAVEFORMVISUALIZER_H

#include "Visualizer.h"
#include <vector>


class WaveformVisualizer : public Visualizer {
private:
    // storing the vertices to be able to draw the waveform 
    std::vector<sf::Vertex> waveformVertices;
    // creating that rectanglular background for our visualizer
    sf::RectangleShape background;

public:
    WaveformVisualizer();
    // starts to update the vertices bases on the audio data
    void update(const AudioPlayer& audioPlayer) override;
    // start rendering the waveform on to the window
    void render(sf::RenderWindow& window) override;
};

#endif // WAVEFORMVISUALIZER_H
