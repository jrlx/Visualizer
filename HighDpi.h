#ifndef HIGHDPI_H
#define HIGHDPI_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>

void SetDPIAwareness(sf::RenderWindow &window) {
#ifdef _WIN32
    UINT dpi = GetDpiForWindow(window.getSystemHandle());
    float dpiScale = dpi / 96.0f;

    ImGui::GetIO().FontGlobalScale = dpiScale;

    sf::View view = window.getView();
    view.setSize(window.getSize().x / dpiScale, window.getSize().y / dpiScale);
    window.setView(view);
#else
    // DPI Awareness not implemented
#endif
}


#endif // HIGHDPI_H