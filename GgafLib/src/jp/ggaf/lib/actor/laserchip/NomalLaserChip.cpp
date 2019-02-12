#include "jp/ggaf/lib/actor/laserchip/NomalLaserChip.h"



using namespace GgafLib;

NomalLaserChip::NomalLaserChip(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat) :
        LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "NomalLaserChip";
}

void NomalLaserChip::processSettlementBehavior() {
    if (_was_paused_flg) {
        GgafDx::GeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}

NomalLaserChip::~NomalLaserChip() {
}

