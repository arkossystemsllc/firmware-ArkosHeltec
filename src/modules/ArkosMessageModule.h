#pragma once

#include "mesh/MeshModule.h"

class ArkosMessageModule : public MeshModule {
  public:
    enum ArkosPort : uint8_t {
        ARKOS_STATUS = 0x80,
        ARKOS_SENSOR_ALERT = 0x81
    };

    ArkosMessageModule();

    virtual bool wantPacket(const meshtastic_MeshPacket *p) override;
    virtual ProcessMessage handleReceived(const meshtastic_MeshPacket &p) override;
};
