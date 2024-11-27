#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <SFML/Graphics.hpp>
#include "AudioPlayer.h"

class Visualizer {
public:
    // update the visualizer's data based on audio 
    virtual void update(const AudioPlayer& audioPlayer) = 0;
    // to render the visualizer onto the window
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Visualizer() {}
};

#endif // VISUALIZER_H
