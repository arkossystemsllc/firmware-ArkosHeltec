#pragma once

#include "mesh/MeshModule.h"

class ArkosMessageModule : public MeshModule {
  public:
    enum ArkosPort : uint8_t {
        ARKOS_STATUS = 0x80,
        ARKOS_SENSOR_ALERT = 0x81,
        ARKOS_CONTROL = 0x82,
        ARKOS_BINARY = 0x83
    };

    enum ArkosMsgType : uint8_t {
        SENSOR_REPORT = 1,
        BINARY_PAYLOAD = 2,
        CONTROL_CMD = 3,
        OTA_TRIGGER = 4
    };

    ArkosMessageModule();

    virtual bool wantPacket(const meshtastic_MeshPacket *p) override;
    virtual ProcessMessage handleReceived(const meshtastic_MeshPacket &p) override;

  private:
    void handleSensorReport(const uint8_t *data, size_t len);
    void handleBinaryPayload(const uint8_t *data, size_t len);
    void handleControlCmd(const uint8_t *data, size_t len);
};
