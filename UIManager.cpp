#include "UIManager.h"
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <string>
#include <algorithm>
#include "FileDialog.h"

void UIManager::render(AudioPlayer &audioPlayer, sf::RenderWindow &window) {

    static char filepath[128] = "";

    // Menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open")) {
                std::string path = FileDialog::OpenFile();
                // Set "filepath" to acquired path
                path.copy(filepath, sizeof(filepath), 0);
                std::fill_n(filepath + path.size(), sizeof(filepath) - path.size(), '\0');
            }
            if (ImGui::MenuItem("Exit")) {
                window.close();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Audio Controls
    ImGui::Begin("Audio Controls");

    ImGui::InputText("Audio File", filepath, IM_ARRAYSIZE(filepath));

    if (ImGui::Button("Load")) {
        try {
            audioPlayer.loadAudio(filepath);
        } catch (const std::exception& e) {
            // Handle error (e.g., display error message)
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Error loading audio: %s", e.what());
        }
    }

    if (ImGui::Button("Play")) {
        audioPlayer.play();
    }

    ImGui::SameLine();

    if (ImGui::Button("Pause")) {
        audioPlayer.pause();
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
        audioPlayer.stop();
    }

    // Display playback progress
    float currentTime = audioPlayer.getCurrentTime();
    float totalTime = audioPlayer.getTotalTime();
    ImGui::ProgressBar(currentTime / totalTime, ImVec2(0.0f, 0.0f));

    ImGui::End();
}
