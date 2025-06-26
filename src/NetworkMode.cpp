#include "NetworkMode.h"

NetworkMode currentNetworkMode = NetworkMode::MESHTASTIC;

void setNetworkMode(NetworkMode mode) {
    currentNetworkMode = mode;
}
