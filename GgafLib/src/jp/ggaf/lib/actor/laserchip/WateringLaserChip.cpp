#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WateringLaserChip::WateringLaserChip(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
            LaserChip(prm_name, prm_model, prm_pStat) {
    _class_name = "WateringLaserChip";
    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
}

void WateringLaserChip::onActive() {
    //レーザーチップ出現時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    _tmpX = _x;
    _tmpY = _y;
    _tmpZ = _z;
}

void WateringLaserChip::processBehavior() {
    //座標をコピー
    _tmpX = _x;
    _tmpY = _y;
    _tmpZ = _z;
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
        const WateringLaserChip* pF = (WateringLaserChip*)_pChip_front;
        const WateringLaserChip* pB = (WateringLaserChip*)_pChip_behind;
        if (pF && pB && pF->_is_active_flg && pB->_is_active_flg) {
            //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
            //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
            //_x,_y,_z にはまだ変な値が入っている。

            //中間座標に再設定
            _x = ((pF->_tmpX + pB->_tmpX)/2 + _tmpX)/2;
            _y = ((pF->_tmpY + pB->_tmpY)/2 + _tmpY)/2;
            _z = ((pF->_tmpZ + pB->_tmpZ)/2 + _tmpZ)/2;
        }
        LaserChip::processSettlementBehavior();
    }
}


WateringLaserChip::~WateringLaserChip() {
}

