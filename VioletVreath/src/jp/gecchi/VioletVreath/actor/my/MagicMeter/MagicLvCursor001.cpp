#include "stdafx.h"
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
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->forcePtnRange(0,2);
}

void MagicLvCursor001::moveSmoothTo(int prm_lv) {
    MagicLvCursor::moveSmoothTo(prm_lv, 12, 0.3f, 0.7f);
}

void MagicLvCursor001::dispDisable() {
    _pUvFlipper->forcePtnRange(3,3); //ƒƒbƒN•\Ž¦
    _pUvFlipper->setActivePtn(3);
}

void MagicLvCursor001::dispEnable() {
    _pUvFlipper->forcePtnRange(0,2);
    _pUvFlipper->setActivePtn(0);
}

MagicLvCursor001::~MagicLvCursor001() {
}
