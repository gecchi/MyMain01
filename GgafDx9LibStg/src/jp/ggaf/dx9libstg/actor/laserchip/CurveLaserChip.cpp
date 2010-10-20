#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;


CurveLaserChip::CurveLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "CurveLaserChip";
    _tmpX = 0;
    _tmpY = 0;
    _tmpZ = 0;
}

void CurveLaserChip::initialize() {
    //初期設定です。
    //30px/frame の移動速度
    //当たり判定あり。
    //α＝0.99
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    _pMover->setMvVelo(30000);
    _fAlpha = 0.99;
}


void CurveLaserChip::onActive() {
    //レーザーチップ出現時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}

void CurveLaserChip::onInactive() {
    //レーザーチップ消失時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onInactive() メソッドも呼び出してください。
    LaserChip::onInactive();
}

void CurveLaserChip::processBehavior() {
    LaserChip::processBehavior();
    _pMover->behave();
    //座標をコピー
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}
void CurveLaserChip::processSettlementBehavior() {
    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。

    if (_pChip_front == NULL) {
        //先端
        if (_pChip_behind != NULL && _pChip_behind->isActive()) {
            //普通の先端
        } else {
            //先端で末端
            //どこへでもいきなはれ
        }
    } else if (_pChip_behind == NULL) {
        //末端
        if (_pChip_front != NULL && _pChip_front->isActive()) {
            //普通の末端

        } else {
            //末端で先端
            //どこへでもいきなはれ
        }
    } else if (_pChip_front->isActive() && _pChip_behind->isActive()) {
        //_pChip_behind == NULL の判定だけではだめ。_pChip_behind->isActive()と判定すること
        //なぜならemployの瞬間に_pChip_behind != NULL となるが、active()により有効になるのは次フレームだから
        //_X,_Y,_Z にはまだ変な値が入っている。
        CurveLaserChip* pF = (CurveLaserChip*)_pChip_front;
        CurveLaserChip* pB = (CurveLaserChip*)_pChip_behind;
        //中間座標に再設定
        _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
        _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
        _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
        _pMover->_veloVxMv = (pF->_pMover->_veloVxMv + _pMover->_veloVxMv + pB->_pMover->_veloVxMv) / 3;
        _pMover->_veloVyMv = (pF->_pMover->_veloVyMv + _pMover->_veloVyMv + pB->_pMover->_veloVyMv) / 3;
        _pMover->_veloVzMv = (pF->_pMover->_veloVzMv + _pMover->_veloVzMv + pB->_pMover->_veloVzMv) / 3;
    }
    LaserChip::processSettlementBehavior();
}

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

