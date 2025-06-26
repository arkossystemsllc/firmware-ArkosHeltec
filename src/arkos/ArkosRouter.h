#pragma once

#include "mesh/ReliableRouter.h"
#include "mesh/NodeDB.h"
#include "ArkosConfig.h"

class ArkosRouter : public ReliableRouter {
  public:
    ArkosRouter();
    virtual ErrorCode send(meshtastic_MeshPacket *p) override;

  protected:
    uint8_t selectBestNextHop(NodeNum to);

    virtual bool shouldFilterReceived(const meshtastic_MeshPacket *p) override;
};
