#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTamago01::EnemyTamago01(const char* prm_name) :
        SpriteMeshSetActor(prm_name, "8/tamago", STATUS(EnemyTamago01)) { //8/をいれとかないとユニークにならない

    _class_name = "EnemyTamago01";
    iMovePatternNo_ = 0;
    pProgram_Tamago01Move_ = NULL;
    pDepoCon_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;

    pDepoCon_ = connectToDepositoryManager("DpCon_Shot001", NULL);
    //pDepo_Shot_ = pDepoCon_->fetch();
pDepo_Shot_ = NULL;
    _pSeTxer->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));
}

void EnemyTamago01::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
}

void EnemyTamago01::initialize() {

    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->setMvAng(900000, 300000, 300000);
    _pKurokoA->setMvVelo(3000);
    _pColliChecker->makeCollision(1);
//    _pColliChecker->setColliAAPrism_Cube(0, 200000,POS_PRISM_ZX_pp);
//        _pColliChecker->setColliAAPrism_WHD(0,0,0,300000,100000,200000,100000,POS_PRISM_YZ_pn);

    //ヒットしない理由を探せ！！
//      _pColliChecker->setColliAAPrism_WHD(0,20000,-30000,50000,
//                                                90000,140000,60000,POS_PRISM_XY_nn);
//
//      _pColliChecker->setColliAAPrism_WHD(1,-20000,-30000,-50000,
//                                                 60000,90000,140000,POS_PRISM_ZX_pp);

//    _pColliChecker->setColliAAB_WHD(0,20000,-30000,50000,
//                                              90000,140000,60000);
    _pColliChecker->setColliAAB_Cube(0, 50000);


    //_pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _X = -50000;
    _Y = 200000;
    _Z = 100000;
    _pScaler->setScale(1000);
}

void EnemyTamago01::onActive() {
    _pStatus->reset();
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動をプログラムしておく
    }

//    _pUvFlipper->setRotation(16, 1/16.0, 1/16.0);
//    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5);
//    _pUvFlipper->forcePtnRange(0, 16*16-1);
//    _pUvFlipper->setActivePtn(0);
    iMovePatternNo_ = 0;
}

void EnemyTamago01::processBehavior() {

//    if (GgafDxInput::isBeingPressedKey(DIK_Q)) {
//        _pScaler->addScale(500);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_W)) {
//        _pScaler->addScale(-500);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_1)) {
//        _pModel->_pTextureBlinker->->addScale(2000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        _pModel->_pTextureBlinker->->addScale(-2000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _pModel->_pTextureBlinker->->intoTargetScaleAcceStep(3000, 0, 3);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _pModel->_pTextureBlinker->->loopLiner(20, -1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_5)) {
//        _pModel->_pTextureBlinker->->loopLiner(10, 5);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_6)) {
//        _pModel->_pTextureBlinker->->beat(20, 2 ,5, -1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        _pModel->_pTextureBlinker->->stopImmed();
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pModel->_pTextureBlinker->->setScaleToBottom();
//    }


    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (iMovePatternNo_ == 0) {
        //スプライン移動中
        if (pProgram_Tamago01Move_ && !(pProgram_Tamago01Move_->isExecuting())) {
            iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (iMovePatternNo_ == 1) {
        //スプライン移動終了時
        _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X+800000, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                   2000, 0,
                                                   TURN_CLOSE_TO);
        iMovePatternNo_++; //次の行動パターンへ
    }

    if (iMovePatternNo_ == 2) {
        iMovePatternNo_++;
    }

    if (iMovePatternNo_ == 3) {

    }
    if (getBehaveingFrame() % 30 == 0) {
        _pKurokoA->execTurnMvAngSequence(P_MYSHIP, 2000,0,TURN_CLOSE_TO);

        if (pDepo_Shot_) {
            //放射状ショット発射
            int way = 8;
            angle* paAng_way = NEW angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            UTIL::getRzRyAng(P_MYSHIP->_X - _X, P_MYSHIP->_Y - _Y, P_MYSHIP->_Z - _Z, target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            UTIL::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            UTIL::getWayAngle2D(target_RyRz_Ry, way, 10000, paAng_way);
            GgafDxDrawableActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                if (pActor) {
                    pActor->_pKurokoA->relateFaceAngWithMvAng(true);
                    pActor->_pKurokoA->setRzRyMvAng_by_RyRz(paAng_way[i], target_RyRz_Rz);
                    pActor->locateWith(this);
                }
            }
            DELETEARR_IMPOSSIBLE_NULL(paAng_way);
            //ショット発射エフェクト
            if (pDepo_ShotEffect_) {
                pActor = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                if (pActor) {
                    pActor->locateWith(this);
                }
            }
        }

    }
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->behave();
    }
    _pKurokoA->behave();
    _pScaler->behave();
    _pUvFlipper->behave();
    //_pSeTxer->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyTamago01::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = employFromCommon(EffectExplosion001);
    _pSeTxer->play3D(0);
    _TRACE_("HIT!!!");
    if (pExplo001) {
        pExplo001->locateWith(this);
    }

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        sayonara();
    }
}

void EnemyTamago01::onInactive() {
    //end();
}

EnemyTamago01::~EnemyTamago01() {
    pDepoCon_->close();
    DELETE_POSSIBLE_NULL(pProgram_Tamago01Move_);
}
