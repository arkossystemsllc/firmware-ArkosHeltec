#include "ArkosModules.h"
#include "modules/ArkosMessageModule.h"
#include "ArkosConfig.h"

void setupArkosModules() {
    loadArkosConfig();
    new ArkosMessageModule();
}
