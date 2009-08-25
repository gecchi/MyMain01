#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


StraightLaserChip::StraightLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _pSourceActor = NULL;
}
void StraightLaserChip::initialize() {
    //下位レーザーチップでオーバーライトされている可能性あり
    _pMover->setVxMoveVelocity(100000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.9;
}

void StraightLaserChip::onActive() {
    //・・・
    _X_onActive = _X;
    _Y_onActive = _Y;
    _Z_onActive = _Z;
    _RX = _pSourceActor->_RX;
    _RY = _pSourceActor->_RY;
    _RZ = _pSourceActor->_RZ;
    _X = 0;
    _Y = 0;
    _Z = 0;

    //出現時
    _chip_kind = 1;
    if (_pChip_front == NULL) {
        if (_pDispatcher->_pSeConnection) {
            _pDispatcher->_pSeConnection->view()->play();
        }
    }

    _pDispatcher->_num_chip_active++;

    GgafDx9GeometricActor::getWorldMatrix_RxRzRyScMv(this, _matWorld);
    //俺はFKをやろうとしてるのか？！・・・・

    if (_pChip_front != NULL) {
        processPreJudgement();

    } else {
        _rev_pos_Z = 0;
    }

}


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


    GgafDx9GeometricActor::getWorldMatrix_ScMvRxRzRy(this, _matWorld);
}


StraightLaserChip::~StraightLaserChip() {

}

