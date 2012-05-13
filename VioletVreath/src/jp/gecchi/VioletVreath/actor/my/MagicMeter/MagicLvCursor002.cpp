#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor002::MagicLvCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor002", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor002";
}
void MagicLvCursor002::initialize() {
    MagicLvCursor::initialize();
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->forcePtnRange(0,2);
}

void MagicLvCursor002::moveSmoothTo(int prm_lv, frame prm_spent) {
    MagicLvCursor::moveSmoothTo(prm_lv, prm_spent, 0.3f, 0.7f); //‚¶‚í`‚Á‚ÆˆÚ“®
}

void MagicLvCursor002::dispDisable() {
    _pUvFlipper->forcePtnRange(3,3); //ƒƒbƒN•\Ž¦
    _pUvFlipper->setActivePtn(3);
}

void MagicLvCursor002::dispEnable() {
    _pUvFlipper->forcePtnRange(0,2);
    _pUvFlipper->setActivePtn(0);
}

MagicLvCursor002::~MagicLvCursor002() {
}
