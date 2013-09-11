#include "stdafx.h"
#include "CostDispBar.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/lib/util/AmountGraph.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

CostDispBar::CostDispBar(const char* prm_name, GraphBar* prm_pSourceBar, AmountGraph* prm_pCostValue)
      : GraphBar(prm_name, "CostDispBar", prm_pCostValue) {
    _class_name = "CostDispBar";
    pSourceBar_ = prm_pSourceBar;
//    pCostValue_ = prm_pCostValue;
}

void CostDispBar::initialize() {
    _pUvFlipper->exec(NOT_ANIMATED); //�A�j������
    setAlpha(0.7);
}

void CostDispBar::onReset() {
//    setScaleR(pCostValue_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
}

void CostDispBar::onActive() {
}

void CostDispBar::processBehavior() {
    if ( pAmount_->getPx() > 0) {
        //���̒l�̓R�X�g�L���\���B�僁�[�^�[�̍팸�l��ԂŎ����悤�ɂ���B
        _pUvFlipper->setActivePtn(0);//��
        pixcoord px = pSourceBar_->pAmount_->getPx() - pAmount_->getPx();
        if (px > 0) {
            _X = pSourceBar_->_X +  PX_C(px);
            setScaleR(pAmount_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
        } else {
            //�����[�^�[����͂͂ݏo�Ȃ��悤�ɂ���
            _X = pSourceBar_->_X;
            _SX = pSourceBar_->_SX;
        }
    } else {
        //���̒l�̓R�X�g���}�C�i�X�A�܂茳�̒l��������B�僁�[�^�[�̑����l��Ŏ����悤�ɂ���B
        _pUvFlipper->setActivePtn(1);
        _X = pSourceBar_->_X + PX_C(pSourceBar_->pAmount_->getPx());
        setScaleR(-1.0 * pAmount_->getPx() * rate_org_width_, 1.0); //�������ɔ{���ŐL�΂�
    }
    _pUvFlipper->behave();
}


void CostDispBar::processJudgement() {
}

void CostDispBar::onInactive() {
}

CostDispBar::~CostDispBar() {
}
