#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

HoshiBoshiTitle::HoshiBoshiTitle(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshiTitle";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñB
    _far_rate = 10.0f;
    _SX = _SY = _SZ =  (P_CAM->_zf*LEN_UNIT)*_far_rate;
}

void HoshiBoshiTitle::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTitle::processBehavior() {
    if (_X < -_CAM_ZF*_far_rate) {
        _X += (_CAM_ZF*_far_rate*2);
    } else {
        _X -= 10000*_far_rate;
    }
    _pUvFlipper->behave();
    _pFader->behave();
}

void HoshiBoshiTitle::processJudgement() {
}

void HoshiBoshiTitle::fadein() {
    _pFader->setAlphaToBottom();
    _pFader->intoTargetAlphaLinerUntil(1.0, 240);
}
HoshiBoshiTitle::~HoshiBoshiTitle() {
}
