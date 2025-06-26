#include "ArkosConfig.h"
#include "FSCommon.h"
#include "SPILock.h"

ArkosConfig arkosConfig;

struct StoredArkosConfig {
    uint8_t topology;
    uint8_t powerAware;
    uint8_t lowProbDetect;
};

void loadArkosConfig() {
#ifdef FSCom
    concurrency::LockGuard g(spiLock);
    File f = FSCom.open("/arkos.cfg", FILE_O_READ);
    if (f) {
        StoredArkosConfig s{};
        if (f.readBytes(reinterpret_cast<char *>(&s), sizeof(s)) == sizeof(s)) {
            arkosConfig.topology = static_cast<ArkosTopology>(s.topology);
            arkosConfig.powerAware = s.powerAware;
            arkosConfig.lowProbDetect = s.lowProbDetect;
        }
        f.close();
    }
#endif
}

void setArkosTopology(ArkosTopology t) { arkosConfig.topology = t; }
void enablePowerAware(bool en) { arkosConfig.powerAware = en; }
void enableLowProbDetect(bool en) { arkosConfig.lowProbDetect = en; }
