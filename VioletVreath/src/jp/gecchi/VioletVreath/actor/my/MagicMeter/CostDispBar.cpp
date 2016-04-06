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
    setAlpha(0.7); //���̒l���g��
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
    _x = pSourceBar_->_x + PX_C(pSourceBar_->getBarPx()); //pSourceBar_��[�̍��W
    if (getVal() > 0) {
        //���̒l�͎僁�[�^�[�̑����l��Ŏ����悤�ɂ���B
        getUvFlipper()->setActivePtn(4);//��
    } else if (getVal() < 0) {
        //���̒l�͎僁�[�^�[�̍팸�l��ԂŎ����悤�ɂ���B
        getUvFlipper()->setActivePtn(0);//��
    }
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
