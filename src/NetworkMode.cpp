#include "NetworkMode.h"
#include "FSCommon.h"
#include "SPILock.h"
#include <Arduino.h>

NetworkMode currentNetworkMode = NetworkMode::MESHTASTIC;

void setNetworkMode(NetworkMode mode) {
    currentNetworkMode = mode;
}

// Path where the selected network mode is stored
static const char *networkModeFile = "/prefs/network_mode";

void persistNetworkMode() {
#ifdef FSCom
    concurrency::LockGuard g(spiLock);
    File f = FSCom.open(networkModeFile, FILE_O_WRITE);
    if (f) {
        uint8_t m = static_cast<uint8_t>(currentNetworkMode);
        f.write(&m, 1);
        f.close();
    }
#endif
}

void loadNetworkMode() {
#ifdef FSCom
    concurrency::LockGuard g(spiLock);
    File f = FSCom.open(networkModeFile, FILE_O_READ);
    if (f) {
        int v = f.read();
        if (v == static_cast<int>(NetworkMode::ARKOS))
            currentNetworkMode = NetworkMode::ARKOS;
        else
            currentNetworkMode = NetworkMode::MESHTASTIC;
        f.close();
    }
#endif
}
