#include "stdafx.h"
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
    //GgafDxRectUV* pRectUV_Active;
    HRESULT hr;
    //�p���[���[�^�[
    //[====]���P�̑傫�� [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = pMagicMeter_->ringMagics_.getElemFirst();
    Magic* pMagic;
    int len_magics = pMagicMeter_->ringMagics_.length();

    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//��������̂ŃA�N�e�B�u�ł���͂�
        //�e���[�^�[���i�\��
        if (pMagic->level_ > 0) {
            setAlpha(1.0);
            _X = pMagicMeter_->_X + PX_C(pMagicMeter_->width_px_)*i;
            _Y = pMagicMeter_->_Y + PX_C(pMagicMeter_->height_px_);
            sprintf(aBuf_, "%06d", (pMagic->lvinfo_[pMagic->level_].remainingtime_of_effect_)/60);
            update(aBuf_);
            StringBoardActor::processDraw();
        }

        _X = pMagicMeter_->_X + PX_C(pMagicMeter_->width_px_)*(i+1); //i+1 �͉E�ׂɕ\��
        //�e�}�W�b�N�v�f
        float rr = pMagicMeter_->paFloat_rr_[i];
        if (rr > 0.1) {
            for (int j = 1; j <= pMagic->level_; j++) {
                setAlpha(rr);
                _Y = pMagicMeter_->_Y - (PX_C(pMagicMeter_->height_px_)*(j+1)*rr); //j+1 �� +1 �͍ŉ��i�� nothing �̈�
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

