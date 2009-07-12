#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

#define S_OPTION 0

//1/√2
#define NANAME 0.7

MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "X/vic2") {
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
    _pDispatcher_MyShots001 = NEW ActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    getLordActor()->accept(KIND_MY_SHOT_GU, _pDispatcher_MyShots001);

    _pDispatcher_MyWaves001 = NEW ActorDispatcher("RotWave001");
    MyWave001* pWave;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pWave = NEW MyWave001("MY_Wave001");
        pWave->inactivateImmediately();
        _pDispatcher_MyWaves001->addSubLast(pWave);
    }
    getLordActor()->accept(KIND_MY_SHOT_GU, _pDispatcher_MyWaves001);

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    MyLaserChip001* pChip;
    for (int i = 0; i < 30; i++) { //レーザーストック
        Sleep(2); //工場に気を使う。
        stringstream name;
        name <<  "MyLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyLaserChip001(name2.c_str());
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addLaserChip(pChip);
    }
    getLordActor()->accept(KIND_MY_SHOT_GU, _pLaserChipDispatcher);

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }

    setBumpable(true);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -20000, -20000, -20000, 20000, 20000, 20000);
    _pMover->setMoveVelocity(0);
    _pScaler->setScaleRange(1000, 3000);
}

void MyShip::processBehavior() {
    _stc = VB::getBeingPressedStick();

    ///////////スケーリングテスト////////////////
        if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
            _pScaler->intoTargetScaleLinerUntil(2000, 60);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
            _pScaler->intoTargetScaleLinerStep(3000, 10);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
            _pScaler->intoTargetScaleAccelerationStep(8000, 0, 3);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
            _pScaler->beatLiner(20, -1);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_5)) {
            _pScaler->beatLiner(10, 5);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_6)) {
            _pScaler->beat(20, 2 ,5, -1);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
            _pScaler->stopImmediately();
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
            _pScaler->resetScale();
        }
        _pScaler->behave();
    ///////////モーフテスト////////////////

    if (_stc != 0) {
//////////////////////////
        if (GgafDx9Input::isBeingPressedKey(DIK_SPACE)) {
            switch (_stc) {
                case VB_UP_STC:
                    _pMover->addRzMoveAngle(1000);
                    break;
                case VB_UP_RIGHT_STC:
                    _pMover->addRzMoveAngle(1000);
                    _pMover->addRyMoveAngle(-1000);
                    break;
                case VB_UP_LEFT_STC:
                    _pMover->addRzMoveAngle(1000);
                    _pMover->addRyMoveAngle(1000);
                    break;
                case VB_LEFT_STC:
                    _pMover->addRyMoveAngle(1000);
                    break;
                case VB_RIGHT_STC:
                    _pMover->addRyMoveAngle(-1000);
                    break;
                case VB_DOWN_STC:
                    _pMover->addRzMoveAngle(-1000);
                    break;
                case VB_DOWN_RIGHT_STC:
                    _pMover->addRzMoveAngle(-1000);
                    _pMover->addRyMoveAngle(-1000);
                    break;
                case VB_DOWN_LEFT_STC:
                    _pMover->addRzMoveAngle(-1000);
                    _pMover->addRyMoveAngle(1000);
                    break;
                default:
                    break;
            }
            _pMover->setRotAngle(AXIS_Z, _pMover->_angRzMove);
            _pMover->setRotAngle(AXIS_Y, _pMover->_angRyMove);

        } else {
//////////////////////



        if (VB::isPushedDown(_stc)) { //方向シングルプッシュ
            if (MyShip::isDoublePushedDown(_stc)) { //方向ダブルプッシュ
                if (VB::isBeingPressed(VB_XMOVE)) {
                    turnFaceNeutralZY();
                    turnFaceXYMove(_stc);
                    beginTurboXY(_stc);
                } else {
                    turnFaceNeutralXY();
                    turnFaceZYMove(_stc);
                    beginTurboZY(_stc);

                }
            } else {
                //方向ダブルプッシュでない＝方向シングルプッシュ
                if (VB::isBeingPressed(VB_XMOVE)) {
                    turnFaceNeutralXY();
                    turnFaceZYMove(_stc);
                    moveZY(_stc);
                } else {
                    turnFaceNeutralZY();
                    turnFaceXYMove(_stc);
                    moveXY(_stc);
                }
            }

        } else {

            //方向押しっぱ
            if (VB::isBeingPressed(VB_XMOVE)) {
                turnFaceNeutralZY();
                turnFaceXYMove(_stc);
                moveXY(_stc);
            } else {
                turnFaceZYMove(_stc);
                turnFaceXYMove(_stc);
                moveZY(_stc);
            }
        }
//////////////
        }
//////////////
    } else {
        if (VB::isBeingPressed(VB_XMOVE)) {
            //ニュートラルターボ
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralZY();
        } else {
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralZY();
        }
    }

    //X軸転落ち着け
    if (_pMover->_angveloRot[AXIS_X] > _angRXTopVelo_MZ) {
        _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pMover->_angveloRot[AXIS_X] < -1*_angRXTopVelo_MZ) {
        _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2);
    }

    ////////////////////////////////////////////////////

    //ショット関連処理
    //MyShip::transactShot(this);
    if (VB::isPushedDown(VB_SHOT1)) {
        MyShot001* pShot = (MyShot001*)_pDispatcher_MyShots001->employ();
        if (pShot != NULL) {
            pShot->activateTree();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
            if (pExplo001 != NULL) {
                pExplo001->setGeometry(this);
            }
        }
    }

    if (VB::isBeingPressed(VB_SHOT2)) {//isBeingPressed
        //ActorDispatcherの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる。
        MyLaserChip001* pLaser = (MyLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaser != NULL) {
            pLaser->_pMover->_vX = _pMover->_vX;
            pLaser->_pMover->_vY = _pMover->_vY;
            pLaser->_pMover->_vZ = _pMover->_vZ;
            pLaser->_pMover->_angRzMove = _pMover->_angRzMove;
            pLaser->_pMover->_angRyMove = _pMover->_angRyMove;
            static angle wk;
            if ((0<=_pMover->_angRzMove && _pMover->_angRzMove < ANGLE90) ||
                (ANGLE270<=_pMover->_angRzMove && _pMover->_angRzMove < ANGLE360) ) {
                wk = 0;
            } else {
                wk = ANGLE180;
            }
            pLaser->_pMover->_angRot[AXIS_X] = wk;
            pLaser->_pMover->_angRot[AXIS_Z] = _pMover->_angRzMove;
            pLaser->_pMover->_angRot[AXIS_Y] = _pMover->_angRyMove;
            pLaser->_pMover->behave();
            pLaser->setGeometry(this);

            //pLaser->_frame_on_change_to_active_flg = _lifeframe;
        }
    }

    //ショットボタン
    if (VB::arePushedDownAtOnce(VB_SHOT1, VB_SHOT2)) {
        MyWave001* pWave = (MyWave001*)_pDispatcher_MyWaves001->employ();
        if (pWave != NULL) {
            pWave->activateTree();

            EffectExplosion001* pExplo001 =
                    (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
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
        _pScaler->increaseScale(-200);
    }
    if (VB::isBeingPressed(VB_CONTROL)) {
        _pScaler->increaseScale(200);    }

    //座標に反映
    _pMover->behave();
    _pStgChecker->behave();
    _pRing_GeoHistory->next()->set(_X, _Y, _Z);

    //_TRACE_("_S = "<<_SX<<","<<_SY<<","<<_SZ);
}

void MyShip::processJudgement() {
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
}

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("MyShipヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}


void MyShip::beginTurboZY(int prm_VB) {
    _pMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pMover->setMoveAcceleration(_iMvAcce_MT);
    switch(prm_VB) {

        case VB_LEFT_STC: //奥
            _way = WAY_ZLEFT;
            _pMover->setRzRyMoveAngle(0, ANGLE270);
            _pMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_UP;
            _pMover->setRzRyMoveAngle(ANGLE45, ANGLE270);
            _pMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_DOWN_LEFT_STC:
            _way = WAY_ZLEFT_DOWN;
            _pMover->setRzRyMoveAngle(ANGLE315, ANGLE270);
            _pMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_STC:
            _way = WAY_UP;
            _pMover->setRzRyMoveAngle(ANGLE90, 0);
            break;

        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _pMover->setRzRyMoveAngle(ANGLE270, 0);
            break;

        case VB_RIGHT_STC: //手前
            _way = WAY_ZRIGHT;
            _pMover->setRzRyMoveAngle(0, ANGLE90);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_RIGHT_STC:
            _way = WAY_ZRIGHT_UP;
            _pMover->setRzRyMoveAngle(ANGLE45, ANGLE90);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_DOWN;
            _pMover->setRzRyMoveAngle(ANGLE315, ANGLE135);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;
        default:
            break;
        }
}


void MyShip::beginTurboXY(int prm_VB) {
    _pMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pMover->setMoveAcceleration(_iMvAcce_MT);

    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_UP;
            _pMover->setRzRyMoveAngle(ANGLE90, 0);
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_UP_FRONT;
            _pMover->setRzRyMoveAngle(ANGLE45, 0);
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_UP_BEHIND;
            _pMover->setRzRyMoveAngle(ANGLE135, 0);
            break;
        case VB_LEFT_STC:
            _way = WAY_BEHIND;
            _pMover->setRzRyMoveAngle(ANGLE180, 0);
            break;
        case VB_RIGHT_STC:
            _way = WAY_FRONT;
            _pMover->setRzRyMoveAngle(ANGLE0, 0);
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _pMover->setRzRyMoveAngle(ANGLE270, 0);
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_DOWN_FRONT;
            _pMover->setRzRyMoveAngle(ANGLE315, 0);
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_DOWN_BEHIND;
            _pMover->setRzRyMoveAngle(ANGLE225, 0);
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

void MyShip::moveZY(int prm_VB) {
    static angle distwk, angRX;
    switch (prm_VB) {
        case VB_LEFT_STC:
            _way = WAY_ZLEFT;
            _Z += _iMoveSpeed;
            distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE); //反時計回りの距離
            if (0 < distwk && distwk <= ANGLE180) {
                _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pMover->setTargetRotAngle(AXIS_X, _angRXStop_MZ, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_UP;
            _Z += _iMoveSpeed * NANAME;
            _Y += _iMoveSpeed * NANAME;
            angRX = _angRXStop_MZ - (_angRXStop_MZ/2);
            distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, angRX, TURN_COUNTERCLOCKWISE); //反時計回りの距離
            if (0 < distwk && distwk <= ANGLE180) {
                _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pMover->setTargetRotAngle(AXIS_X, angRX, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_ZLEFT_DOWN;
            _Z += _iMoveSpeed * NANAME;
            _Y -= _iMoveSpeed * NANAME;
            angRX = _angRXStop_MZ + (_angRXStop_MZ/2);
            distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, angRX, TURN_COUNTERCLOCKWISE); //反時計回りの距離
            if (0 < distwk && distwk <= ANGLE180) {
                _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (ANGLE180 < distwk && distwk < ANGLE360) {
                _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pMover->setTargetRotAngle(AXIS_X, angRX, TURN_COUNTERCLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _Y -= _iMoveSpeed;
            break;
        case VB_UP_STC:
            _way = WAY_UP;
            _Y += _iMoveSpeed;
            break;
        case VB_RIGHT_STC:
            _way = WAY_ZRIGHT;
            _Z -= _iMoveSpeed;
            distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE); //時計回りの距離
            if (-1*ANGLE360 < distwk && distwk < -1*ANGLE180) {
                _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (-1*ANGLE180 <= distwk && distwk < 0) {
                _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pMover->setTargetRotAngle(AXIS_X, -1*_angRXStop_MZ, TURN_CLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_ZRIGHT_UP;
            _Z -= _iMoveSpeed * NANAME;
            _Y += _iMoveSpeed * NANAME;
            angRX = _angRXStop_MZ - (_angRXStop_MZ/2);
            distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, -1*angRX, TURN_CLOCKWISE); //時計回りの距離
            if (-1*ANGLE360 < distwk && distwk < -1*ANGLE180) {
                _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (-1*ANGLE180 <= distwk && distwk < 0) {
                _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pMover->setTargetRotAngle(AXIS_X, -1*angRX, TURN_CLOCKWISE, _angRXTopVelo_MZ);
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_DOWN;
            _Z -= _iMoveSpeed * NANAME;
            _Y -= _iMoveSpeed * NANAME;
            angRX = _angRXStop_MZ + (_angRXStop_MZ/2);
            distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, -1*angRX, TURN_CLOCKWISE); //時計回りの距離
            if (-1*ANGLE360 < distwk && distwk < -1*ANGLE180) {
                _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
            } else if (-1*ANGLE180 <= distwk && distwk < 0) {
                _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
            }
            _pMover->setTargetRotAngle(AXIS_X, -1*angRX, TURN_CLOCKWISE, _angRXTopVelo_MZ);
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

void MyShip::turnFaceZYMove(int prm_VB) {
}

void MyShip::turnFaceNeutralXY() {
}

void MyShip::turnFaceNeutralZY() {

    angle distwk = _pMover->getDifferenceFromRotAngleTo(AXIS_X, 0, TURN_COUNTERCLOCKWISE); //反時計回りの距離
    if (0 < distwk && distwk < ANGLE180) {
        _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ);
    } else if (ANGLE180 < distwk && distwk < ANGLE360) {
        _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ);
    }
    _pMover->setTargetRotAngle(AXIS_X, 0, TURN_BOTH, _angRXTopVelo_MZ);
}

void MyShip::doNotingMoveInput() {

}

void MyShip::transactShot(GgafDx9GeometricActor* prm_pActor) {

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
//        pOption->setRadicalActor((GgafDx9GeometricActor*)pOption->getPrev());
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

