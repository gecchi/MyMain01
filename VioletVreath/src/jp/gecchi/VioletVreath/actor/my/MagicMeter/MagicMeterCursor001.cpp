#include "MagicMeterCursor001.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/ggaf/dx/actor/supporter/KurokoMvAssistant.h"



using namespace GgafLib;
using namespace VioletVreath;


MagicMeterCursor001::MagicMeterCursor001(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        DefaultBoardActor(prm_name, "Cursor001") {
    _class_name = "MagicMeterCursor001";
    pMagicMeter_ = prm_pMagicMeter;
    tmp_alpha_ = _alpha;
    tx_ = 0;
    ty_ = 0;
}

void MagicMeterCursor001::initialize() {
    setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
    _x = tx_ = pMagicMeter_->_x + pMagicMeter_->width_*pMagicMeter_->lstMagic_.getCurrentIndex() + (pMagicMeter_->width_/2);
    _y = ty_ = pMagicMeter_->_y + (pMagicMeter_->height_/2);
    getUvFlipper()->setActivePtn(0);
}

void MagicMeterCursor001::onActive() {
}

void MagicMeterCursor001::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    setAlpha(pMagicMeter_->getAlpha());
    pKuroko->behave();
    if (pKuroko->asstMv()->hasJustFinishedSliding()) {
        //理想位置に補正
        _x = tx_;
        _y = ty_;
    }
    getUvFlipper()->behave();
}

void MagicMeterCursor001::processJudgement() {
}

void MagicMeterCursor001::moveTo(int prm_magic_mater_index) {
    tx_ = pMagicMeter_->_x + pMagicMeter_->width_*prm_magic_mater_index + (pMagicMeter_->width_/2);
    ty_ = pMagicMeter_->_y + (pMagicMeter_->height_/2);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setMvAngTwd(tx_, ty_);
    pKuroko->asstMv()->slideByDt(UTIL::getDistance(_x, _y, tx_, ty_), 12,
                                  0.2, 0.4, 0, true);
}

MagicMeterCursor001::~MagicMeterCursor001() {
}
