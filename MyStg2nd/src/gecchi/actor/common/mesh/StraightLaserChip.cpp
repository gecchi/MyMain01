#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
//    _pPosSourceActor = NULL;
//    _pAngleSourceActor = NULL;

    _pSource_X = &_X;
    _pSource_Y = &_Y;
    _pSource_Z = &_Z;
    _pSource_RX = &_RX;
    _pSource_RY = &_RY;
    _pSource_RZ = &_RZ;
    _pSource_vX = &_pMover->_vX;
    _pSource_vY = &_pMover->_vY;
    _pSource_vZ = &_pMover->_vZ;
}

void StraightLaserChip::initialize() {
    //下位レーザーチップでオーバーライトされている可能性あり
    _veloMove = 10000;
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
    _dwActiveFrame = 0;
}

void StraightLaserChip::onActive() {
    LaserChip::onActive();
    _dwActiveFrame = 0;
}

void StraightLaserChip::processBehavior() {
    _dwActiveFrame++;
    _RX = (*_pSource_RX);
    _RY = (*_pSource_RY);
    _RZ = (*_pSource_RZ);
    _X = (*_pSource_X) + ((*_pSource_vX) * 1.0 * _veloMove * _dwActiveFrame);
    _Y = (*_pSource_Y) + ((*_pSource_vY) * 1.0 * _veloMove * _dwActiveFrame);
    _Z = (*_pSource_Z) + ((*_pSource_vZ) * 1.0 * _veloMove * _dwActiveFrame);

    //座標に反映
    //_pMover->behave();
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

//void StraightLaserChip::processDraw() {
//    _TRACE_("> StraightLaserChip,(RZ,RY)=("<<_RZ<<","<<_RY<<")");
//    LaserChip::processDraw();
//    _TRACE_("< StraightLaserChip,(RZ,RY)=("<<_RZ<<","<<_RY<<")");
//}

void StraightLaserChip::processJudgement() {
    if (isOffScreen()) {
        inactivate();
    }

    //レーザー種別  1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先）
    if (_pChip_front) {
        if (_pChip_behind) {
            if (_pChip_behind->isActive()) {
                if (_pChip_front->_pChip_front) {
                    _chip_kind = 2; //中間テクスチャ
                } else {
                    _chip_kind = 3; //先頭テクスチャ
                }
            } else {
                _chip_kind = 1; //発射元の末尾テクスチャ
            }
        } else {
            _chip_kind = 1; //末尾テクスチャ
        }
    } else {
        _chip_kind = 4; //何も描画したくない
    }


    GgafDx9GeometricActor::getWorldMatrix_ScRxRzRyMv(this, _matWorld);
}


StraightLaserChip::~StraightLaserChip() {

}

