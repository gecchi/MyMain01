#include "MagicLvCursor001.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor001::MagicLvCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor001", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor001";
}
void MagicLvCursor001::initialize() {
    MagicLvCursor::initialize();
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,2);
    pUvFlipper->setActivePtnToTop();
}

void MagicLvCursor001::dispDisable() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    int lock_ptn_no = 3; //最後のパターンの次はロック表示
    pUvFlipper->setFlipPtnRange(lock_ptn_no, lock_ptn_no);
    pUvFlipper->setActivePtn(lock_ptn_no);
}

void MagicLvCursor001::dispEnable() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0,2);
    pUvFlipper->setActivePtnToTop();
}

MagicLvCursor001::~MagicLvCursor001() {
}
