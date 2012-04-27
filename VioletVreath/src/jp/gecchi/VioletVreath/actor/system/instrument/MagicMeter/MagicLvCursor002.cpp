#include "stdafx.h"
using namespace std;
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

void MagicLvCursor002::moveSmoothTo(int prm_lv) {
    MagicLvCursor::moveSmoothTo(prm_lv, 10, 0.3f, 0.7f);
}

void MagicLvCursor002::dispDisable() {
    _pUvFlipper->forcePtnRange(3,3); //ロック表示
    _pUvFlipper->setActivePtn(3);
}

void MagicLvCursor002::dispEnable() {
    _pUvFlipper->forcePtnRange(0,2);
    _pUvFlipper->setActivePtn(0);
}

void MagicLvCursor002::beginBlinking() {
    //_pFader->beat(8, 0, 4, 4, -1); //ピカピカしっぱなし
}

//void MagicLvCursor002::stopBlinking() {
//    //_pFader->beat(8, 0, 4, 4, 1); //ピカピカ終了
//    setAlpha(pMagicMeter_->paFloat_rr_[magic_index_]);
//}

MagicLvCursor002::~MagicLvCursor002() {
}
