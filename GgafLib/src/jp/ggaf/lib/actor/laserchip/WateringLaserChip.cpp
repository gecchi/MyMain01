#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


WateringLaserChip::WateringLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "WateringLaserChip";
    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
    _middle_colli_able = true; //中間あたり判定自動生成有
}

void WateringLaserChip::onActive() {
    //レーザーチップ出現時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}

void WateringLaserChip::processBehavior() {
    _pKurokoB->behave();
    //座標をコピー
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}
void WateringLaserChip::processSettlementBehavior() {
    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        if (_pChip_front == nullptr) {
//            //先端
//            if (_pChip_behind != nullptr && _pChip_behind->isActiveInTheTree()) {
//                //普通の先端
//            } else {
//                //先端で末端
//                //どこへでもいきなはれ
//            }
        } else if (_pChip_behind == nullptr) {
//            //末端
//            if (_pChip_front != nullptr && _pChip_front->isActiveInTheTree()) {
//                //普通の末端
//            } else {
//                //末端で先端
//                //どこへでもいきなはれ
//            }
        } else if (_pChip_front->_is_active_flg && _pChip_behind->_is_active_flg) {
            //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
            //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
            //_X,_Y,_Z にはまだ変な値が入っている。
            WateringLaserChip* pF = (WateringLaserChip*)_pChip_front;
            WateringLaserChip* pB = (WateringLaserChip*)_pChip_behind;
            //中間座標に再設定
            _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3; //intの割り算だしまぁいいか
            _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
            _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
        }
        LaserChip::processSettlementBehavior();
    }
}


WateringLaserChip::~WateringLaserChip() {
}

