#include "stdafx.h"
#include "MagicLvCursor001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor001::MagicLvCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor001", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor001";
}
void MagicLvCursor001::initialize() {
    MagicLvCursor::initialize();
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,2);
    pUvFlipper->setActivePtnToTop();
}

void MagicLvCursor001::moveSmoothTo(int prm_lv) {
    MagicLvCursor::moveSmoothTo(prm_lv, 12, 0.3f, 0.7f);
}

void MagicLvCursor001::dispDisable() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    int lock_ptn_no = pUvFlipper->getBottomPtnno() + 1; //最後のパターンの次はロック表示
    pUvFlipper->setFlipPtnRange(lock_ptn_no, lock_ptn_no);
    pUvFlipper->setActivePtn(lock_ptn_no);
}

void MagicLvCursor001::dispEnable() {
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,2);
    pUvFlipper->setActivePtnToTop();
}

MagicLvCursor001::~MagicLvCursor001() {
}
