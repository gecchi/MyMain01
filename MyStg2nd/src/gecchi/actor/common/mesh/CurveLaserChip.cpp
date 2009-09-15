#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


CurveLaserChip::CurveLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "CurveLaserChip";
}

void CurveLaserChip::initialize() {
    //下位レーザーチップでオーバーライトされている可能性あり
    _pMover->setMoveVelocity(40000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}


void CurveLaserChip::onActive() {
    LaserChip::onActive();
}

void CurveLaserChip::onInactive() {
    LaserChip::onInactive();
}

void CurveLaserChip::processBehavior() {
    _dwActiveFrame++;
    //座標に反映
    if (_dwActiveFrame > 1) {
        _pMover->behave();
    }
/*
    //中間地点にも当たり判定
    static int centerX, centerY, centerZ;
    if (_pChip_front != NULL) {
      centerX = (_X - _pChip_front->_X) / 2;
      centerY = (_Y - _pChip_front->_Y) / 2;
      centerZ = (_Z - _pChip_front->_Z) / 2;
      _pStgChecker->setHitAreaBox(
                      1,
                      centerX - 30000,
                      centerY - 30000,
                      centerZ - 30000,
                      centerX + 30000,
                      centerY + 30000,
                      centerZ + 30000
                 ); //中間の当たり判定
      _pStgChecker->getHitAreaBoxs()->enable(1);
    } else {
      _pStgChecker->getHitAreaBoxs()->disable(1);

    }
*/

}

void CurveLaserChip::processJudgement() {
    LaserChip::processJudgement();
    //【注意】4/15 メモ
    //奥から描画となるので processDrawXxxx は、同一フレーム内で _pChip_front が必ずしも先に実行されとは限らない。
    //processBehavior,processJudgementは _pChip_front が必ず先に実行される。
    //描画時に_pChip_frontも使用するためここで設定しとく必要がある。
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

CurveLaserChip::~CurveLaserChip() {
}

