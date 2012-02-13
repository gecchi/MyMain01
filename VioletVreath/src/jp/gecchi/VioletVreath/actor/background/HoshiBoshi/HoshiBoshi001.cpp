#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshi001";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñB
    _far_rate = 30.0f;
    _SX = _SY = _SZ =  (P_CAM->_zf*LEN_UNIT)*_far_rate;
}

void HoshiBoshi001::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshi001::processBehavior() {
    if (_X < -_CAM_ZF*_far_rate) {
        _X += (_CAM_ZF*_far_rate*2);
    } else {
        _X -= 1000*_far_rate;
    }
    _pUvFlipper->behave();
}

void HoshiBoshi001::processJudgement() {
}

HoshiBoshi001::~HoshiBoshi001() {
}
