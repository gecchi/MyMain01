#include "stdafx.h"
#include "MagicLvCursor001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor001::MagicLvCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor001", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor001";
}
void MagicLvCursor001::initialize() {
    MagicLvCursor::initialize();
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setActivePtn(0);
    pUvFlipper->setFlipPtnRange(0,2);
}

void MagicLvCursor001::moveSmoothTo(int prm_lv) {
    MagicLvCursor::moveSmoothTo(prm_lv, 12, 0.3f, 0.7f);
}

void MagicLvCursor001::dispDisable() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(3,3); //ƒƒbƒN•\Ž¦
    pUvFlipper->setActivePtn(3);
}

void MagicLvCursor001::dispEnable() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,2);
    pUvFlipper->setActivePtn(0);
}

MagicLvCursor001::~MagicLvCursor001() {
}
