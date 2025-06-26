#include "ArkosMessageModule.h"

ArkosMessageModule::ArkosMessageModule() : MeshModule("ArkosMessage") {}

bool ArkosMessageModule::wantPacket(const meshtastic_MeshPacket *p) {
    return p->decoded.portnum == ARKOS_STATUS || p->decoded.portnum == ARKOS_SENSOR_ALERT;
}

ProcessMessage ArkosMessageModule::handleReceived(const meshtastic_MeshPacket &p) {
    // Placeholder: process Arkos-specific messages
    return ProcessMessage::CONTINUE;
}
