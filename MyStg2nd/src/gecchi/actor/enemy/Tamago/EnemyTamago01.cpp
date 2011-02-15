#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyTamago01::EnemyTamago01(const char* prm_name) : SpriteMeshSetActor(prm_name, "8/Flora") { //8/をいれとかないとユニークにならない

    _class_name = "EnemyTamago01";
    MyStgUtil::resetEnemyTamago01Status(_pStatus);
    _iMovePatternNo = 0;
    _pProgram_Tamago01Move = NULL;
    _pDispatcherCon = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;

    _pDispatcherCon = (DispatcherConnection*)(P_GOD->_pDispatcherManager->getConnection("DpCon_Shot001"));
    //_pDispatcher_Shot = _pDispatcherCon->refer();
_pDispatcher_Shot = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
}

void EnemyTamago01::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void EnemyTamago01::initialize() {

    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 1000);
    _pMover->setMvAng(900000, 300000, 300000);
    _pMover->setMvVelo(2);
    _pCollisionChecker->makeCollision(2);
//    _pCollisionChecker->setColliAAPrism_Cube(0, 200000,POS_PRISM_ZX_pp);
        _pCollisionChecker->setColliAAPrism_WHD(0,0,0,300000,100000,200000,100000,POS_PRISM_YZ_pn);

    //ヒットしない理由を探せ！！
//      _pCollisionChecker->setColliAAPrism_WHD(0,20000,-30000,50000,
//                                                90000,140000,60000,POS_PRISM_XY_nn);
//
      _pCollisionChecker->setColliAAPrism_WHD(1,-20000,-30000,-50000,
                                                 60000,90000,140000,POS_PRISM_ZX_pp);

//    _pCollisionChecker->setColliAAB_WHD(0,20000,-30000,50000,
//                                              90000,140000,60000);
//    _pCollisionChecker->setColliAAB_Cube(0, 50000);


    //_pCollisionChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _X = -50000;
    _Y = 200000;
    _Z = 100000;
    _pScaler->setScale(5000);
}

void EnemyTamago01::onActive() {
    MyStgUtil::resetEnemyTamago01Status(_pStatus);
    if (_pProgram_Tamago01Move) {
        _pProgram_Tamago01Move->begin(0); //スプライン移動をプログラムしておく
    }

    _pUvFlipper->setTextureUvRotation(16, 1/16.0, 1/16.0);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
    _pUvFlipper->forcePtnNoRange(0, 16*16-1);
    _pUvFlipper->setPtnNo(0);
    _iMovePatternNo = 0;
}

void EnemyTamago01::processBehavior() {

//    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
//        _pScaler->addScale(500);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
//        _pScaler->addScale(-500);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_1)) {
//        _pGgafDx9Model->_pTextureBlinker->->addScale(2000);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_2)) {
//        _pGgafDx9Model->_pTextureBlinker->->addScale(-2000);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_3)) {
//        _pGgafDx9Model->_pTextureBlinker->->intoTargetScaleAcceStep(3000, 0, 3);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_4)) {
//        _pGgafDx9Model->_pTextureBlinker->->loopLiner(20, -1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_5)) {
//        _pGgafDx9Model->_pTextureBlinker->->loopLiner(10, 5);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_6)) {
//        _pGgafDx9Model->_pTextureBlinker->->beat(20, 2 ,5, -1);
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_7)) {
//        _pGgafDx9Model->_pTextureBlinker->->stopImmediately();
//    }
//    if (GgafDx9Input::isBeingPressedKey(DIK_0)) {
//        _pGgafDx9Model->_pTextureBlinker->->setScaleToBottom();
//    }


    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_iMovePatternNo == 0) {
        //スプライン移動中
        if (_pProgram_Tamago01Move && !(_pProgram_Tamago01Move->isExecuting())) {
            _iMovePatternNo++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (_iMovePatternNo == 1) {
        //スプライン移動終了時
        _pMover->execTagettingMvAngSequence(P_MYSHIP->_X+800000, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                   2000, 0,
                                                   TURN_CLOSE_TO);
        _iMovePatternNo++; //次の行動パターンへ
    }

    if (_iMovePatternNo == 2) {
        _iMovePatternNo++;
    }

    if (_iMovePatternNo == 3) {

    }
    if (getBehaveingFrame() % 30 == 0) {
        _pMover->execTagettingMvAngSequence(P_MYSHIP, 2000,0,TURN_CLOSE_TO);

        if (_pDispatcher_Shot) {
            //放射状ショット発射
            int way = 8;
            angle* paAngWay = NEW angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            GgafDx9Util::getRzRyAng(P_MYSHIP->_X - _X, P_MYSHIP->_Y - _Y, P_MYSHIP->_Z - _Z, target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            GgafDx9Util::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            GgafDx9Util::getWayAngle2D(target_RyRz_Ry, way, 10000, paAngWay);
            GgafDx9DrawableActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng_by_RyRz(paAngWay[i], target_RyRz_Rz);
                    pActor->setCoordinateBy(this);
                    pActor->activate();
                }
            }
            DELETEARR_IMPOSSIBLE_NULL(paAngWay);
            //ショット発射エフェクト
            if (_pDispatcher_ShotEffect) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->setCoordinate(_X, _Y, _Z);
                }
            }
        }

    }
    if (_pProgram_Tamago01Move) {
        _pProgram_Tamago01Move->behave();
    }
    _pMover->behave();
    _pScaler->behave();
    _pUvFlipper->behave();
    //_pSeTransmitter->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyTamago01::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
    _pSeTransmitter->play3D(0);
    _TRACE_("HIT!!!");
    if (pExplo001) {
        pExplo001->activate();
        pExplo001->setCoordinateBy(this);
    }

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {


        //sayonara();
    }
}

void EnemyTamago01::onInactive() {
    //end();
}

EnemyTamago01::~EnemyTamago01() {
    _pDispatcherCon->close();
    DELETE_POSSIBLE_NULL(_pProgram_Tamago01Move);
}
