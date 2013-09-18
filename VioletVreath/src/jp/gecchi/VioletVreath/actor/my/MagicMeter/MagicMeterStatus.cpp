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
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    MagicMeter* pMM = pMagicMeter_;
    MagicList::Elem* pElem = pMM->lstMagic_.getElemFirst();
    Magic* pMagic;
    const int len_magics = pMM->lstMagic_.length();
    const coord mm_w = PX_C(pMM->width_px_);
    const coord mm_h = PX_C(pMM->height_px_);
    const float alpha1 = pMM->getAlpha()*4; //メータよりちょっと濃い目に表示
    const coord mm_X = pMM->_X;
    const coord mm_Y = pMM->_Y;
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        //各メーター下段表示（現在のレベルの残時間表示）
        if (pMagic->level_ > 0) {
            setAlpha(alpha1);
            _X = mm_X + mm_w*i;
            _Y = mm_Y + mm_h;
            sprintf(aBuf_, "%06d", (int)((pMagic->lvinfo_[pMagic->level_].remainingtime_of_effect_)*(1.0/60.0)));
            update(aBuf_);
            StringBoardActor::processDraw();
        }

        _X = mm_X + mm_w*(i+1); //i+1 は右隣に表示
        //各マジックレベル要素
        float rr = pMM->paFloat_rr_[i];
        if (rr > 0.1) {
            for (int j = 1; j <= pMagic->level_; j++) {
                setAlpha(rr);
                _Y = mm_Y - (mm_h*(j+1)*rr); //j+1 の +1 は最下段が nothing の為
                sprintf(aBuf_, "%06d", (int)((pMagic->lvinfo_[j].remainingtime_of_effect_)*(1.0/60.0)));
                update(aBuf_);
                StringBoardActor::processDraw();
            }
        }
        pElem = pElem->_pNext;
    }
}

MagicMeterStatus::~MagicMeterStatus() {
}

