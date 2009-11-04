#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


HomingLaserChip::HomingLaserChip(const char* prm_name, const char* prm_model) :
    LaserChip(prm_name, prm_model) {
    _class_name = "HomingLaserChip";
}

void HomingLaserChip::initialize() {
    //初期設定です。
    //30px/frame の移動速度
    //当たり判定あり。
    //α＝0.99
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    _pMover->setMoveVelocity(30000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    //_pStgChecker->setHitAreaBox(1, -30000, -30000, -30000, 30000, 30000, 30000);
    setBumpable(true);
    _fAlpha = 0.99;
}


void HomingLaserChip::onActive() {
    //レーザーチップ出現時処理
    HomingLaserChip* pChip_front = (HomingLaserChip*)_pChip_front;
    if (_pChip_front == NULL) {
        //自身が先頭の場合
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_vX = _pMover->_vX;
        _begining_vY = _pMover->_vY;
        _begining_vZ = _pMover->_vZ;
        _begining_RzMoveAngle = _pMover->_angRzMove;
        _begining_RyMoveAngle = _pMover->_angRyMove;
        _begining_target_RzMoveAngle = _pMover->_angTargetRzMove;
        _begining_target_RyMoveAngle = _pMover->_angTargetRyMove;
    } else {
        _begining_X = pChip_front->_begining_X;
        _begining_Y = pChip_front->_begining_Y;
        _begining_Z = pChip_front->_begining_Z;
        _begining_vX = pChip_front->_begining_vX;
        _begining_vY = pChip_front->_begining_vY;
        _begining_vZ = pChip_front->_begining_vZ;
        _begining_RzMoveAngle = pChip_front->_begining_RzMoveAngle;
        _begining_RyMoveAngle = pChip_front->_begining_RyMoveAngle;
        _begining_target_RzMoveAngle = pChip_front->_begining_target_RzMoveAngle;
        _begining_target_RyMoveAngle = pChip_front->_begining_target_RyMoveAngle;

        _X = _begining_X;
        _Y = _begining_Y;
        _Z = _begining_Z;
        _pMover->_vX = _begining_vX;
        _pMover->_vY = _begining_vY;
        _pMover->_vZ = _begining_vZ;
        _pMover->_angRzMove = _begining_RzMoveAngle;
        _pMover->_angRyMove = _begining_RyMoveAngle;
        _pMover->_angTargetRzMove = _begining_target_RzMoveAngle;
        _pMover->_angTargetRyMove = _begining_target_RyMoveAngle;
    }



    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
}

void HomingLaserChip::onInactive() {
    //レーザーチップ消失時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onInactive() メソッドも呼び出してください。
    LaserChip::onInactive();
}

void HomingLaserChip::processBehavior() {
    //レーザーチップ消失時処理
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの processBehavior() メソッドも呼び出してください。
    _dwActiveFrame++;
    //座標に反映
    if (_dwActiveFrame > 1) {
        _pMover->behave();
    }
}

void HomingLaserChip::processJudgement() {
    LaserChip::processJudgement();
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

HomingLaserChip::~HomingLaserChip() {
}

