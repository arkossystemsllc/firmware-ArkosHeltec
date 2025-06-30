#pragma once

enum class NetworkMode {
    MESHTASTIC = 0,
    ARKOS = 1
};

extern NetworkMode currentNetworkMode;
void setNetworkMode(NetworkMode mode);
// Persist current network mode to flash
void persistNetworkMode();
// Load saved network mode during startup
void loadNetworkMode();
