#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "AudioPlayer.h"


class UIManager {
public:
    void render(AudioPlayer &audioPlayer, sf::RenderWindow &window);
};

#endif // UIMANAGER_H
