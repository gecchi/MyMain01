#include "CostDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CostDispBar::CostDispBar(const char* prm_name, GraphBarActor* prm_pTargetSourceBar)
      : GraphBarActor(prm_name, "CostDispBar") {
    _class_name = "CostDispBar";
    pSourceBar_ = prm_pTargetSourceBar;
}

void CostDispBar::initialize() {
    setAlpha(0.7); //負の値も使う
}

void CostDispBar::onReset() {
    positionAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setVal(0);
}

void CostDispBar::onActive() {
    positionAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setVal(0);
}

void CostDispBar::processBehavior() {
    _x = pSourceBar_->_x + PX_C(pSourceBar_->getBarPx()); //pSourceBar_先端の座標
    if (getVal() > 0) {
        //正の値は主メーターの増分値を青で示すようにする。
        getUvFlipper()->setActivePtn(4);//青
    } else if (getVal() < 0) {
        //負の値は主メーターの削減値を赤で示すようにする。
        getUvFlipper()->setActivePtn(0);//赤
    }
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
