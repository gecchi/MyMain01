#include "stdafx.h"
using namespace std;
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

void MagicLvCursor001::moveTo(int prm_lv) {
    MagicLvCursor::moveTo(prm_lv, 10, 0.3f, 0.7f);
}
void MagicLvCursor001::disable() {
    _pUvFlipper->forcePtnRange(3,3); //ロック表示
    _pUvFlipper->setActivePtn(3);
}


void MagicLvCursor001::enable() {
    _pUvFlipper->forcePtnRange(0,2);
    _pUvFlipper->setActivePtn(0);
}

void MagicLvCursor001::beginBlinking() {
    _pFader->beat(6, 0, 3, 3, 10); //ピカピカ
}

void MagicLvCursor001::stopBlinking() {
    _pFader->beat(8, 0, 4, 4, 1); //ピカピカ終了
}

MagicLvCursor001::~MagicLvCursor001() {
}
