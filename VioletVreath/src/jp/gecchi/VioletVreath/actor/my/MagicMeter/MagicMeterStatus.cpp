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
    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    MagicMeter* pMM = pMagicMeter_;
    GgafLinkedListRing<Magic>::Elem* pElem = pMM->ringMagics_.getElemFirst();
    Magic* pMagic;
    int len_magics = pMM->ringMagics_.length();
    coord mm_w = PX_C(pMM->width_px_);
    coord mm_h = PX_C(pMM->height_px_);
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        //各メーター下段表示
        if (pMagic->level_ > 0) {
            setAlpha(pMM->getAlpha());
            _X = pMM->_X + mm_w*i;
            _Y = pMM->_Y + mm_h;
            sprintf(aBuf_, "%06d", (pMagic->lvinfo_[pMagic->level_].remainingtime_of_effect_)/60);
            update(aBuf_);
            StringBoardActor::processDraw();
        }

        _X = pMM->_X + mm_w*(i+1); //i+1 は右隣に表示
        //各マジック要素
        float rr = pMM->paFloat_rr_[i];
        if (rr > 0.1) {
            for (int j = 1; j <= pMagic->level_; j++) {
                setAlpha(rr);
                _Y = pMM->_Y - (mm_h*(j+1)*rr); //j+1 の +1 は最下段が nothing の為
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

