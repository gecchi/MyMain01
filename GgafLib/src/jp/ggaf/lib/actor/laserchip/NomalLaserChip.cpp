#include "jp/ggaf/lib/actor/laserchip/NomalLaserChip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

NomalLaserChip::NomalLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "NomalLaserChip";
}

void NomalLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

NomalLaserChip::~NomalLaserChip() {
}

