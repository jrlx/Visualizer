#include "UIManager.h"
#include <imgui.h>

void UIManager::render(AudioPlayer& audioPlayer) {
    ImGui::Begin("Audio Controls");

    static char filepath[128] = "";
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
