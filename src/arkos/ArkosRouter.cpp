#include "ArkosRouter.h"
#include "PowerFSM.h"
#include "PowerStatus.h"

ArkosRouter::ArkosRouter() : ReliableRouter() {}

uint8_t ArkosRouter::selectBestNextHop(NodeNum to) {
    uint8_t bestHop = NO_NEXT_HOP_PREFERENCE;
    float bestScore = -1000.0f;
    uint8_t ourRelay = nodeDB->getLastByteOfNodeNum(getNodeNum());

    meshtastic_NodeInfoLite *dest = nodeDB->getMeshNode(to);
    if (dest && dest->next_hop && dest->next_hop != ourRelay) {
        return dest->next_hop;
    }

    for (size_t i = 0; i < nodeDB->getNumMeshNodes(); ++i) {
        meshtastic_NodeInfoLite *n = nodeDB->getMeshNodeByIndex(i);
        if (n->num == 0 || n->next_hop == 0 || n->num == to)
            continue;
        float hopScore = n->has_hops_away && n->hops_away ? 1.0f / n->hops_away : 0.0f;
        float score = hopScore + n->snr;
        if (score > bestScore) {
            bestScore = score;
            bestHop = n->next_hop;
        }
    }
    return bestHop;
}

ErrorCode ArkosRouter::send(meshtastic_MeshPacket *p) {
    if (!isBroadcast(p->to)) {
        p->next_hop = selectBestNextHop(p->to);
    }

    if (arkosConfig.powerAware && powerStatus && powerStatus->getBatteryChargePercent() >= 0 &&
        powerStatus->getBatteryChargePercent() < 20 && !powerStatus->getIsCharging()) {
        delay(200); // conserve power when battery low
    }

    if (arkosConfig.lowProbDetect) {
        delay(random(20, 120));
    }

    ErrorCode err = ReliableRouter::send(p);
    if (err && p) {
        LOG_WARN("Arkos send failed %d, retrying", err);
        delay(50);
        if (!isBroadcast(p->to)) {
            p->next_hop = selectBestNextHop(p->to);
        }
        err = ReliableRouter::send(p);
    }
    return err;
}

bool ArkosRouter::shouldFilterReceived(const meshtastic_MeshPacket *p) {
    if (p->which_payload_variant == meshtastic_MeshPacket_encrypted_tag && p->pki_encrypted && !isToUs(p)) {
        return false; // forward silently
    }
    return ReliableRouter::shouldFilterReceived(p);
}
