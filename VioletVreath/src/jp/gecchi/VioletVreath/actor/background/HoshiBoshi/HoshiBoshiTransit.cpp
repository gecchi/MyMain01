#include "HoshiBoshiTransit.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiTransit::HoshiBoshiTransit(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshiTransit") {
    _class_name = "HoshiBoshiTransit";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñ‚ÅA
    far_rate_ = 1.0f;
    _sx = _sy = _sz =  (P_CAM->getZFar()*LEN_UNIT)*far_rate_;
}

void HoshiBoshiTransit::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTransit::processBehavior() {
    if (_x < -CAM_ZF_*far_rate_) {
        _x += (CAM_ZF_*far_rate_*2);
    } else {
        _x -= 90000*far_rate_;
    }
    getUvFlipper()->behave();
}

void HoshiBoshiTransit::processJudgement() {
}


HoshiBoshiTransit::~HoshiBoshiTransit() {
}
