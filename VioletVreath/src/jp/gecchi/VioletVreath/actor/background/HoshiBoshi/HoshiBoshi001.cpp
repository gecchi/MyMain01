#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshi001";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñB
    far_rate_ = 30.0f;
    _SX = _SY = _SZ =  (P_CAM->_zf*LEN_UNIT)*far_rate_;
}

void HoshiBoshi001::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshi001::processBehavior() {
    if (_X < -CAM_ZF_*far_rate_) {
        _X += (CAM_ZF_*far_rate_*2);
    } else {
        _X -= 1000*far_rate_;
    }
    _pUvFlipper->behave();
}

void HoshiBoshi001::processJudgement() {
}

HoshiBoshi001::~HoshiBoshi001() {
}
