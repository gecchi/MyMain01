#include "MagicLvCursor002.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"



using namespace GgafLib;
using namespace VioletVreath;


MagicLvCursor002::MagicLvCursor002(const char* prm_name, MagicMeter* prm_pMagicMeter, Magic* prm_pMagic) :
        MagicLvCursor(prm_name, "MagicLvCursor002", prm_pMagicMeter, prm_pMagic) {
    _class_name = "MagicLvCursor002";
}
void MagicLvCursor002::initialize() {
    MagicLvCursor::initialize();
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 2);
    pUvFlipper->setActivePtnToTop();
}

void MagicLvCursor002::moveSmoothTo(int prm_lv, frame prm_spent) {
    MagicLvCursor::moveSmoothTo(prm_lv, prm_spent, 0.3f, 0.7f); //じわ～っと移動
}

void MagicLvCursor002::dispDisable() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    int lock_ptn_no = 3; //最後のパターンの次はロック表示
    pUvFlipper->setFlipPtnRange(lock_ptn_no,lock_ptn_no); //ロック表示
    pUvFlipper->setActivePtn(lock_ptn_no);
}

void MagicLvCursor002::dispEnable() {
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 2);
    pUvFlipper->setActivePtnToTop();
}

MagicLvCursor002::~MagicLvCursor002() {
}
