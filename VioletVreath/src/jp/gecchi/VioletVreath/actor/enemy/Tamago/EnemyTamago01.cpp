#include "stdafx.h"
#include "EnemyTamago01.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTamago01::EnemyTamago01(const char* prm_name) :
        SpriteMeshSetActor(prm_name, "8/tamago", STATUS(EnemyTamago01)) { //8/をいれとかないとユニークにならない
    _class_name = "EnemyTamago01";
    pScaler_ = NEW GgafDxScaler(this);
    iMovePatternNo_ = 0;
    pProgram_Tamago01Move_ = nullptr;
    pDepoConnection_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

    pDepoConnection_ = connect_DepositoryManager("Shot001");
    //pDepo_Shot_ = pDepoConnection_->peek();
pDepo_Shot_ = nullptr;
    _pSeTx->set(0, "WAVE_EXPLOSION_001");
}

void EnemyTamago01::onCreateModel() {
    _pModel->setBlinkPower(0.1, 0.9);
    _pModel->_pTexBlinker->forceRange(0.1, 1.0);
    _pModel->_pTexBlinker->beat(120, 60, 0, 60, -1);
}

void EnemyTamago01::initialize() {

    setHitAble(true);
    _pKuroko->relateFaceWithMvAng(true);
    _pKuroko->setFaceAngVelo(AXIS_X, 1000);
    _pKuroko->setMvAngTwd(900000, 300000, 300000);
    _pKuroko->setMvVelo(3000);
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
    _x = -50000;
    _y = 200000;
    _z = 100000;
    setScale(1000);
}

void EnemyTamago01::onActive() {
    _pStatus->reset();
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動をプログラムしておく
    }

//    _pUvFlipper->setRotation(16, 1/16.0, 1/16.0);
//    _pUvFlipper->exec(FLIP_ORDER_LOOP, 5);
//    _pUvFlipper->setFlipPtnRange(0, 16*16-1);
//    _pUvFlipper->setActivePtn(0);
    iMovePatternNo_ = 0;
}

void EnemyTamago01::processBehavior() {

//    if (GgafDxInput::isBeingPressedKey(DIK_Q)) {
//        addScale(500);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_W)) {
//        addScale(-500);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_1)) {
//        _pModel->_pTexBlinker->->addScale(2000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        _pModel->_pTexBlinker->->addScale(-2000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        _pModel->_pTexBlinker->->transitionAcceStep(3000, 0, 3);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        _pModel->_pTexBlinker->->loopLiner(20, -1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_5)) {
//        _pModel->_pTexBlinker->->loopLiner(10, 5);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_6)) {
//        _pModel->_pTexBlinker->->beat(20, 2 ,5, -1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        _pModel->_pTexBlinker->->stopImmed();
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        _pModel->_pTexBlinker->->setScaleToBottom();
//    }


    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (iMovePatternNo_ == 0) {
        //スプライン移動中
        if (pProgram_Tamago01Move_ && pProgram_Tamago01Move_->isFinished()) {
            iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (iMovePatternNo_ == 1) {
        //スプライン移動終了時
        _pKuroko->turnMvAngTwd(P_MYSHIP->_x+800000, P_MYSHIP->_y, P_MYSHIP->_z,
                                            2000, 0,
                                            TURN_CLOSE_TO, false);
        iMovePatternNo_++; //次の行動パターンへ
    }

    if (iMovePatternNo_ == 2) {
        iMovePatternNo_++;
    }

    if (iMovePatternNo_ == 3) {

    }
    if (getBehaveingFrame() % 30U == 0) {
        _pKuroko->turnMvAngTwd(P_MYSHIP,
                                2000,0,TURN_CLOSE_TO, false);

        if (pDepo_Shot_) {
            //放射状ショット発射
            int way = 8;
            angle* paAng_way = NEW angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            UTIL::convVectorToRzRy(P_MYSHIP->_x - _x, P_MYSHIP->_y - _y, P_MYSHIP->_z - _z,
                                   target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            UTIL::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            UTIL::getWayAngle2D(target_RyRz_Ry, way, 10000, paAng_way);
            GgafDxDrawableActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                if (pActor) {
                    pActor->_pKuroko->relateFaceWithMvAng(true);
                    pActor->_pKuroko->setRzRyMvAng_by_RyRz(paAng_way[i], target_RyRz_Rz);
                    pActor->positionAs(this);
                }
            }
            GGAF_DELETEARR(paAng_way);
            //ショット発射エフェクト
            if (pDepo_ShotEffect_) {
                pActor = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                if (pActor) {
                    pActor->positionAs(this);
                }
            }
        }

    }
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->behave();
    }
    _pKuroko->behave();
    pScaler_->behave();
    _pUvFlipper->behave();
    //_pSeTx->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyTamago01::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = dispatchFromCommon(EffectExplosion001);
    _pSeTx->play3D(0);
    _TRACE_("HIT!!!");
    if (pExplo001) {
        pExplo001->positionAs(this);
    }

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        sayonara();
    }
}

void EnemyTamago01::onInactive() {
}

EnemyTamago01::~EnemyTamago01() {
    GGAF_DELETE(pScaler_);
    pDepoConnection_->close();
    GGAF_DELETE_NULLABLE(pProgram_Tamago01Move_);
}
