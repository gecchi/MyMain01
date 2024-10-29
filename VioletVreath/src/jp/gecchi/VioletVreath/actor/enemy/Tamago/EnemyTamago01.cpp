#include "EnemyTamago01.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyTamago01::EnemyTamago01(const char* prm_name) :
        VvEnemyActor<SpriteMeshSetActor>(prm_name, "tamago", StatusReset(EnemyTamago01)) { //8/をいれとかないとユニークにならない
    _class_name = "EnemyTamago01";
    iMovePatternNo_ = 0;
    pVehicleLeader_Tamago01Move_ = nullptr;
    pConn_depo_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;

    pConn_depo_ = connectToDepositoryManager("Shot001");
    //pDepo_shot_ = pConn_depo_->peek();
    pDepo_shot_ = nullptr;
}

void EnemyTamago01::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyTamago01::initialize() {
    setHitAble(true);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(1000);
    pLocusVehicle->setMvAngTwd(900000, 300000, 300000);
    pLocusVehicle->setMvVelo(3000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
//    pChecker->setColliAAPrism_Cube(0, 200000,POS_PRISM_ZX_PP);
//        pChecker->setColliAAPrism_WHD(0,0,0,300000,100000,200000,100000,POS_PRISM_YZ_PN);

    //ヒットしない理由を探せ！！
//      pChecker->setColliAAPrism_WHD(0,20000,-30000,50000,
//                                                90000,140000,60000,POS_PRISM_XY_NN);
//
//      pChecker->setColliAAPrism_WHD(1,-20000,-30000,-50000,
//                                                 60000,90000,140000,POS_PRISM_ZX_PP);

//    pChecker->setColliAABox_WHD(0,20000,-30000,50000,
//                                              90000,140000,60000);
    pChecker->setColliAACube(0, 50000);


    //pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _x = -50000;
    _y = 200000;
    _z = 100000;
    setScale(1000);
}

void EnemyTamago01::onActive() {
    getStatus()->reset();
    if (pVehicleLeader_Tamago01Move_) {
        pVehicleLeader_Tamago01Move_->start(ABSOLUTE_COORD); //カーブ移動をプログラムしておく
    }

//    getUvFlipper()->locatePatternNo(16, 1/16.0, 1/16.0);
//    getUvFlipper()->exec(FLIP_ORDER_LOOP, 5);
//    getUvFlipper()->setFlipPtnRange(0, 16*16-1);
//    getUvFlipper()->setActivePtn(0);
    iMovePatternNo_ = 0;
}

void EnemyTamago01::processBehavior() {

//    if (GgafDx::Input::isPressedKey(DIK_Q)) {
//        addScale(500);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_W)) {
//        addScale(-500);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_1)) {
//        pModel->getTexBlinker()->->addScale(2000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_2)) {
//        pModel->getTexBlinker()->->addScale(-2000);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_3)) {
//        pModel->getTexBlinker()->->transitionAcceUntil(3000, 0, 3);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_4)) {
//        pModel->getTexBlinker()->->transitionLinearLoop(20, -1);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_5)) {
//        pModel->getTexBlinker()->->transitionLinearLoop(10, 5);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_6)) {
//        pModel->getTexBlinker()->->beat(20, 2 ,5, -1);
//    }
//    if (GgafDx::Input::isPressedKey(DIK_7)) {
//        pModel->getTexBlinker()->->stopImmed();
//    }
//    if (GgafDx::Input::isPressedKey(DIK_0)) {
//        pModel->getTexBlinker()->->setScaleToBottom();
//    }
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();

    if (iMovePatternNo_ == 0) {
        //カーブ移動中
        if (pVehicleLeader_Tamago01Move_ && pVehicleLeader_Tamago01Move_->isFinished()) {
            iMovePatternNo_++; //カーブ移動が終了したら次の行動パターンへ
        }
    }

    if (iMovePatternNo_ == 1) {
        //カーブ移動終了時
        pLocusVehicle->turnMvAngTwd(pMYSHIP->_x+800000, pMYSHIP->_y, pMYSHIP->_z,
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
        pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                2000,0,TURN_CLOSE_TO, false);

        if (pDepo_shot_) {
            //放射状ショット発射
            int way = 8;
            angle* paAng_way = NEW angle[way];
            angle target_RzRy_Rz, target_RzRy_Ry;
            UTIL::convVectorToRzRy(pMYSHIP->_x - _x, pMYSHIP->_y - _y, pMYSHIP->_z - _z,
                                   target_RzRy_Rz, target_RzRy_Ry);
            angle target_RyRz_Ry, target_RyRz_Rz;
            UTIL::convRzRyToRyRz(target_RzRy_Rz, target_RzRy_Ry, target_RyRz_Ry, target_RyRz_Rz);
            UTIL::getWayAngleArr(target_RyRz_Ry, way, 10000, paAng_way);
            GgafDx::FigureActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
                if (pActor) {
                    pActor->getLocusVehicle()->linkFaceAngByMvAng(true);
                    pActor->getLocusVehicle()->setRzRyMvAngByRyRz(paAng_way[i], target_RyRz_Rz);
                    pActor->setPositionAt(this);
                }
            }
            GGAF_DELETEARR(paAng_way);
            //ショット発射エフェクト
            if (pDepo_effect_) {
                pActor = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
                if (pActor) {
                    pActor->setPositionAt(this);
                }
            }
        }

    }
    if (pVehicleLeader_Tamago01Move_) {
        pVehicleLeader_Tamago01Move_->behave();
    }
    pLocusVehicle->behave();
    getScaler()->behave();
    getUvFlipper()->behave();
    //getSeXmtr()->behave();
}

void EnemyTamago01::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyTamago01::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyTamago01::onInactive() {
}

EnemyTamago01::~EnemyTamago01() {
    pConn_depo_->close();
    GGAF_DELETE_NULLABLE(pVehicleLeader_Tamago01Move_);
}
