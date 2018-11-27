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
    _x = pSourceBar_->_x + pSourceBar_->getWidth(); //pSourceBar_先端の座標
    pixcoord bar_width = getPix();
    if (bar_width >= 0) {
        getUvFlipper()->setActivePtn(4);//青
        setAlign(ALIGN_LEFT);
        setWidth(PX_C(bar_width));
    } else {
        getUvFlipper()->setActivePtn(0);//赤
        setAlign(ALIGN_RIGHT);
        setWidth(PX_C(-bar_width));
    }
    DefaultFramedBoardActor::processPreDraw();
}
void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
