#pragma once

// Configuration options for ArkosMesh mode

enum class ArkosTopology {
    P2P = 0,
    FEDERATED = 1,
    STAR = 2
};

struct ArkosConfig {
    ArkosTopology topology = ArkosTopology::P2P;
    bool powerAware = false;
    bool lowProbDetect = false;
};

extern ArkosConfig arkosConfig;
void loadArkosConfig();
void setArkosTopology(ArkosTopology t);
void enablePowerAware(bool en);
void enableLowProbDetect(bool en);
