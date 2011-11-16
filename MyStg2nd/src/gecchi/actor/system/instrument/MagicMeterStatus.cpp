#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;

MagicMeterStatus::MagicMeterStatus(const char* prm_name, MagicMeter* prm_pMagicMeter) :
        StringBoardActor(prm_name, "Gecchi_8Font")
{
    _class_name = "MagicMeterStatus";
    _pMagicMeter = prm_pMagicMeter;
}
void MagicMeterStatus::initialize() {
}

void MagicMeterStatus::processBehavior() {
}

void MagicMeterStatus::processDraw() {
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    //GgafDxRectUV* pRectUV_Active;
    HRESULT hr;
    //パワーメーター
    //[====]が１つの大きさ [====][====][====]
    GgafLinkedListRing<Magic>::Elem* pElem = _pMagicMeter->_ringMagics.getElemFirst();
    Magic* pMagic;
    int len_magics = _pMagicMeter->_ringMagics.length();

    for (int i = 0; i < len_magics; i++) {
        pMagic = pElem->_pValue;//一周したのでアクティブであるはず
        _X = _pMagicMeter->_X + PX2CO(_pMagicMeter->_width_px)*(i+1); //i+1 は右隣に表示
        //各マジック要素
        if (pMagic->_rr > 0.1) {
            for (int j = 0; j < pMagic->_level; j++) {
                _Y = _pMagicMeter->_Y - (PX2CO(_pMagicMeter->_height_px)*(j+1)*pMagic->_rr);
                sprintf(_aBuf, "%07d", pMagic->_lvinfo[j]._remaining_time_of_effect);
                update(_aBuf);
                StringBoardActor::processDraw();
            }
        }
        pElem = pElem->_pNext;
    }
}
MagicMeterStatus::~MagicMeterStatus() {
}

