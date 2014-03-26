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
    setAlpha(0.7); //���̒l���g��
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
    _x = pSourceBar_->_x + PX_C(pSourceBar_->getBarPx()); //pSourceBar_��[�̍��W
    if (getQty() > 0) {
        //���̒l�͎僁�[�^�[�̑����l��Ŏ����悤�ɂ���B
        getUvFlipper()->setActivePtn(4);//��
    } else if (getQty() < 0) {
        //���̒l�͎僁�[�^�[�̍팸�l��ԂŎ����悤�ɂ���B
        getUvFlipper()->setActivePtn(0);//��
    }
//    if ( pPxQty_->getPx() > 0) {
//        //���̒l�̓R�X�g�L���\���B�僁�[�^�[�̍팸�l��ԂŎ����悤�ɂ���B
//        getUvFlipper()->setActivePtn(0);//��
//        pixcoord px = pSourceBar_->pPxQty_->getPx() - pPxQty_->getPx();
//        if (px > 0) {
//            _x = pSourceBar_->_x +  PX_C(px);
//            setScaleR(pPxQty_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
//        } else {
//            //�����[�^�[����͂͂ݏo�Ȃ��悤�ɂ���
//            _x = pSourceBar_->_x;
//            _sx = pSourceBar_->_sx;
//        }
//    } else {
//        //���̒l�̓R�X�g���}�C�i�X�A�܂茳�̒l��������B�僁�[�^�[�̑����l��Ŏ����悤�ɂ���B
//        getUvFlipper()->setActivePtn(1);
//        _x = pSourceBar_->_x + PX_C(pSourceBar_->pPxQty_->getPx());
//        setScaleR(-1.0 * pPxQty_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
//    }
//    getUvFlipper()->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
