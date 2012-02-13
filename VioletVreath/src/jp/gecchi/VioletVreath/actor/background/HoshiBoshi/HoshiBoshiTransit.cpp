#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



HoshiBoshiTransit::HoshiBoshiTransit(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiTransit") {
    _class_name = "HoshiBoshiTransit";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñ‚ÅA
    _far_rate = 1.0f;
    _SX = _SY = _SZ =  (P_CAM->_zf*LEN_UNIT)*_far_rate;
}

void HoshiBoshiTransit::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTransit::processBehavior() {
    if (_X < -_CAM_ZF*_far_rate) {
        _X += (_CAM_ZF*_far_rate*2);
    } else {
        _X -= 90000*_far_rate;
    }
    _pUvFlipper->behave();
}

void HoshiBoshiTransit::processJudgement() {
}


HoshiBoshiTransit::~HoshiBoshiTransit() {
}
