#include "stdafx.h"
#include "HoshiBoshiRankUp.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiRankUp::HoshiBoshiRankUp(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiRankUp") {
    _class_name = "HoshiBoshiRankUp";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñ‚ÅA
    far_rate_ = 1.0f;
    _sx = _sy = _sz =  (P_CAM->_zf*LEN_UNIT)*far_rate_;
}

void HoshiBoshiRankUp::onActive() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 36);
}

void HoshiBoshiRankUp::processBehavior() {
    if (_x > CAM_ZF_*far_rate_) {
        _x -= (CAM_ZF_*far_rate_*2);
    } else {
        _x += 90000*far_rate_;
    }
    _pUvFlipper->behave();
}

void HoshiBoshiRankUp::processJudgement() {
}


HoshiBoshiRankUp::~HoshiBoshiRankUp() {
}
