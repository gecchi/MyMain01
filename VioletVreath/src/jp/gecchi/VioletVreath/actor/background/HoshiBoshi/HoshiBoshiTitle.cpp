#include "stdafx.h"
#include "HoshiBoshiTitle.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiTitle::HoshiBoshiTitle(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshiTitle";
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚ÉŽû‚Ü‚Á‚Ä‚¢‚é‘O’ñB
    far_rate_ = 10.0f;
    _sx = _sy = _sz =  (P_CAM->_zf*LEN_UNIT)*far_rate_;
}

void HoshiBoshiTitle::onActive() {
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTitle::processBehavior() {
    if (_x < -CAM_ZF_*far_rate_) {
        _x += (CAM_ZF_*far_rate_*2);
    } else {
        _x -= 10000*far_rate_;
    }
    _pUvFlipper->behave();
    _pAFader->behave();
}

void HoshiBoshiTitle::processJudgement() {
}

void HoshiBoshiTitle::fadein() {
    _pAFader->setToBottom();
    _pAFader->fadeLinerUntil(1.0, 240);
}
HoshiBoshiTitle::~HoshiBoshiTitle() {
}
