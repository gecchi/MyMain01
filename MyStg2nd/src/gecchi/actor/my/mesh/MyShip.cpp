#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define S_OPTION 0

//1/√2
#define NANAME 0.7

MyShip::MyShip(const char* prm_name) : DefaultMorphMeshActor(prm_name, "M/4/donatu") {
    _class_name = "MyShip";
    GameGlobal::_pMyShip = this;
    /** 移動スピードレベル */
    _lv_MoveSpeed = 2;
    /** 移動スピードレベルに相応する移動スピード */
    _iMoveSpeed = 5000;


    //CommonSceneがnewの場合設定
    //キャッシュロード
    //GgafDx9SeManager::get("laser001");
    _angRXVelo_BeginMZ = 1000; //奥又は手前へ通常Z通常移動開始時のX軸回転角速度の初速度
    _angRXAcce_MZ = 300; //奥又は手前へ通常Z移動中のX軸回転角速度の初角加速度
    _angRXTopVelo_MZ = 5000; //奥又は手前へ通常Z移動中のX軸回転角速度の上限角速度
    _angRXStop_MZ = 90000; //奥又は手前へ通常Z移動中のX軸回転角の目標停止角度

    _angRXVelo_BeginMZT = 23000; //奥又は手前へTurbo移動開始時のX軸回転角速度の初速度

    _iMvBtmVelo_MT = 0; //Turbo移動中の移動速度の最低速度
    _iMvVelo_BeginMT = _iMoveSpeed * 3; //Turbo移動開始時の移動速度の初速度
    _iMvAcce_MT = -200; //Turbo移動中の移動速度の加速度

    _way = WAY_FRONT;

    MyOptionParent* pMyOptionParent = NEW MyOptionParent("MY_OPTION_PARENT");
    addSubLast(pMyOptionParent);

}

void MyShip::initialize() {
    _pMyShots001Rotation = NEW RotationActor("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateTreeImmediately();
        _pMyShots001Rotation->addSubLast(pShot);
    }
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyShots001Rotation);

    _pMyWaves001Rotation = NEW RotationActor("RotWave001");
    MyWave001* pWave;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pWave = NEW MyWave001("MY_Wave001");
        pWave->inactivateTreeImmediately();
        _pMyWaves001Rotation->addSubLast(pWave);
    }
    getLordActor()->accept(KIND_MY_SHOT_GU, _pMyWaves001Rotation);

    _pLaserChipRotation = NEW LaserChipRotationActor("MyRotLaser");
    MyLaserChip001* pChip;
    for (int i = 0; i < 30; i++) { //レーザーストック
        Sleep(2); //工場に気を使う。
        stringstream name;
        name <<  "MyLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyLaserChip001(name2.c_str());
        pChip->inactivateImmediately();
        _pLaserChipRotation->addLaserChip(pChip);
    }
    getLordActor()->accept(KIND_MY_SHOT_GU, _pLaserChipRotation);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }

    setBumpable(true);
    _pChecker->useHitAreaBoxNum(1);
    _pChecker->setHitAreaBox(0, -20000, -20000, -20000, 20000, 20000, 20000);
    _pGeoMover->setMoveVelocity(0);
}

void MyShip::processBehavior() {
    _stc = VB::getBeingPressedStick();
///////////モーフテスト////////////////
    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
        _pMorpher->loopTriangleWave(1, 30, 3, 22);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
        _pMorpher->stopImmediately(1);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
        _pMorpher->intoTargetAccelerationStep(2, 1.0, 0, 0.002);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_8)) {
        _pMorpher->intoTargetAccelerationStep(2, 0, 0, -0.004);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
        _pMorpher->loopTriangleWave(3, 20, 13, 2);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_9)) {
        _pMorpher->stopImmediately(3);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
        _pMorpher->loopTriangleWave(4, 60, 3, 20);
    } else if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
        _pMorpher->stopImmediately(4);
    }

    _pMorpher->behave();
///////////モーフテスト////////////////

    if (_stc != 0) {
//////////////////////////
        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            switch (_stc) {
                case VB_UP_STC:
                    _pGeoMover->addRzMoveAngle(1000);
                    break;
                case VB_UP_RIGHT_STC:
                    _pGeoMover->addRzMoveAngle(1000);
                    _pGeoMover->addRyMoveAngle(-1000);
                    break;
                case VB_UP_LEFT_STC:
                    _pGeoMover->addRzMoveAngle(1000);
                    _pGeoMover->addRyMoveAngle(1000);
                    break;
                case VB_LEFT_STC:
                    _pGeoMover->addRyMoveAngle(1000);
                    break;
                case VB_RIGHT_STC:
                    _pGeoMover->addRyMoveAngle(-1000);
                    break;
                case VB_DOWN_STC:
                    _pGeoMover->addRzMoveAngle(-1000);
                    break;
                case VB_DOWN_RIGHT_STC:
                    _pGeoMover->addRzMoveAngle(-1000);
                    _pGeoMover->addRyMoveAngle(-1000);
                    break;
                case VB_DOWN_LEFT_STC:
                    _pGeoMover->addRzMoveAngle(-1000);
                    _pGeoMover->addRyMoveAngle(1000);
                    break;
                default:
                    break;
            }
            _pGeoMover->setRotAngle(AXIS_Z, _pGeoMover->_angRzMove);
            _pGeoMover->setRotAngle(AXIS_Y, _pGeoMover->_angRyMove);

        } else {
//////////////////////



        if (VB::isPushedDown(_stc)) { //方向シングルプッシュ
            if (MyShip::isDoublePushedDown(_stc)) { //方向ダブルプッシュ
                if (VB::isBeingPressed(VB_ZMOVE)) {
                    turnFaceNeutralXY();
                    turnFaceXZMove(_stc);
                    beginTurboXZ(_stc);
                } else {
                    turnFaceNeutralXZ();
                    turnFaceXYMove(_stc);
                    beginTurboXY(_stc);
                }
            } else {
                //方向ダブルプッシュでない＝方向シングルプッシュ
                if (VB::isBeingPressed(VB_ZMOVE)) {
                    turnFaceNeutralXY();
                    turnFaceXZMove(_stc);
                    moveXZ(_stc);
                } else {
                    turnFaceNeutralXZ();
                    turnFaceXYMove(_stc);
                    moveXY(_stc);
                }
            }

        } else {

            //方向押しっぱ
            if (VB::isBeingPressed(VB_ZMOVE)) {
                turnFaceXZMove(_stc);
                turnFaceXYMove(_stc);
                moveXZ(_stc);

            } else {
                turnFaceNeutralXZ();
                turnFaceXYMove(_stc);
                moveXY(_stc);

            }
        }
//////////////
        }
//////////////
    } else {
        if (VB::isBeingPressed(VB_ZMOVE)) {
            //ニュートラルターボ
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralXZ();
        } else {
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralXZ();
        }
    }

    //X軸転落ち着け
    if (_pGeoMover->_angveloRot[AXIS_X] > _angRXTopVelo_MZ) {
        _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pGeoMover->_angveloRot[AXIS_X] < -1*_angRXTopVelo_MZ) {
        _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2);
    }

    ////////////////////////////////////////////////////

    //ショット関連処理
    //MyShip::transactShot(this);
    if (VB::isPushedDown(VB_SHOT1)) {
        MyShot001* pShot = (MyShot001*)_pMyShots001Rotation->obtain();
        if (pShot != NULL) {
            pShot->activateTree();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isBeingPressed(VB_SHOT2)) {//isBeingPressed
        //RotationActorの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
        MyLaserChip001* pLaser = (MyLaserChip001*)_pLaserChipRotation->obtain();
        if (pLaser != NULL) {
            pLaser->_pGeoMover->_vX = _pGeoMover->_vX;
            pLaser->_pGeoMover->_vY = _pGeoMover->_vY;
            pLaser->_pGeoMover->_vZ = _pGeoMover->_vZ;
            pLaser->_pGeoMover->_angRzMove = _pGeoMover->_angRzMove;
            pLaser->_pGeoMover->_angRyMove = _pGeoMover->_angRyMove;
            static angle wk;
            if ((0<=_pGeoMover->_angRzMove && _pGeoMover->_angRzMove < ANGLE90) ||
                (ANGLE270<=_pGeoMover->_angRzMove && _pGeoMover->_angRzMove < ANGLE360) ) {
                wk = 0;
            } else {
                wk = ANGLE180;
            }
            pLaser->_pGeoMover->_angRot[AXIS_X] = wk;
            pLaser->_pGeoMover->_angRot[AXIS_Z] = _pGeoMover->_angRzMove;
            pLaser->_pGeoMover->_angRot[AXIS_Y] = _pGeoMover->_angRyMove;
            pLaser->_pGeoMover->behave();
            pLaser->setGeometry(this);

            //pLaser->_frame_on_change_to_active_flg = _lifeframe;
        }
    }

    //ショットボタン
    if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyWave001* pWave = (MyWave001*)_pMyWaves001Rotation->obtain();
        if (pWave != NULL) {
            pWave->activateTree();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pEffectExplosion001Rotation->obtain();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isBeingPressed(VB_SHOT3)) {
        setAlpha(getAlpha()-0.01);
        //equipOption();
    }

    if (VB::isBeingPressed(VB_POWERUP)) {
        _SX -= 300;
        _SY -= 300;
        _SZ -= 300;
    }
    if (VB::isBeingPressed(VB_CONTROL)) {
        _SX += 300;
        _SY += 300;
        _SZ += 300;
    }

    //座標に反映
    _pGeoMover->behave();
    _pChecker->behave();
    _pRing_GeoHistory->next()->set(_X, _Y, _Z);
}

void MyShip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
    _TRACE_("MyShipヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}


void MyShip::beginTurboXZ(int prm_VB) {
    _pGeoMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pGeoMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pGeoMover->setMoveAcceleration(_iMvAcce_MT);
    switch(prm_VB) {

        case VB_UP_STC: //奥
            _way = WAY_ZLEFT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE270);
            _pGeoMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_RIGHT_STC:
            _way = WAY_ZLEFT_FRONT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE315);
            _pGeoMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_BEHIND;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE225);
            _pGeoMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_RIGHT_STC:
            _way = WAY_FRONT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE0);
            break;

        case VB_LEFT_STC:
            _way = WAY_BEHIND;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE180);
            break;

        case VB_DOWN_STC:
            _way = WAY_ZRIGHT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE90);
            _pGeoMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_FRONT;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE45);
            _pGeoMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_DOWN_LEFT_STC:
            _way = WAY_ZRIGHT_BEHIND;
            _pGeoMover->setRzRyMoveAngle(0, ANGLE135);
            _pGeoMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;
        default:
            break;
        }
}


void MyShip::beginTurboXY(int prm_VB) {
    _pGeoMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pGeoMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pGeoMover->setMoveAcceleration(_iMvAcce_MT);

    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_UP;
            _pGeoMover->setRzRyMoveAngle(ANGLE90, 0);
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_UP_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE45, 0);
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_UP_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE135, 0);
            break;
        case VB_LEFT_STC:
            _way = WAY_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE180, 0);
            break;
        case VB_RIGHT_STC:
            _way = WAY_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE0, 0);
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _pGeoMover->setRzRyMoveAngle(ANGLE270, 0);
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_DOWN_FRONT;
            _pGeoMover->setRzRyMoveAngle(ANGLE315, 0);
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_DOWN_BEHIND;
            _pGeoMover->setRzRyMoveAngle(ANGLE225, 0);
            break;
        default:
            break;
    }
}

void MyShip::moveXY(int prm_VB) {
    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_UP;
            _Y += _iMoveSpeed;
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_UP_FRONT;
            _Y += _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_UP_BEHIND;
            _Y += _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
            break;
        case VB_LEFT_STC:
            _way = WAY_BEHIND;
            _X -= _iMoveSpeed;
            break;
        case VB_RIGHT_STC:
            _way = WAY_DOWN_FRONT;
            _way = WAY_FRONT;
            _X += _iMoveSpeed;
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _Y -= _iMoveSpeed;
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_DOWN_FRONT;
            _Y -= _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_DOWN_BEHIND;
            _Y -= _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
            break;
        default:
            break;
    }
}

void MyShip::moveXZ(int prm_VB) {
    static angle distwk;
    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_ZLEFT;
            _Z += _iMoveSpeed;
            distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE); //反時計回りの距離
            if (0 < distwk && distwk <= ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pGeoMover->setAutoTargetRotAngle(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_ZLEFT_FRONT;
            _Z += _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;

            distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, _angRXStop_MZ/2, TURN_COUNTERCLOCKWISE); //反時計回りの距離
            if (0 < distwk && distwk <= ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ/2);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ/2);
            }
            _pGeoMover->setAutoTargetRotAngle(AXIS_X, _angRXStop_MZ/2, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_BEHIND;
            _Z += _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;

            distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, _angRXStop_MZ/2, TURN_COUNTERCLOCKWISE); //反時計回りの距離
            if (0 < distwk && distwk <= ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ/2);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ/2);
            }
            _pGeoMover->setAutoTargetRotAngle(AXIS_X, _angRXStop_MZ/2, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_LEFT_STC:
            _way = WAY_BEHIND;
            _X -= _iMoveSpeed;
            break;
        case VB_RIGHT_STC:
            _way = WAY_FRONT;
            _X += _iMoveSpeed;
            break;
        case VB_DOWN_STC:
            _way = WAY_ZRIGHT;
            _Z -= _iMoveSpeed;
            distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE); //時計回りの距離
            if (-1*ANGLE360 < distwk && distwk < -1*ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (-1*ANGLE180 <= distwk && distwk < 0) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pGeoMover->setAutoTargetRotAngle(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_FRONT;
            _Z -= _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
            distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ/2, TURN_CLOCKWISE); //時計回りの距離
            if (-1*ANGLE360 < distwk && distwk < -1*ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (-1*ANGLE180 <= distwk && distwk < 0) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pGeoMover->setAutoTargetRotAngle(AXIS_X, -1*_angRXStop_MZ/2, TURN_CLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_ZRIGHT_BEHIND;
            _Z -= _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
            distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ/2, TURN_CLOCKWISE); //時計回りの距離
            if (-1*ANGLE360 < distwk && distwk < -1*ANGLE180) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (-1*ANGLE180 <= distwk && distwk < 0) {
                _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pGeoMover->setAutoTargetRotAngle(AXIS_X, -1*_angRXStop_MZ/2, TURN_CLOCKWISE, _angRXTopVelo_MZ);
            break;
        default:
            break;
    }
}


void MyShip::turnFaceXYMove(int prm_VB) {

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
}

void MyShip::turnFaceXZMove(int prm_VB) {
}

void MyShip::turnFaceNeutralXY() {
}

void MyShip::turnFaceNeutralXZ() {

    angle distwk = _pGeoMover->getDifferenceFromRotAngleTo(AXIS_X, 0, TURN_COUNTERCLOCKWISE); //反時計回りの距離
    if (0 < distwk && distwk < ANGLE180) {
        _pGeoMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
    } else if (ANGLE180 < distwk && distwk < ANGLE360) {
        _pGeoMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
    }
    _pGeoMover->setAutoTargetRotAngle(AXIS_X, 0, TURN_BOTH, _angRXTopVelo_MZ);
}

void MyShip::doNotingMoveInput() {

}

void MyShip::transactShot(GgafDx9UntransformedActor* prm_pActor) {

}

void MyShip::equipOption() {
//
//    if (_state.eq_option >= EQ_MAX_OPTION) {
//        return;
//    }
//    MyOption* pOption = (MyOption*)_pSubFirst;
//    for (int i = 0; i < _state.eq_option; i++) {
//        pOption = (MyOption*)(pOption->getNext());
//    }
//    if (_state.eq_option == 0) {
//        pOption->setRadicalActor(this);
//    } else {
//        pOption->setRadicalActor((GgafDx9UntransformedActor*)pOption->getPrev());
//    }
//
//    _state.eq_option++;
//    pOption->activate();

}

MyShip::~MyShip() {
    DELETE_IMPOSSIBLE_NULL(_pRing_GeoHistory);
}


bool MyShip::isDoublePushedDown(int prm_VB) {
    //過去に遡りながら検証
    static VB::VBMap* pVBMap;
    DWORD dwFrameApply;
    DWORD dwFrameAgo = 1;
    pVBMap = VB::getPastVBMap(dwFrameAgo);
    //直前は必ず押されていてはは駄目
    if (pVBMap->_state[prm_VB] == false) {

        dwFrameAgo++;
        //その前の5フレーム以内のどこかで押していなければならない
        dwFrameApply = dwFrameAgo + 6;//許容フレーム
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if (pVBMap->_state[prm_VB]) {
                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            return false; //不合格
        }

        //さらにそこから以前5フレーム以内のどこかで押されていては駄目
        dwFrameApply = dwFrameAgo + 6;//許容フレーム
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if (pVBMap->_state[prm_VB] == false) {

                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            return false; //不合格
        }
        return true;

    } else {
        return false;
    }

}

