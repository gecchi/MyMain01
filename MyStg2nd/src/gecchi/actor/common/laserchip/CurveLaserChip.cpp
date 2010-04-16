﻿#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


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

//    _tmpX = 0;
//    _tmpY = 0;
//    _tmpZ = 0;
}

void CurveLaserChip::onInactive() {
    //レーザーチップ消失時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onInactive() メソッドも呼び出してください。
    LaserChip::onInactive();
}

void CurveLaserChip::processBehavior() {

    //座標に反映
    //これにより発射元の根元から表示される
    if (getPartFrame() > 0) {
        LaserChip::processBehavior();
        _pMover->behave();
    }

    //座標をコピー
    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;
}
void CurveLaserChip::processPreJudgement() {
    //平均曲線座標設定。
    //processPreJudgement() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、仕方ないのでprocessPreJudgement()に
    //食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessPreJudgement()では、先頭で呼び出した方が良い。

    if (_pChip_front == NULL) {
        //先端は何もなし
    } else if (_pChip_behind == NULL) {
        //末端
    } else if (_pChip_front->isActive() && _pChip_behind->isActive()) {
        //_pChip_behind == NULL の判定だけではだめ。_pChip_behind->isActive()と判定すること
        //なぜならemployの瞬間に_pChip_behind != NULL となるが、active()により有効になるのは次フレームだから
        //_X,_Y,_Z にはまだ変な値が入っている。
        MyCurveLaserChip001* pF = (MyCurveLaserChip001*)_pChip_front;
        MyCurveLaserChip001* pB = (MyCurveLaserChip001*)_pChip_behind;
        //中間座標に再設定
        _X = (pF->_tmpX + _tmpX + pB->_tmpX) / 3;
        _Y = (pF->_tmpY + _tmpY + pB->_tmpY) / 3;
        _Z = (pF->_tmpZ + _tmpZ + pB->_tmpZ) / 3;
    }
    LaserChip::processPreJudgement();
}

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //GgafDx9Util::setWorldMatrix_RxRzRyScMv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

