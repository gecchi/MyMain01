#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define S_OPTION 0

//1/√2
#define NANAME 0.7

MyShip::MyShip(const char* prm_name) : DefaultPrimitiveActor(prm_name, "X/cube22", "default") {
//MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "M/ebi2") {
    _class_name = "MyShip";
    GameGlobal::_pMyShip = this;
    /** 移動スピードレベル */
    _lv_MoveSpeed = 2;
    /** 移動スピードレベルに相応する移動スピード */
    _iMoveSpeed = 4000;

    //CommonSceneがnewの場合設定
    _iShotKind01 = 0;
    _iShotKind02 = 0;
    _iShotKind03 = 0;

    //キャッシュロード
    //GgafDx9SeManager::get("laser001");

    //	_angRXVelo_BeginMZ = 100;
    //	_angRXAcce_MZ = 100;
    //	_angRXTopVelo_MZ = 5000;
    //	_angRXStop_MZ = 85000;
    //
    //	_iMvVelo_BeginMT = 5000;
    //	_iMvAcce_MT = -100;
    //	_iMvBtmVelo_MT = 1000;
    //
    //	_angRXVelo_BeginMZT = 10000;
    //	_angRXAcce_MZT = -200;
    //	_angRXBtmVelo_MZT = _angRXTopVelo_MZ;
    //
    //
    //	_angRXTopVelo_MNZ = 2000;
    //	_angRXAcce_MNZ = 100;

    _tmpX = _X;
    _tmpY = _Y;
    _tmpZ = _Z;

    _angRZVelo_BeginMY = 100; //上又は下へ通常移動開始時のZ軸回転角速度の初速度
    _angRZTopVelo_MY = 2000; //上又は下へ移動中のZ軸回転角速度の上限角速度
    _angRZAcce_MY = 200; //上又は下へ通常移動中のZ軸回転角速度の角加速度
    _angRZStop_MY = 30000; //上又は下へ通常Z移動中のZ軸回転角の停止角度

    _iMvBtmVelo_MT = 1000; //TURBO移動中の移動速度の最低速度
    _iMvVelo_BeginMT = _iMoveSpeed * 5; //TURBO移動開始時の移動速度の初速度
    _iMvAcce_MT = -200; //TURBO移動中の移動速度の加速度

    _iMvAcce_EOD_MT = -500; //TURBO中に逆方向に入力される事により加算される（減速する）速度

    _angRZVelo_BeginMYT = 13000; //上又は下へTURBO移動開始時のZ軸回転角速度の初速度
    _angRZAcce_MYT = -200; //上又は下へTURBO移動中のZ軸回転角速度の角加速度
    _angRZBtmVelo_MYT = 3000; //上又は下へTURBO移動中のZ軸回転角速度の最低速度

    _angRZTopVelo_MNY = 2000; //上又は下へ通常移動時、自動的にAngle0に戻ろうとするZ軸回転角速度の上限角速度
    _angRZAcce_MNY = 100; //上又は下へ通常移動時、自動的にAngle0に戻ろうとする時のZ軸回転角加速度(正負共通)

    _dwFrameNextXYTurboOut = 0; //XY次回ターボ終了フレーム
    _dwIntervalXYTurbo = 60; //XYターボ終了フレーム間隔


    _dwFrameTurboMove = 0; //ターボ経過フレーム
    _dwFrameXYTurboMove = 0; //ターボ経過フレーム

    _dwIntervalFinshTurbo = 60;

    _angFaceTurnRange = 30000;//振り向き許容アングる
    _angRotVelo_FaceTurn = 2000;

    _needTurnFaceNeutralXY = true;
    _needTurnFaceXYMove = false;

    _dwFrameNomalMove = 0; //通常移動経過フレーム
    _wayTurbo = WAY_NONE;
    _dRate_TurboControl = 0.8; //ターボ中移動制御できる割合
    _iTurboControl = 0;

    _pMyShots001Rotation = NEW RotationActor("RotShot001");
    addSubLast(_pMyShots001Rotation); //仮所属
    MyShot001* pShot;
    for (int i = 0; i < 50; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001", "S/moji2");
        pShot->inactImmediately();
        _pMyShots001Rotation->addSubLast(pShot);
    }

    _pMyWaves001Rotation = NEW RotationActor("RotWave001");
    addSubLast(_pMyWaves001Rotation);//仮所属
    MyWave001* pWave;
    for (int i = 0; i < 50; i++) { //自弾ストック
        pWave = NEW MyWave001("MY_Wave001", "M/wave");
        pWave->inactImmediately();
        _pMyWaves001Rotation->addSubLast(pWave);
    }

    _pMyLaserChipRotation = NEW MyLaserChipRotationActor("ROTLaser");
    addSubLast(_pMyLaserChipRotation);
//    _pMyLaserChipRotation = NEW RotationActor("RotLaser001");
//    addSubLast(_pMyLaserChipRotation);//仮所属
//    MyLaserChip2* pChip;
//    for (int i = 0; i < 100; i++) { //レーザーストック
//        pChip = NEW MyLaserChip2("MYS_MyLaserChip2", "m/laserchip9");
//        pChip->inactImmediately();
//        _pMyLaserChipRotation->addSubLast(pChip);
//    }

    for (int i = 0; i < EQ_MAX_OPTION; i++) {
        MyOption* pOption = NEW MyOption("MY_OPTION", "M/ebi");
        pOption->_iMyNo = i; //おぷ番
        pOption->inactImmediatelyAlone();
        addSubLast(pOption);
    }

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 200; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }

}

void MyShip::initialize() {
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyShots001Rotation->tear());
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyWaves001Rotation->tear());
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyLaserChipRotation->tear());

    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -10000, -10000, 10000, 10000);
    _pGeoMover->setMoveVelocity(0);

    //_pGeoMover->setRotAngleVelocityRenge(AXIS_Y, -300000, -300000);
	_pGeoMover->setRotAngleVelocity(AXIS_X,700);
    _pGeoMover->setRotAngleVelocity(AXIS_Y,1000);
    _pGeoMover->setRotAngleVelocity(AXIS_Z,1300);


}

void MyShip::processBehavior() {

    static int stc;
    if (VB::isPushedDown(VB_TURBO) != 0 && _dwFrameTurboMove > 2) {
        stc = VB::getBeingPressedStick();
        if (stc != 0) {
            //			_TRACE_("XYターボ始動");
            beginTurboXY(stc);
        } else {
            //			_TRACE_("ただターボPushDownしただけ");
            doNotingMoveInput();
            turnFaceNeutralXY();
        }
    } else if (VB::isBeingPressed(VB_TURBO)) {
        //		_TRACE_("ただターボおしっぱなししてるだけ");
        doNotingMoveInput();
        turnFaceNeutralXY();
    } else {
        stc = VB::getBeingPressedStick();
        if (stc != 0) {
            if (_wayTurbo == WAY_NONE) {
                //				_TRACE_("XY移動制御");
                moveXY(stc);
                turnFaceXYMove(stc);
            } else {
                //				_TRACE_("ターボ中XY制御");
                controlTurboXY(stc);
            }
        } else {
            //な～んにもしてない
            doNotingMoveInput();
            turnFaceNeutralXY();
        }
    }

    _dwFrameTurboMove++;
    _dwFrameXYTurboMove++;
    if (_dwFrameTurboMove > _dwIntervalFinshTurbo) {
        _wayTurbo = WAY_NONE;
        _pGeoMover->setMoveVelocityRenge(0, 10000000);
        _pGeoMover->setMoveVelocity(0);
    }

    ////////////////////////////////////////////////////

    //ショット関連処理
    //MyShip::transactShot(this);
    if (VB::isPushedDown(VB_SHOT1)) {
        MyShot001* pShot = (MyShot001*)_pMyShots001Rotation->obtain();
        if (pShot != NULL) {
            pShot->act();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isBeingPressed(VB_SHOT2)) {
        //RotationActorの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
        MyLaserChip2* pLaser = (MyLaserChip2*)_pMyLaserChipRotation->obtain();
        if (pLaser != NULL) {
            pLaser->setRadicalActor(this);
            //pLaser->_dwFrame_switchedToActFlg = _dwFrame;
        }
    }

    //ショットボタン
    if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyWave001* pWave = (MyWave001*)_pMyWaves001Rotation->obtain();
        if (pWave != NULL) {
            pWave->act();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isPushedDown(VB_SHOT3)) {
        equipOption();
    }

    if (VB::isBeingPressed(VB_POWERUP)) {
        _SX -= 1000;
        _SY -= 1000;
        _SZ -= 1000;
    }
    if (VB::isBeingPressed(VB_GUARD)) {
        _SX += 1000;
        _SY += 1000;
        _SZ += 1000;
    }

    //座標に反映
    _pGeoMover->behave();
}

void MyShip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
    farewell();
}

void MyShip::beginTurboXY(int prm_VB) {
    _dwFrameTurboMove = 0;
    _dwFrameXYTurboMove = 0;
    _pGeoMover->setMoveVelocityRenge(_iMvBtmVelo_MT, 10000000);
    _pGeoMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pGeoMover->setMoveAcceleration(_iMvAcce_MT);

    switch (prm_VB) {

        case VB_UP_STC:
            _wayTurbo = WAY_UP;
            _pGeoMover->setRzRyMoveAngle(ANGLE90, 0);
            break;

        case VB_UP_RIGHT_STC:
            _wayTurbo = WAY_UP_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE45, 0);
            break;

        case VB_UP_LEFT_STC:
            _wayTurbo = WAY_UP_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE135, 0);
            break;

        case VB_LEFT_STC:
            _wayTurbo = WAY_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE180, 0);
            break;

        case VB_RIGHT_STC:
            _wayTurbo = WAY_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE0, 0);
            break;

        case VB_DOWN_STC:
            _wayTurbo = WAY_DOWN;
            _pGeoMover->setRzRyMoveAngle(ANGLE270, 0);
            break;

        case VB_DOWN_RIGHT_STC:
            _wayTurbo = WAY_DOWN_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE315, 0);
            break;

        case VB_DOWN_LEFT_STC:
            _wayTurbo = WAY_DOWN_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE225, 0);
            break;

        default:

            break;
    }

}

void MyShip::moveXY(int prm_VB) {
    switch (prm_VB) {

        case VB_UP_STC:
            _Y += _iMoveSpeed;
            break;

        case VB_UP_RIGHT_STC:
            _Y += _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
            break;

        case VB_UP_LEFT_STC:
            _Y += _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
            break;

        case VB_LEFT_STC:
            _X -= _iMoveSpeed;
            break;

        case VB_RIGHT_STC:
            _X += _iMoveSpeed;
            break;

        case VB_DOWN_STC:
            _Y -= _iMoveSpeed;
            break;

        case VB_DOWN_RIGHT_STC:
            _Y -= _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
            break;

        case VB_DOWN_LEFT_STC:
            _Y -= _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
            break;

        default:
            break;
    }
}

void MyShip::controlTurboXY(int prm_VB) {
    switch (prm_VB) {

        case VB_UP_STC:
            if (_wayTurbo == WAY_DOWN) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y += _iMoveSpeed;
            }
            break;

        case VB_UP_RIGHT_STC:
            if (_wayTurbo == WAY_DOWN_BEHIND) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y += _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            }
            break;

        case VB_UP_LEFT_STC:
            if (_wayTurbo == WAY_DOWN_FRONT) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y += _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            }
            break;

        case VB_LEFT_STC:
            if (_wayTurbo == WAY_FRONT) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _X -= _iMoveSpeed;
            }
            break;

        case VB_RIGHT_STC:
            if (_wayTurbo == WAY_BEHIND) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _X += _iMoveSpeed;
            }
            break;

        case VB_DOWN_STC:
            if (_wayTurbo == WAY_UP) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y -= _iMoveSpeed;
            }
            break;

        case VB_DOWN_RIGHT_STC:
            if (_wayTurbo == WAY_UP_BEHIND) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y -= _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            }
            break;

        case VB_DOWN_LEFT_STC:
            if (_wayTurbo == WAY_UP_FRONT) {
                _pGeoMover->setMoveVelocityRenge(-1 * _iMoveSpeed, 10000000);
                _pGeoMover->addMoveVelocity(_iMvAcce_EOD_MT);
            } else {
                _pGeoMover->setMoveVelocityRenge(0, 10000000);
                _Y -= _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            }
            break;

        default:
            break;
    }
}
void MyShip::turnFaceXYMove(int prm_VB) {

    if (_needTurnFaceXYMove) {
        switch (prm_VB) {

            case VB_UP_STC:
                break;

            case VB_UP_RIGHT_STC:
                break;

            case VB_UP_LEFT_STC:
                break;

            case VB_LEFT_STC:
                break;

            case VB_RIGHT_STC:
                break;

            case VB_DOWN_STC:
                break;

            case VB_DOWN_RIGHT_STC:
                break;

            case VB_DOWN_LEFT_STC:
                break;

            default:
                break;
        }

        _needTurnFaceXYMove = false;
        _needTurnFaceNeutralXY = true;
    }
}

void MyShip::turnFaceNeutralXY() {
    //ロール（仰角、俯角）を元に戻す
    if (_needTurnFaceNeutralXY) {
        _pGeoMover->setRotAngleVelocityRenge(AXIS_Z, -1 * _angRZTopVelo_MNY, _angRZTopVelo_MNY);
        _pGeoMover->setRotAngleAcceleration(AXIS_Z, sgn(_pGeoMover->getDistanceFromRotAngleTo(AXIS_Z, 0, TURN_CLOSE_TO)) * _angRZAcce_MNY);
        _pGeoMover->setAutoTargetRotAngle(AXIS_Z, 0, TURN_BOTH);
        _needTurnFaceNeutralXY = false;
        _needTurnFaceXYMove = true;
    }
}

void MyShip::doNotingMoveInput() {

}

void MyShip::transactShot(GgafDx9UntransformedActor* prm_pActor) {

}

void MyShip::equipOption() {

    if (_state.eq_option >= EQ_MAX_OPTION) {
        return;
    }
    MyOption* pOption = (MyOption*)_pSubFirst;
    for (int i = 0; i < _state.eq_option; i++) {
        pOption = (MyOption*)(pOption->getNext());
    }
    if (_state.eq_option == 0) {
        pOption->setRadicalActor(this);
    } else {
        pOption->setRadicalActor((GgafDx9UntransformedActor*)pOption->getPrev());
    }

    _state.eq_option++;
    pOption->actAlone();

}

MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}

