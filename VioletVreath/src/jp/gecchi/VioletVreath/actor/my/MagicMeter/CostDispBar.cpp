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
    _SX = pSourceBar_->_SX;
    setQty(0);
}

void CostDispBar::onActive() {
    positionAs(pSourceBar_);
    _SX = pSourceBar_->_SX;
    setQty(0);
}

void CostDispBar::processBehavior() {
    _X = pSourceBar_->_X + PX_C(pSourceBar_->getBarPx()); //pSourceBar_��[�̍��W
    if (getQty() > 0) {
        //���̒l�͎僁�[�^�[�̑����l��Ŏ����悤�ɂ���B
        _pUvFlipper->setActivePtn(4);//��
    } else if (getQty() < 0) {
        //���̒l�͎僁�[�^�[�̍팸�l��ԂŎ����悤�ɂ���B
        _pUvFlipper->setActivePtn(0);//��
    }
//    if ( pPxQty_->getPx() > 0) {
//        //���̒l�̓R�X�g�L���\���B�僁�[�^�[�̍팸�l��ԂŎ����悤�ɂ���B
//        _pUvFlipper->setActivePtn(0);//��
//        pixcoord px = pSourceBar_->pPxQty_->getPx() - pPxQty_->getPx();
//        if (px > 0) {
//            _X = pSourceBar_->_X +  PX_C(px);
//            setScaleR(pPxQty_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
//        } else {
//            //�����[�^�[����͂͂ݏo�Ȃ��悤�ɂ���
//            _X = pSourceBar_->_X;
//            _SX = pSourceBar_->_SX;
//        }
//    } else {
//        //���̒l�̓R�X�g���}�C�i�X�A�܂茳�̒l��������B�僁�[�^�[�̑����l��Ŏ����悤�ɂ���B
//        _pUvFlipper->setActivePtn(1);
//        _X = pSourceBar_->_X + PX_C(pSourceBar_->pPxQty_->getPx());
//        setScaleR(-1.0 * pPxQty_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
//    }
//    _pUvFlipper->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
