#include "ArkosRouter.h"

ArkosRouter::ArkosRouter() : ReliableRouter() {}

ErrorCode ArkosRouter::send(meshtastic_MeshPacket *p) {
    // Placeholder for Arkos-specific routing policies
    return ReliableRouter::send(p);
}

bool ArkosRouter::shouldFilterReceived(const meshtastic_MeshPacket *p) {
    // Custom filtering for Arkos messages could go here
    return ReliableRouter::shouldFilterReceived(p);
}
