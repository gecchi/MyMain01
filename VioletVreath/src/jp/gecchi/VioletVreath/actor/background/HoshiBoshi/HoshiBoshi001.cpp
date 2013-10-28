#include "stdafx.h"
#include "HoshiBoshi001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshi001";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñB
    far_rate_ = 30.0f;
    _sx = _sy = _sz =  (P_CAM->_zf*LEN_UNIT)*far_rate_;
}

void HoshiBoshi001::onActive() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshi001::processBehavior() {
    if (_x < -CAM_ZF_*far_rate_) {
        _x += (CAM_ZF_*far_rate_*2);
    } else {
        _x -= 1000*far_rate_;
    }
    _pUvFlipper->behave();
}

void HoshiBoshi001::processJudgement() {
}

HoshiBoshi001::~HoshiBoshi001() {
}
