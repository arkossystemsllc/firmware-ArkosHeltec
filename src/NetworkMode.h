#pragma once

enum class NetworkMode {
    MESHTASTIC = 0,
    ARKOS = 1
};

extern NetworkMode currentNetworkMode;
void setNetworkMode(NetworkMode mode);
