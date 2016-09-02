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
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
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
    pConn_depo_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;

    pConn_depo_ = connectToDepositoryManager("Shot001");
    //pDepo_shot_ = pConn_depo_->peek();
    pDepo_shot_ = nullptr;
    GgafDxSeTransmitterForActor* pSe = getSeTransmitter();
    pSe->set(0, "WAVE_EXPLOSION_001");
}

void EnemyTamago01::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyTamago01::initialize() {
    setHitAble(true);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(1000);
    pKuroko->setMvAngTwd(900000, 300000, 300000);
    pKuroko->setMvVelo(3000);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
//    pChecker->setColliAAPrism_Cube(0, 200000,POS_PRISM_ZX_pp);
//        pChecker->setColliAAPrism_WHD(0,0,0,300000,100000,200000,100000,POS_PRISM_YZ_pn);

    //ヒットしない理由を探せ！！
//      pChecker->setColliAAPrism_WHD(0,20000,-30000,50000,
//                                                90000,140000,60000,POS_PRISM_XY_nn);
//
//      pChecker->setColliAAPrism_WHD(1,-20000,-30000,-50000,
//                                                 60000,90000,140000,POS_PRISM_ZX_pp);

//    pChecker->setColliAABox_WHD(0,20000,-30000,50000,
//                                              90000,140000,60000);
    pChecker->setColliAABox_Cube(0, 50000);


    //pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _x = -50000;
    _y = 200000;
    _z = 100000;
    setScale(1000);
}

void EnemyTamago01::onActive() {
    getStatus()->reset();
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->start(ABSOLUTE_COORD); //スプライン移動をプログラムしておく
    }

//    getUvFlipper()->setRotation(16, 1/16.0, 1/16.0);
//    getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
//    getUvFlipper()->setFlipPtnRange(0, 16*16-1);
//    getUvFlipper()->setActivePtn(0);
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
//        pModel->getTexBlinker()->->addScale(2000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_2)) {
//        pModel->getTexBlinker()->->addScale(-2000);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_3)) {
//        pModel->getTexBlinker()->->transitionAcceUntil(3000, 0, 3);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_4)) {
//        pModel->getTexBlinker()->->transitionLinerLoop(20, -1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_5)) {
//        pModel->getTexBlinker()->->transitionLinerLoop(10, 5);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_6)) {
//        pModel->getTexBlinker()->->beat(20, 2 ,5, -1);
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_7)) {
//        pModel->getTexBlinker()->->stopImmed();
//    }
//    if (GgafDxInput::isBeingPressedKey(DIK_0)) {
//        pModel->getTexBlinker()->->setScaleToBottom();
//    }
    GgafDxKuroko* const pKuroko = getKuroko();

    if (iMovePatternNo_ == 0) {
        //スプライン移動中
        if (pProgram_Tamago01Move_ && pProgram_Tamago01Move_->isFinished()) {
            iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (iMovePatternNo_ == 1) {
        //スプライン移動終了時
        pKuroko->turnMvAngTwd(P_MYSHIP->_x+800000, P_MYSHIP->_y, P_MYSHIP->_z,
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
        pKuroko->turnMvAngTwd(P_MYSHIP,
                                2000,0,TURN_CLOSE_TO, false);

        if (pDepo_shot_) {
            //放射状ショット発射
            int way = 8;
            angle* paAng_way = NEW angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            UTIL::convVectorToRzRy(P_MYSHIP->_x - _x, P_MYSHIP->_y - _y, P_MYSHIP->_z - _z,
                                   target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            UTIL::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            UTIL::getWayAngle2D(target_RyRz_Ry, way, 10000, paAng_way);
            GgafDxFigureActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDxFigureActor*)pDepo_shot_->dispatch();
                if (pActor) {
                    pActor->getKuroko()->linkFaceAngByMvAng(true);
                    pActor->getKuroko()->setRzRyMvAng_by_RyRz(paAng_way[i], target_RyRz_Rz);
                    pActor->placeAs(this);
                }
            }
            GGAF_DELETEARR(paAng_way);
            //ショット発射エフェクト
            if (pDepo_effect_) {
                pActor = (GgafDxFigureActor*)pDepo_shot_->dispatch();
                if (pActor) {
                    pActor->placeAs(this);
                }
            }
        }

    }
    if (pProgram_Tamago01Move_) {
        pProgram_Tamago01Move_->behave();
    }
    pKuroko->behave();
    pScaler_->behave();
    getUvFlipper()->behave();
    //getSeTransmitter()->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyTamago01::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(0);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyTamago01::onInactive() {
}

EnemyTamago01::~EnemyTamago01() {
    GGAF_DELETE(pScaler_);
    pConn_depo_->close();
    GGAF_DELETE_NULLABLE(pProgram_Tamago01Move_);
}
