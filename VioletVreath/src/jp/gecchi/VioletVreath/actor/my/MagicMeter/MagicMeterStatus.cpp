#include "stdafx.h"
#include "MagicMeterStatus.h"

#include <stdio.h>
#include "jp/ggaf/dxcore/effect/GgafDxBoardSetEffect.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

MagicMeterStatus::MagicMeterStatus(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        StringBoardActor(prm_name, "Gecchi_8Font")
{
    _class_name = "MagicMeterStatus";
    pMagicMeter_ = prm_pMagicMeter;
}

void MagicMeterStatus::initialize() {
}

void MagicMeterStatus::processBehavior() {
}

void MagicMeterStatus::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    MagicMeter* pMM = pMagicMeter_;
    MagicList::Elem* pElem = pMM->lstMagic_.getElemFirst();
    Magic* pMagic;
    int len_magics = pMM->lstMagic_.length();
    coord mm_w = PX_C(pMM->width_px_);
    coord mm_h = PX_C(pMM->height_px_);
    float alpha1 = pMM->getAlpha()*4; //���[�^��肿����ƔZ���ڂɕ\��
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        //�e���[�^�[���i�\���i���݂̃��x���̎c���ԕ\���j
        if (pMagic->level_ > 0) {
            setAlpha(alpha1);
            _X = pMM->_X + mm_w*i;
            _Y = pMM->_Y + mm_h;
            sprintf(aBuf_, "%06d", (pMagic->lvinfo_[pMagic->level_].remainingtime_of_effect_)/60);
            update(aBuf_);
            StringBoardActor::processDraw();
        }

        _X = pMM->_X + mm_w*(i+1); //i+1 �͉E�ׂɕ\��
        //�e�}�W�b�N���x���v�f
        float rr = pMM->paFloat_rr_[i];
        if (rr > 0.1) {
            for (int j = 1; j <= pMagic->level_; j++) {
                setAlpha(rr);
                _Y = pMM->_Y - (mm_h*(j+1)*rr); //j+1 �� +1 �͍ŉ��i�� nothing �̈�
                sprintf(aBuf_, "%06d", (pMagic->lvinfo_[j].remainingtime_of_effect_)/60);
                update(aBuf_);
                StringBoardActor::processDraw();
            }
        }
        pElem = pElem->_pNext;
    }
}

MagicMeterStatus::~MagicMeterStatus() {
}

