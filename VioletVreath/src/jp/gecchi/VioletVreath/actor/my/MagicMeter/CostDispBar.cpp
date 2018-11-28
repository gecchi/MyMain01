#include "CostDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CostDispBar::CostDispBar(const char* prm_name, FramedHorizontalBarActor* prm_pTargetSourceBar)
      : FramedHorizontalBarActor(prm_name, "CostDispBar") {
    _class_name = "CostDispBar";
    pSourceBar_ = prm_pTargetSourceBar;
}

void CostDispBar::initialize() {
    setAlign(ALIGN_LEFT, VALIGN_MIDDLE);
    setAlpha(0.7); //負の値も使う
}

void CostDispBar::onReset() {
    setPositionAt(pSourceBar_);
    _sy = pSourceBar_->_sy;
    setVal(0);
}

void CostDispBar::onActive() {
    setPositionAt(pSourceBar_);
    _sy = pSourceBar_->_sy;
    setVal(0);
}

void CostDispBar::processBehavior() {
}


void CostDispBar::processJudgement() {
}

void CostDispBar::processPreDraw() {
    _x = pSourceBar_->_x + pSourceBar_->getCoordWidth(); //pSourceBar_先端の座標
    coord bar_width = getCoordWidth();
    if (bar_width >= 0) {
        getUvFlipper()->setActivePtn(4);//青
        setAlign(ALIGN_LEFT);
        setValByCoordWidth(bar_width);
    } else {
        getUvFlipper()->setActivePtn(0);//赤
        setAlign(ALIGN_RIGHT);
        setValByCoordWidth(-bar_width);
    }
    FramedHorizontalBarActor::processPreDraw();
}
void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
