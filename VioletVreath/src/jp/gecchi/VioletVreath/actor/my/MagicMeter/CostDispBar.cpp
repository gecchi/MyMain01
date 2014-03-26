#include "stdafx.h"
#include "CostDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

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
    setQty(0);
}

void CostDispBar::onActive() {
    positionAs(pSourceBar_);
    _sx = pSourceBar_->_sx;
    setQty(0);
}

void CostDispBar::processBehavior() {
    _x = pSourceBar_->_x + PX_C(pSourceBar_->getBarPx()); //pSourceBar_先端の座標
    if (getQty() > 0) {
        //正の値は主メーターの増分値を青で示すようにする。
        getUvFlipper()->setActivePtn(4);//青
    } else if (getQty() < 0) {
        //負の値は主メーターの削減値を赤で示すようにする。
        getUvFlipper()->setActivePtn(0);//赤
    }
//    if ( pPxQty_->getPx() > 0) {
//        //正の値はコスト有りを表す。主メーターの削減値を赤で示すようにする。
//        getUvFlipper()->setActivePtn(0);//赤
//        pixcoord px = pSourceBar_->pPxQty_->getPx() - pPxQty_->getPx();
//        if (px > 0) {
//            _x = pSourceBar_->_x +  PX_C(px);
//            setScaleR(pPxQty_->getPx() * rate_org_width_, 1.0); //横方向に倍率で伸ばす
//        } else {
//            //元メーターからははみ出ないようにする
//            _x = pSourceBar_->_x;
//            _sx = pSourceBar_->_sx;
//        }
//    } else {
//        //負の値はコストがマイナス、つまり元の値が増える。主メーターの増分値を青で示すようにする。
//        getUvFlipper()->setActivePtn(1);
//        _x = pSourceBar_->_x + PX_C(pSourceBar_->pPxQty_->getPx());
//        setScaleR(-1.0 * pPxQty_->getPx() * rate_org_width_, 1.0); //横方向に倍率で伸ばす
//    }
//    getUvFlipper()->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
