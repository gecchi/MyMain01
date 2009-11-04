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
    //独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
    //その際 は、本クラスの onActive() メソッドも呼び出してください。
    LaserChip::onActive();
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;

    //レーザーチップ出現時処理
    if (pChip_front == NULL) {
        //自身が先頭の場合
        _begining_X = _X;
        _begining_Y = _Y;
        _begining_Z = _Z;
        _begining_vX = _pMover->_vX;
        _begining_vY = _pMover->_vY;
        _begining_vZ = _pMover->_vZ;
        _begining_RzMoveAngle = _pMover->_angRzMove;
        _begining_RyMoveAngle = _pMover->_angRyMove;

    } else {
        _begining_X = pChip_front->_begining_X;
        _begining_Y = pChip_front->_begining_Y;
        _begining_Z = pChip_front->_begining_Z;
        _begining_vX = pChip_front->_begining_vX;
        _begining_vY = pChip_front->_begining_vY;
        _begining_vZ = pChip_front->_begining_vZ;
        _begining_RzMoveAngle = pChip_front->_begining_RzMoveAngle;
        _begining_RyMoveAngle = pChip_front->_begining_RyMoveAngle;

        _X = _begining_X;
        _Y = _begining_Y;
        _Z = _begining_Z;
        _pMover->_vX = _begining_vX;
        _pMover->_vY = _begining_vY;
        _pMover->_vZ = _begining_vZ;
        _pMover->_angRzMove = _begining_RzMoveAngle;
        _pMover->_angRyMove = _begining_RyMoveAngle;
    }




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
    HomingLaserChip* pChip_front =  (HomingLaserChip*)_pChip_front;
    if (_dwActiveFrame > 1) {
        //ActorDispatcher::employ() は
        //取得できる場合、ポインタを返すと共に、そのアクターはアクター発送者のサブの一番後ろに移動される。
        //したがって、レーザーの先頭から順番にprocessBehavior() が呼ばれるため、以下のようにすると
        //数珠繋ぎになる。
        if (pChip_front == NULL) {
            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;

            processBehaviorHeadChip();
        } else {

            _prev_X  = _X;
            _prev_Y  = _Y;
            _prev_Z  = _Z;
            _prev_RX = _RX;
            _prev_RY = _RY;
            _prev_RZ = _RZ;

            _X  = pChip_front->_prev_X;
            _Y  = pChip_front->_prev_Y;
            _Z  = pChip_front->_prev_Z;
            _RX = pChip_front->_prev_RX;
            _RY = pChip_front->_prev_RY;
            _RZ = pChip_front->_prev_RZ;
        }
    }
}

void HomingLaserChip::processJudgement() {
    LaserChip::processJudgement();
    GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld);
}

HomingLaserChip::~HomingLaserChip() {
}

