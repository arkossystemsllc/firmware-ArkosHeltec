#include "ArkosConfig.h"

ArkosConfig arkosConfig;

void loadArkosConfig() {
    // TODO: load from persistent storage if desired
}

void setArkosTopology(ArkosTopology t) { arkosConfig.topology = t; }
void enablePowerAware(bool en) { arkosConfig.powerAware = en; }
void enableLowProbDetect(bool en) { arkosConfig.lowProbDetect = en; }
