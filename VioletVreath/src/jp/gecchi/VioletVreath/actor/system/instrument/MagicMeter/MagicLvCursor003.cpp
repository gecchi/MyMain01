#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor003::MagicLvCursor003(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor001", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor003";
    pMagicMeter_ = prm_pMagicMeter;
    pMagic_ = prm_pMagic;
    magic_index_ = pMagicMeter_->ringMagics_.indexOf(pMagic_);
    if (magic_index_ < 0) {
        throwGgafCriticalException("MagicLvCursor003::MagicLvCursor003 prm_pMagic("<<prm_pMagic->getName()<<")‚Í"<<
                                   "MagicMeter‚É“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñB");
    }
}

void MagicLvCursor003::initialize() {
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->forcePtnRange(0,2);
}

void MagicLvCursor003::markOff() {
    setAlpha(0);
//    _pFader->intoTargetAlphaLinerUntil(0, 60);
}

void MagicLvCursor003::markOn(int prm_lv) {
    setLv(prm_lv);
    setAlpha(1);
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->forcePtnRange(0,2);
}

MagicLvCursor003::~MagicLvCursor003() {
}
