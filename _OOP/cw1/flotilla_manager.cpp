#include "flotilla_manager.h"

FlotillasManager &FlotillasManager::operator+=(const Flotilla &flotilla) {
    flotillas[size++] = flotilla;
    return *this;
}

void FlotillasManager::addNewFlotilla() {
    Flotilla flotilla;
    cin >> flotilla;
    *this += flotilla;
}

Flotilla &FlotillasManager::operator[](const size_t idx) {
    return flotillas[idx];
}

size_t FlotillasManager::findFlotillaWithMaxAutopilot() {
    size_t flotilla_idx = 0;
    for (size_t maxAutopilot = 0, i = 0; i < size; ++i)
        if (flotillas[i].countAutopilot() > maxAutopilot) {
            maxAutopilot = flotillas[i].countAutopilot();
            flotilla_idx = i;
        }
    return flotilla_idx;
}
