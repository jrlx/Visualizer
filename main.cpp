#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <memory>
#include "AudioPlayer.h"
#include "Visualizer.h"
#include "WaveformVisualizer.h"
#include "UIManager.h"

class Application {
private:
    sf::RenderWindow window;
    AudioPlayer audioPlayer; // an instance to manage the audio
    std::unique_ptr<Visualizer> visualizer; // Using smart pointer for dynamic memory management
    UIManager uiManager; // to manage the imgui interface

public:
    // to initalize the window
    Application() : window(sf::VideoMode(800, 600), "Music Visualizer") {
        ImGui::SFML::Init(window); // connects imgui with sfml
        // Initialize default visualizer
        visualizer = std::make_unique<WaveformVisualizer>();
    }
    // our destructor

    ~Application() { 
        ImGui::SFML::Shutdown();
    }

    void run() {
        sf::Clock deltaClock;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            ImGui::SFML::Update(window, deltaClock.restart());

            // Render UI
            uiManager.render(audioPlayer);

            // Update visualization
            visualizer->update(audioPlayer);

            window.clear();
            visualizer->render(window); // Render visualizer
            ImGui::SFML::Render(window);
            window.display();
        }
    }
};

int main() {
    // creating an instance of applicaiton
    try {
        Application app;
        // calls run method
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Application Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
