#pragma once

#include "mesh/ReliableRouter.h"

class ArkosRouter : public ReliableRouter {
  public:
    ArkosRouter();
    virtual ErrorCode send(meshtastic_MeshPacket *p) override;

  protected:
    virtual bool shouldFilterReceived(const meshtastic_MeshPacket *p) override;
};
