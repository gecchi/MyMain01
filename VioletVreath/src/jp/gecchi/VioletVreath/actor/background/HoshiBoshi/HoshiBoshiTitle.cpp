#include "HoshiBoshiTitle.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

HoshiBoshiTitle::HoshiBoshiTitle(const char* prm_name) :
        HoshiBoshi(prm_name, "HoshiBoshi001") {
    _class_name = "HoshiBoshiTitle";
    pAFader_ = NEW GgafDxAlphaFader(this);
}

void HoshiBoshiTitle::initialize() {
    setFarRate(10.0f);
}

void HoshiBoshiTitle::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTitle::processBehavior() {
    _x -= 10000*getFarRate();
    getUvFlipper()->behave();
    pAFader_->behave();
}

void HoshiBoshiTitle::processJudgement() {
}

void HoshiBoshiTitle::fadein() {
    setAlpha(pAFader_->getBottom());
    pAFader_->transitionLinerUntil(1.0, 240);
}
HoshiBoshiTitle::~HoshiBoshiTitle() {
    GGAF_DELETE(pAFader_);
}
