#include "MagicMeterStatus.h"

#include <stdio.h>
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"

using namespace GgafLib;
using namespace VioletVreath;

MagicMeterStatus::MagicMeterStatus(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        FontBoardActor(prm_name, "Gecchi_8Font")
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
    const coord mm_x = pMM->_x;
    const coord mm_y = pMM->_y;
    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->getValue();//一周したのでアクティブであるはず
        //各メーター下段表示（現在のレベルの残時間表示）
        if (pMagic->level_ > 0) {
            setAlpha(alpha1);
            _x = mm_x + mm_w*i;
            _y = mm_y + mm_h;
            sprintf(aBuf_, "%06d", (int)((pMagic->lvinfo_[pMagic->level_].remained_frame_of_effecting)* CONFIG::FRAME_SEC ));
            update(aBuf_);
            FontBoardActor::processDraw();
        }

        _x = mm_x + mm_w*(i+1); //i+1 は右隣に表示
        //各マジックレベル要素
        float rr = pMM->r_roll_[i];
        if (rr > 0.1) {
            for (int j = 1; j <= pMagic->level_; j++) {
                setAlpha(rr);
                _y = mm_y - (mm_h*(j+1)*rr); //j+1 の +1 は最下段が nothing の為
                sprintf(aBuf_, "%06d", (int)(   (pMagic->lvinfo_[j].remained_frame_of_effecting)*CONFIG::FRAME_SEC ) );
                update(aBuf_);
                FontBoardActor::processDraw();
            }
        }
        pElem = pElem->_pNext;
    }
}

MagicMeterStatus::~MagicMeterStatus() {
}

