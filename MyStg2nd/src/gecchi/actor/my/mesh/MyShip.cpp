#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;


#define S_OPTION 0
//1/√2
#define NANAME 0.7

MyShip::MyShip(const char* prm_name) : DefaultMeshActor(prm_name, "myvic") {
    _class_name = "MyShip";

    GameGlobal::init();
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

    _pDispatcher_MyShots001 = NEW ActorDispatcher("RotShot001");
    MyShot001* pShot;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pShot = NEW MyShot001("MY_MyShot001");
        pShot->inactivateImmediately();
        _pDispatcher_MyShots001->addSubLast(pShot);
    }
    addSubLast(_pDispatcher_MyShots001); //仮サブ

    _pDispatcher_MyWaves001 = NEW ActorDispatcher("RotWave001");
    MyWave001* pWave;
    for (int i = 0; i < 10; i++) { //自弾ストック
        pWave = NEW MyWave001("MY_Wave001");
        pWave->inactivateImmediately();
        _pDispatcher_MyWaves001->addSubLast(pWave);
    }
    addSubLast(_pDispatcher_MyWaves001); //仮サブ

    _pLaserChipDispatcher = NEW LaserChipDispatcher("MyRotLaser");
    MyStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        Sleep(2); //工場に気を使う。
        stringstream name;
        name <<  "MyStraightLaserChip001_" << i;
        string name2 = name.str();
        pChip = NEW MyStraightLaserChip001(name2.c_str());
        pChip->setSource(this);
        pChip->inactivateImmediately();
        _pLaserChipDispatcher->addLaserChip(pChip);
    }
    addSubLast(_pLaserChipDispatcher); //仮サブ

    //トレース用履歴
    _pRing_GeoHistory = NEW GgafLinkedListRing<GeoElement>();
    for (DWORD i = 0; i < 100; i++) {
        _pRing_GeoHistory->addLast(NEW GeoElement(GameGlobal::_pMyShip));
    }
}

void MyShip::initialize() {
    //種別に振り分け
    getLordActor()->accept(KIND_MY_SHOT_NOMAL, _pDispatcher_MyShots001->extract());
    getLordActor()->accept(KIND_MY_SHOT_NOMAL, _pDispatcher_MyWaves001->extract());
    getLordActor()->accept(KIND_MY_SHOT_NOMAL, _pLaserChipDispatcher->extract());

    setBumpable(true);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -20000, -20000, -20000, 20000, 20000, 20000);
    _pMover->setMoveVelocity(0);
    //_pScaler->setScale(4000);



    double xx[][3] = { {  1,   0,   0},
                       {  0,   1,   1},
                       {-10,   0,   0},
                       {  0,  -1,   1},
                       {  1,   0,   0},
                       {1.1, 0.1, 0.1}
                     };

    GgafDx9Spline3D sp(xx, 6);
    sp.compute(0.1);
    for (int t = 0; t < sp._rnum; t ++) {
        _TRACE_((float)sp._X_compute[t]<<"  "<< (float)sp._Y_compute[t]<<"  "<< (float)sp._Z_compute[t]);
    }

    int rZ1,rY1,rZ2,rY2;
    _TRACE_("START getRotAngleZY");
    for (int x = -30000; x < 30000; x+= 1000) {
        for (int y = -30000; y < 30000; y+= 1000) {
            for (int z = -30000; z < 30000; z+= 1000) {
                GgafDx9Util::getRotAngleZY(x,y,z,rZ1,rY1);
            }
        }
    }
    _TRACE_("DONE getRotAngleZY");
    _TRACE_("START getRotAngleZY_new");
    for (int x = -30000; x < 30000; x+= 1000) {
        for (int y = -30000; y < 30000; y+= 1000) {
            for (int z = -30000; z < 30000; z+= 1000) {
                GgafDx9Util::getRotAngleZY_new(x,y,z,rZ2,rY2);

            }
        }
    }
    _TRACE_("DONE getRotAngleZY_new");
    //_TRACE_(x<<","<<y<<","<<z<<" = ("<<rZ1<<","<<rY1<<") , ("<<rZ2<<","<<rY2<<")");

//テスト
//    int r, r_prev;
//    int x = -500000;
//    r_prev = GgafDx9Util::getAngleFromXY(-764000, x);
//    for (int y = -764000; y < 764000; y+=5000) {
//        r = GgafDx9Util::getAngleFromXY(x, y);
//        _TRACE_("x,y="<<x<<","<<y<<" r="<<r<<" 差="<<(r_prev-r));
//        r_prev = r;
//    }

    //GgafDx9Util::getAngleFromSlantテスト
//    float rad;
//    int vx;
//    int vy;
//    int r1;
//    int r2 ;
//    for (int ang = 0; ang < 36000; ang++) {
//        rad = (PI * 2.0f * ang) / 36000;
//        vx = cos(rad)*1000;
//        vy = sin(rad)*1000;
//        r1 = GgafDx9Util::getAngleFromXY(vx, vy);
//        r2 = GgafDx9Util::getAngle2D(vx, vy);
//        _TRACE_("TEST ang="<<ang<<" r1="<<r1<<" r2="<<r2);
//    }

//    _TRACE_("START getAngleFromXY");
//    for (int i = 0; i < 50000; i++) {
//        for (int ang = 0; ang < 360; ang++) {
//            rad = (PI * 2.0f * ang) / 360;
//            vx = cos(rad)*1000;
//            vy = sin(rad)*1000;
//            r1 = GgafDx9Util::getAngleFromXY(vx, vy);
//        }
//    }
//    _TRACE_("DONE getAngleFromXY "<<r1);
//    _TRACE_("START getAngle2D");
//    for (int i = 0; i < 50000; i++) {
//        for (int ang = 0; ang < 360; ang++) {
//            rad = (PI * 2.0f * ang) / 360;
//            vx = cos(rad)*1000;
//            vy = sin(rad)*1000;
//            r1 = GgafDx9Util::getAngle2D(vx, vy);
//        }
//    }
//    _TRACE_("DONE getAngle2D "<<r1);

}

void MyShip::processBehavior() {

    _stc = VB::getBeingPressedStick();

    ///////////スケーリングテスト////////////////
        if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
            _pScaler->intoTargetScaleLinerUntil(8000, 60);
        }
        if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
            _pScaler->intoTargetScaleLinerStep(8000, 10);
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
    ///////////スケーリングテスト////////////////

    if (_stc != VB_NEUTRAL_STC) {
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
            if (VB::isBeingPressed(VB_OPTION)) {
                //おぷ操作
                switch (_stc) {
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
            } else {
                if (VB::isPushedDown(_stc)) { //方向シングルプッシュ
                    if (MyShip::isDoublePushedDown(_stc)) { //方向ダブルプッシュ
                        if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
                            turnFaceNeutralXY();
                            turnFaceZXMove(_stc);
                            beginTurboZX(_stc);
                        } else {
                            turnFaceNeutralZX();
                            turnFaceXYMove(_stc);
                            beginTurboXY(_stc);
                        }
                    } else {
                        //方向ダブルプッシュでない＝方向シングルプッシュ
                        if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
                            turnFaceNeutralXY();
                            turnFaceZXMove(_stc);
                            if (VB::isBeingPressed(VB_OPTION)) {
                                turnZX(_stc);
                            } else {
                                moveZX(_stc);
                            }

                        } else {

                            turnFaceNeutralZX();
                            turnFaceXYMove(_stc);
                            if (VB::isBeingPressed(VB_OPTION)) {
                                turnXY(_stc);
                            } else {
                                moveXY(_stc);
                            }

                        }
                    }

                } else {

                    //方向押しっぱ
                    if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
                        turnFaceZXMove(_stc);
                        turnFaceXYMove(_stc);
                        moveZX(_stc);
                    } else {
                        turnFaceNeutralZX();
                        turnFaceXYMove(_stc);
                        moveXY(_stc);
                    }
                }
            }
//////////////
        }
//////////////
    } else {
        if (pCAM->_pos_camera == 1 || pCAM->_pos_camera == 2) {
            //ニュートラルターボ
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralZX();
        } else {
            doNotingMoveInput();
            turnFaceNeutralXY();
            turnFaceNeutralZX();
        }
    }

    //X軸転落ち着け
    if (_pMover->_angveloRot[AXIS_X] > _angRXTopVelo_MZ) {
        _pMover->setRotAngleAcceleration(AXIS_X, -1*_angRXAcce_MZ*2);
    } else if (_pMover->_angveloRot[AXIS_X] < -1*_angRXTopVelo_MZ) {
        _pMover->setRotAngleAcceleration(AXIS_X, _angRXAcce_MZ*2);
    }

    ////////////////////////////////////////////////////


    if (_Y > GameGlobal::_lim_MyShip_top) {
        _Y = GameGlobal::_lim_MyShip_top;
    }
    if (_Y < GameGlobal::_lim_MyShip_bottom ) {
        _Y = GameGlobal::_lim_MyShip_bottom;
    }

    if (_X > GameGlobal::_lim_MyShip_front) {
        _X = GameGlobal::_lim_MyShip_front;
    }
    if (_X < GameGlobal::_lim_MyShip_behaind) {
        _X = GameGlobal::_lim_MyShip_behaind;
    }

    if (_Z > GameGlobal::_lim_MyShip_zleft) {
        _Z = GameGlobal::_lim_MyShip_zleft;
    }
    if (_Z < GameGlobal::_lim_MyShip_zright) {
        _Z = GameGlobal::_lim_MyShip_zright;
    }


    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
        setAlpha(getAlpha()-0.01);
        //equipOption();
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
        setAlpha(getAlpha()+0.01);
        //equipOption();
    }

    if (VB::isBeingPressed(VB_BUTTON6)) {
        _pScaler->increaseScale(-200);
    }
    if (VB::isBeingPressed(VB_BUTTON5)) {
        _pScaler->increaseScale(200);
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_I)) {
        _TRACE_("(X,Y,Z)=("<<_X<<","<<_Y<<","<<_Z<<")");

    }


    //座標に反映
    _pMover->behave();
    _pStgChecker->behave();
    _pRing_GeoHistory->next()->set(_X, _Y, _Z);

    if (isOffscreen()) {
        _TRACE_("MyShip is Offscreen! = ("<<_X<<","<<_Y<<","<<_Z<<")");
    }
    //_TRACE_("_S = "<<_SX<<","<<_SY<<","<<_SZ);
}

void MyShip::processJudgement() {
    //ショット関連処理


    if (VB::isBeingPressed(VB_SHOT2)) {//isBeingPressed
        //ActorDispatcherの性質上、末尾アクターが play していなければ、全ての要素が play していないことになる?。
        MyStraightLaserChip001* pLaser = (MyStraightLaserChip001*)_pLaserChipDispatcher->employ();
        if (pLaser != NULL) {
            pLaser->setSource(this);
//            pLaser->_pMover->_vX = _pMover->_vX;
//            pLaser->_pMover->_vY = _pMover->_vY;
//            pLaser->_pMover->_vZ = _pMover->_vZ;
//            pLaser->_pMover->_angRzMove = _pMover->_angRzMove;
//            pLaser->_pMover->_angRyMove = _pMover->_angRyMove;
//            static angle wk;
//            if ((0<=_pMover->_angRzMove && _pMover->_angRzMove < ANGLE90) ||
//                (ANGLE270<=_pMover->_angRzMove && _pMover->_angRzMove < ANGLE360) ) {
//                wk = 0;
//            } else {
//                wk = ANGLE180;
//            }
//            pLaser->_pMover->_angRot[AXIS_X] = wk;
//            pLaser->_pMover->_angRot[AXIS_Z] = _pMover->_angRzMove;
//            pLaser->_pMover->_angRot[AXIS_Y] = _pMover->_angRyMove;
//            pLaser->_pMover->behave();
//            pLaser->setGeometry(this);

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
    } else if (VB::isPushedDown(VB_SHOT1) || VB::isPushedDown(VB_SHOT1_R) ) {
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
    //TRACE("DefaultActor::processJudgement " << getName() << "frame:" << prm_dwFrame);
    //_TRACE_("dep="<< (_fDistance_plnFront)<<"");
}

void MyShip::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("MyShipヒットしました。("<<_X<<","<<_Y<<","<<_Z<<")");
}


void MyShip::beginTurboZY(vbsta prm_VB) {
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
            _pMover->setRzRyMoveAngle(ANGLE315, ANGLE90);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;
        default:
            break;
    }
}


void MyShip::beginTurboZX(vbsta prm_VB) {
    _pMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pMover->setMoveAcceleration(_iMvAcce_MT);
    switch(prm_VB) {

        case VB_LEFT_STC:
            _way = WAY_ZLEFT;
            _pMover->setRzRyMoveAngle(ANGLE180, ANGLE90);
            _pMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_FRONT;
            _pMover->setRzRyMoveAngle(ANGLE180, ANGLE135);
            _pMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_DOWN_LEFT_STC:
            _way = WAY_ZLEFT_BEHIND;
            _pMover->setRzRyMoveAngle(ANGLE180, ANGLE45);
            _pMover->setRotAngleVelocity(AXIS_X, _angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_STC:
            _way = WAY_FRONT;
            _pMover->setRzRyMoveAngle(0, 0);
            break;

        case VB_DOWN_STC:
            _way = WAY_BEHIND;
            _pMover->setRzRyMoveAngle(ANGLE180, 0);
            break;

        case VB_RIGHT_STC:
            _way = WAY_ZRIGHT;
            _pMover->setRzRyMoveAngle(0, ANGLE90);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_UP_RIGHT_STC:
            _way = WAY_ZRIGHT_FRONT;
            _pMover->setRzRyMoveAngle(0, ANGLE45);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;

        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_BEHIND;
            _pMover->setRzRyMoveAngle(0, ANGLE135);
            _pMover->setRotAngleVelocity(AXIS_X, -1*_angRXVelo_BeginMZT); //勢いよく回転開始
            break;
        default:
            break;
    }
}



void MyShip::beginTurboXY(vbsta prm_VB) {
    _pMover->setMoveVelocityRenge(_iMvBtmVelo_MT, _iMvVelo_BeginMT);
    _pMover->setMoveVelocity(_iMvVelo_BeginMT);
    _pMover->setMoveAcceleration(_iMvAcce_MT);

    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_UP;
            _pMover->setRzRyMoveAngle(ANGLE90, 0);
            break;
        case VB_UP_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_UP_FRONT;
                _pMover->setRzRyMoveAngle(ANGLE45, 0);
            } else { //pCAM->_pos_camera == 3 である
                _way = WAY_UP_BEHIND;
                _pMover->setRzRyMoveAngle(ANGLE135, 0);
            }
            break;
        case VB_UP_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_UP_BEHIND;
                _pMover->setRzRyMoveAngle(ANGLE135, 0);
            } else {
                _way = WAY_UP_FRONT;
                _pMover->setRzRyMoveAngle(ANGLE45, 0);
            }
            break;
        case VB_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_BEHIND;
                _pMover->setRzRyMoveAngle(ANGLE180, 0);
            } else {
                _way = WAY_FRONT;
                _pMover->setRzRyMoveAngle(ANGLE0, 0);
            }
            break;
        case VB_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_FRONT;
                _pMover->setRzRyMoveAngle(ANGLE0, 0);
            } else {
                _way = WAY_BEHIND;
                _pMover->setRzRyMoveAngle(ANGLE180, 0);
            }
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _pMover->setRzRyMoveAngle(ANGLE270, 0);
            break;
        case VB_DOWN_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_DOWN_FRONT;
                _pMover->setRzRyMoveAngle(ANGLE315, 0);
            } else {
                _way = WAY_DOWN_BEHIND;
                _pMover->setRzRyMoveAngle(ANGLE225, 0);
            }
            break;
        case VB_DOWN_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_DOWN_BEHIND;
                _pMover->setRzRyMoveAngle(ANGLE225, 0);
            } else {
                _way = WAY_DOWN_FRONT;
                _pMover->setRzRyMoveAngle(ANGLE315, 0);
            }
            break;
        default:
            break;
    }
}

void MyShip::moveXY(vbsta prm_VB) {
    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_UP;
            _Y += _iMoveSpeed;
            break;
        case VB_UP_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_UP_FRONT;
                _Y += _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            } else {
                _way = WAY_UP_BEHIND;
                _Y += _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            }
            break;
        case VB_UP_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_UP_BEHIND;
                _Y += _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            } else {
                _way = WAY_UP_FRONT;
                _Y += _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            }
            break;
        case VB_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_BEHIND;
                _X -= _iMoveSpeed;
            } else {
                _way = WAY_FRONT;
                _X += _iMoveSpeed;
            }
            break;
        case VB_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_FRONT;
                _X += _iMoveSpeed;
            } else {
                _way = WAY_BEHIND;
                _X -= _iMoveSpeed;
            }
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            _Y -= _iMoveSpeed;
            break;
        case VB_DOWN_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_DOWN_FRONT;
                _Y -= _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            } else {
                _way = WAY_DOWN_BEHIND;
                _Y -= _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            }
            break;
        case VB_DOWN_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_DOWN_BEHIND;
                _Y -= _iMoveSpeed * NANAME;
                _X -= _iMoveSpeed * NANAME;
            } else {
                _way = WAY_DOWN_FRONT;
                _Y -= _iMoveSpeed * NANAME;
                _X += _iMoveSpeed * NANAME;
            }
            break;
        default:
            break;
    }
}

void MyShip::turnXY(vbsta prm_VB) {
    switch (prm_VB) {
        case VB_UP_STC:
            _way = WAY_UP;
            break;
        case VB_UP_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_UP_FRONT;
            } else {
                _way = WAY_UP_BEHIND;
            }
            break;
        case VB_UP_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_UP_BEHIND;
            } else {
                _way = WAY_UP_FRONT;
            }
            break;
        case VB_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_BEHIND;
            } else {
                _way = WAY_FRONT;
            }
            break;
        case VB_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_FRONT;
            } else {
                _way = WAY_BEHIND;
            }
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            break;
        case VB_DOWN_RIGHT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_DOWN_FRONT;
            } else {
                _way = WAY_DOWN_BEHIND;
            }
            break;
        case VB_DOWN_LEFT_STC:
            if (pCAM->_pos_camera == 0) {
                _way = WAY_DOWN_BEHIND;
            } else {
                _way = WAY_DOWN_FRONT;
            }
            break;
        default:
            break;
    }
}


void MyShip::moveZY(vbsta prm_VB) {
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


void MyShip::turnZY(vbsta prm_VB) {
    switch (prm_VB) {
        case VB_LEFT_STC:
            _way = WAY_ZLEFT;
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_UP;
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_ZLEFT_DOWN;
            break;
        case VB_DOWN_STC:
            _way = WAY_DOWN;
            break;
        case VB_UP_STC:
            _way = WAY_UP;
            break;
        case VB_RIGHT_STC:
            _way = WAY_ZRIGHT;
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_ZRIGHT_UP;
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_DOWN;
            break;
        default:
            break;
    }
}










void MyShip::moveZX(vbsta prm_VB) {
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
            _way = WAY_ZLEFT_FRONT;
            _Z += _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
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
            _way = WAY_ZLEFT_BEHIND;
            _Z += _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
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
            _way = WAY_BEHIND;
            _X -= _iMoveSpeed;
            break;
        case VB_UP_STC:
            _way = WAY_FRONT;
            _X += _iMoveSpeed;
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
            _way = WAY_ZRIGHT_FRONT;
            _Z -= _iMoveSpeed * NANAME;
            _X += _iMoveSpeed * NANAME;
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
            _way = WAY_ZRIGHT_BEHIND;
            _Z -= _iMoveSpeed * NANAME;
            _X -= _iMoveSpeed * NANAME;
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


void MyShip::turnZX(vbsta prm_VB) {
    switch (prm_VB) {
        case VB_LEFT_STC:
            _way = WAY_ZLEFT;
            break;
        case VB_UP_LEFT_STC:
            _way = WAY_ZLEFT_FRONT;
            break;
        case VB_DOWN_LEFT_STC:
            _way = WAY_ZLEFT_BEHIND;
            break;
        case VB_DOWN_STC:
            _way = WAY_BEHIND;
            break;
        case VB_UP_STC:
            _way = WAY_FRONT;
            break;
        case VB_RIGHT_STC:
            _way = WAY_ZRIGHT;
            break;
        case VB_UP_RIGHT_STC:
            _way = WAY_ZRIGHT_FRONT;
            break;
        case VB_DOWN_RIGHT_STC:
            _way = WAY_ZRIGHT_BEHIND;
            break;
        default:
            break;
    }
}






void MyShip::turnFaceXYMove(vbsta prm_VB) {

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

void MyShip::turnFaceZYMove(vbsta prm_VB) {
}

void MyShip::turnFaceZXMove(vbsta prm_VB) {
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

void MyShip::turnFaceNeutralZX() {

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


bool MyShip::isDoublePushedDown(vbsta prm_VB) {
    //過去に遡りながら検証
    static VB::VBMap* pVBMap;
    DWORD dwFrameApply;
    DWORD dwFrameAgo = 1;
    pVBMap = VB::getPastVBMap(dwFrameAgo);
    //直前は必ず押されていては駄目、ニュートラルでなければだめ
    if ((pVBMap->_state & prm_VB) == 0) {

        dwFrameAgo++;
        //その前の5フレーム以内のどこかで押していなければならない
        dwFrameApply = dwFrameAgo + 7;//許容フレーム
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if (pVBMap->_state & prm_VB) {
                break;
            }
        }
        if (dwFrameAgo >= dwFrameApply) {
            return false; //不合格
        }

        //さらにそこから以前5フレーム以内のどこかで押されていては駄目
        dwFrameApply = dwFrameAgo + 7;//許容フレーム
        for ( ; dwFrameAgo < dwFrameApply; dwFrameAgo++) {
            pVBMap = VB::getPastVBMap(dwFrameAgo);
            if ((pVBMap->_state & prm_VB) == 0) {

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

