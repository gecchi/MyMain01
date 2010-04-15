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
    prepareSe(0, "bomb1", GgafRepeatSeq::nextVal("CANNEL_bomb1"));
    _pDispatcherCon = (DispatcherConnection*)God::_dispatcherManager.connect("DpCon_Shot001");
    _pDispatcher_Shot = _pDispatcherCon->view();
}

void EnemyTamago01::onCreateModel() {
    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void EnemyTamago01::initialize() {

    setHitAble(false);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 1000);
    _pMover->setMvAng(900000, 300000, 300000);
    _pMover->setMvVelo(0);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 90000);


    //_pCollisionChecker->setColliBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
//    _X = 300000;
//    _Y = 300000;
//    _Z = 300000;
    _pScaler->setScale(5000);
}

void EnemyTamago01::onActive() {
    MyStgUtil::resetEnemyTamago01Status(_pStatus);
    if (_pProgram_Tamago01Move) {
        _pMover->executeSplineMoveProgram(_pProgram_Tamago01Move, 0); //スプライン移動をプログラムしておく
    }

    _pUvFlipper->setTextureUvRotation(16, 1/16.0, 1/16.0);
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
    _pUvFlipper->forcePtnNoRange(0, 16*16-1);
    _pUvFlipper->setPtnNo(0);
    _iMovePatternNo = 0;
}

void EnemyTamago01::processBehavior() {

    if (GgafDx9Input::isBeingPressedKey(DIK_Q)) {
        _pScaler->addScale(500);
    }
    if (GgafDx9Input::isBeingPressedKey(DIK_W)) {
        _pScaler->addScale(-500);
    }
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
        _pMover->execTagettingMvAngSequence(pMYSHIP->_X+800000, pMYSHIP->_Y, pMYSHIP->_Z,
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
        _pMover->execTagettingMvAngSequence(pMYSHIP, 2000,0,TURN_CLOSE_TO);

        if (_pDispatcher_Shot) {
            //放射状ショット発射
            int way = 8;
            angle* paAngWay = new angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            GgafDx9Util::getRzRyAng(pMYSHIP->_X - _X, pMYSHIP->_Y - _Y, pMYSHIP->_Z - _Z, target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            GgafDx9Util::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            GgafDx9Util::getWayAngle2D(target_RyRz_Ry, way, 10000, paAngWay);
            GgafDx9DrawableActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng_by_RyRz(paAngWay[i], target_RyRz_Rz);
                    pActor->setGeometry(this);
                    pActor->activate();
                }
            }
            DELETEARR_IMPOSSIBLE_NULL(paAngWay);
            //ショット発射エフェクト
            if (_pDispatcher_ShotEffect) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->setGeometry(_X, _Y, _Z);
                }
            }
        }

    }

    _pMover->behave();
    _pScaler->behave();
    _pUvFlipper->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyTamago01::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe3D(0);
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {


        //inactivate();
    }
}

void EnemyTamago01::onInactive() {
    //sayonara();
}

EnemyTamago01::~EnemyTamago01() {
    _pDispatcherCon->close();
    DELETE_POSSIBLE_NULL(_pProgram_Tamago01Move);
}
