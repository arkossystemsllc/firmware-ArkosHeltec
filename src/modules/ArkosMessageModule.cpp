#include "ArkosMessageModule.h"
#include "PowerFSM.h"
#if defined(ARCH_ESP32)
#include "WiFiOTA.h"
#endif

ArkosMessageModule::ArkosMessageModule() : MeshModule("ArkosMessage") {
    encryptedOk = true;
}

bool ArkosMessageModule::wantPacket(const meshtastic_MeshPacket *p) {
    return p->decoded.portnum == ARKOS_STATUS || p->decoded.portnum == ARKOS_SENSOR_ALERT ||
           p->decoded.portnum == ARKOS_CONTROL || p->decoded.portnum == ARKOS_BINARY;
}

ProcessMessage ArkosMessageModule::handleReceived(const meshtastic_MeshPacket &p) {
    const pb_bytes_array_t *payload = nullptr;
    if (p.which_payload_variant == meshtastic_MeshPacket_decoded_tag) {
        payload = &p.decoded.payload;
    } else if (p.which_payload_variant == meshtastic_MeshPacket_encrypted_tag) {
        payload = &p.encrypted;
    }
    if (!payload || payload->size < 1)
        return ProcessMessage::CONTINUE;

    ArkosMsgType type = static_cast<ArkosMsgType>(payload->bytes[0]);
    const uint8_t *data = &payload->bytes[1];
    size_t len = payload->size - 1;

    switch (type) {
        case SENSOR_REPORT:
            handleSensorReport(data, len);
            break;
        case BINARY_PAYLOAD:
            handleBinaryPayload(data, len);
            break;
        case CONTROL_CMD:
            handleControlCmd(data, len);
            break;
        case OTA_TRIGGER:
#if defined(ARCH_ESP32)
            WiFiOTA::saveConfig(&config.network);
            if (WiFiOTA::trySwitchToOTA()) {
                powerFSM.trigger(EVENT_FIRMWARE_UPDATE);
            }
#endif
            break;
        default:
            break;
    }
    return ProcessMessage::STOP;
}

void ArkosMessageModule::handleSensorReport(const uint8_t *data, size_t len) {
    if (len < 5)
        return;
    uint8_t sensorId = data[0];
    int32_t value;
    memcpy(&value, &data[1], 4);
    LOG_INFO("Sensor %u report %d", sensorId, value);
}

void ArkosMessageModule::handleBinaryPayload(const uint8_t *data, size_t len) {
    LOG_INFO("Received %u bytes of binary payload", (unsigned)len);
    // TODO: store payload to flash for side-loading
}

void ArkosMessageModule::handleControlCmd(const uint8_t *data, size_t len) {
    std::string cmd(reinterpret_cast<const char *>(data), len);
    LOG_INFO("Control command: %s", cmd.c_str());
}
