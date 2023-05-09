#include "EnemyStraea.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/core/actor/ex/ActorDepositoryStore.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/ggaf/dx/util/Input.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT,
    PHASE_ENTRY,
    PHASE_MOVE ,
    PHASE_TURN ,
    PHASE_FIRE ,
    PHASE_BANPEI,
};
enum {
    SE_EXPLOSION,
    SE_FIRE     ,
};

EnemyStraea::EnemyStraea(const char* prm_name) :
        VvEnemyActor<DefaultMeshActor>(prm_name, "Straea", StatusReset(EnemyErmione)) {
    //レーザー
    laser_way_ = 5;
    cnt_laserchip_ = 0;
    _x = 0;
    _y = 0;
    _z = 0;
    laser_length_ = 30;
    laser_interval_ = 300; //発射間隔

    angvelo_turn_ = 5000;
    ang_clearance_ = 10000;//開き具合
    papapLaserChipDepo_ = NEW LaserChipDepository**[laser_way_];
    for (int i = 0; i < laser_way_; i++) {
        papapLaserChipDepo_[i] = NEW LaserChipDepository*[laser_way_];
        for (int j = 0; j < laser_way_; j++) {
            papapLaserChipDepo_[i][j] = nullptr;
        }
    }

    pConn_pRefractionEffectDepository_ = connectToDepositoryManager("EffRefraction001");
    pConn_pDepoStore_laser_set = connectToDepositoryManager(
            "EnemyStraeaLaserChip004DepoStore"//,
         //"EnemyStraeaLaserChip003DepoStore",
         //"EnemyStraeaLaserChip001DepoStore",
         //"EnemyStraeaLaserChip002DepoStore",
         //pConn_pRefractionEffectDepository_->peek()
        );

    papaPosLaser_ = NEW PosLaser*[laser_way_];
    angle* paAng_way = NEW angle[laser_way_];
    UTIL::getWayAngle2D(0, laser_way_, ang_clearance_, paAng_way);
    angle Rz,Ry;
    double vx, vy, vz;
    for (int i = 0; i < laser_way_; i++) {
        Rz = UTIL::simplifyAng(paAng_way[i]);
        papaPosLaser_[i] = NEW PosLaser[laser_way_];
        for (int j = 0; j < laser_way_; j++) {
            Ry = UTIL::simplifyAng(paAng_way[j]);
            UTIL::convRzRyToVector(Rz, Ry, vx, vy, vz);
            papaPosLaser_[i][j].x = vx * PX_C(100);
            papaPosLaser_[i][j].y = vy * PX_C(100);
            papaPosLaser_[i][j].z = vz * PX_C(100);
        }
    }
    GGAF_DELETEARR(paAng_way);
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_EXPLOSION, "SE_EXPLOSION_MIDDLE_001");
    pSeXmtr->set(SE_FIRE     , "SE_ENEMY_FIRE_LASER_001");

    pConn_pShotDepo2_ = connectToDepositoryManager("Shot004Yellow");
    pConn_pShotDepo3_ = connectToDepositoryManager("Shot004Blue");
}

void EnemyStraea::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(1.0, 0.97);
    pModel->getTexBlinker()->setRange(0.5, 12.0);
    pModel->getTexBlinker()->beat(60*6, 60*2, 0, 60*2, -1);
}

void EnemyStraea::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(200));
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    pLocoVehicle->setRzRyMvAng(0, D180ANG);
}

void EnemyStraea::onActive() {
    getStatus()->reset();
    setHitAble(false);
    Spacetime* pSpacetime =  pCARETAKER->getSpacetime();
    _x = pSpacetime->_x_bound_right;
    getPhase()->reset(PHASE_INIT);
}

void EnemyStraea::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pLocoVehicle->setRollFaceAngVelo(4000);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pPhase->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
            static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
            if (pPhase->hasArrivedFrameAt(frame_of_summons_begin)) {
                getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            getAlphaFader()->behave();
            break;
        }
        case PHASE_MOVE: {
            if (pPhase->hasJustChanged()) {
                angle v = angvelo_turn_ / 50;
                pLocoVehicle->setRollPitchYawFaceAngVelo(RND(-v, v), RND(-v, v), RND(-v, v));
                pLocoVehicle->setMvVelo(2000);
            }
            if (getActiveFrame() % laser_interval_ == 0) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_TURN: {
            if (pPhase->hasJustChanged()) {
                //ターン開始
                pLocoVehicle->turnFaceAngTwd(pMYSHIP,
                                        angvelo_turn_, 0, TURN_ANTICLOSE_TO, false);
                cnt_laserchip_ = 0;
            }
            if (pLocoVehicle->isTurningFaceAng()) {
                //ターン中
            } else {
                //自機にがいた方向に振り向きが完了時
                pLocoVehicle->setRollPitchYawFaceAngVelo(angvelo_turn_*2, 0, 0);
                pLocoVehicle->setMvVelo(0);
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_FIRE: {
            if (pPhase->hasJustChanged()) {
                //レーザーセット、借入
                GgafCore::ActorDepositoryStore* pLaserChipDepoStore =
                        (GgafCore::ActorDepositoryStore*)(pConn_pDepoStore_laser_set->peek());
                bool can_fire = false;
                for (int i = 0; i < laser_way_; i++) {
                    for (int j = 0; j < laser_way_; j++) {
                        papapLaserChipDepo_[i][j] = (LaserChipDepository*)(pLaserChipDepoStore->dispatch());
                        if (papapLaserChipDepo_[i][j]) {
                            papapLaserChipDepo_[i][j]->config(laser_length_, 1);
                            can_fire = true;
                        }
                    }
                }
                if (can_fire) {
                    getSeXmtr()->play3D(SE_FIRE); //発射音
                    effectFlush(2); //フラッシュ
                }
            }
            if (cnt_laserchip_ < laser_length_) {
                cnt_laserchip_++;
                LaserChip* pLaserChip;
                PosLaser* p;
                D3DXMATRIX matWorldRot;
                UTIL::setWorldMatrix_RxRzRy(this, matWorldRot);
                angle Rz, Ry;
                int vX, vY, vZ;
                for (int i = 0; i < laser_way_; i++) {
                    for (int j = 0; j < laser_way_; j++) {
                        if (papapLaserChipDepo_[i][j]) {
                            pLaserChip = papapLaserChipDepo_[i][j]->dispatch();
                            if (pLaserChip) {
                                //レーザーの向きを計算
                                //ローカルでのショットの方向ベクトルを(x_org_,y_org_,z_org_)、
                                //ワールド変換行列の回転部分（matWorldRot)の成分を mat_xx、
                                //最終的な方向ベクトルを(vX, vY, vZ) とすると
                                //
                                //                          | mat_11 mat_12 mat_13 |
                                // | x_org_ y_org_ z_org_ | | mat_21 mat_22 mat_23 | = | vX vY vZ |
                                //                          | mat_31 mat_32 mat_33 |
                                //よって
                                // vX = x_org_*mat_11 + y_org_*mat_21 + z_org_*mat_31
                                // vY = x_org_*mat_12 + y_org_*mat_22 + z_org_*mat_32
                                // vZ = x_org_*mat_13 + y_org_*mat_23 + z_org_*mat_33
                                p = &(papaPosLaser_[i][j]);
                                vX = p->x*matWorldRot._11 + p->y*matWorldRot._21 + p->z*matWorldRot._31;
                                vY = p->x*matWorldRot._12 + p->y*matWorldRot._22 + p->z*matWorldRot._32;
                                vZ = p->x*matWorldRot._13 + p->y*matWorldRot._23 + p->z*matWorldRot._33;
                                UTIL::convVectorToRzRy(vX, vY, vZ, Rz, Ry); //現在の最終的な向きを、RzRyで取得
                                pLaserChip->setPosition(_x+vX, _y+vY, _z+vZ);
                                pLaserChip->getLocoVehicle()->setRzRyMvAng(Rz, Ry);
                                pLaserChip->_rz = Rz;
                                pLaserChip->_ry = Ry;
                            }
                        }
                    }
                }
            } else {
                pPhase->change(PHASE_MOVE);
            }
            break;
        }
    }
    getSeXmtr()->behave();
    pLocoVehicle->behave();
}

void EnemyStraea::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyStraea::onHit(const GgafCore::Actor* prm_pOtherActor) {
    static uint32_t spritedoller[24] = {
                                     6144      ,       //  000000000001100000000000
                                     14336     ,       //  000000000011100000000000
                                     13312     ,       //  000000000011010000000000
                                     25088     ,       //  000000000110001000000000
                                     49408     ,       //  000000001100000100000000
                                     98432     ,       //  000000011000000010000000
                                     196704    ,       //  000000110000000001100000
                                     393528    ,       //  000001100000000100111000
                                     917407    ,       //  000011011111111110011111
                                     3145734   ,       //  001100000000000000000110
                                     12582912  ,       //  110000000000000000000000
                                     1098776   ,       //  000100001100010000011000
                                     2091004   ,       //  000111111110011111111100
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     1623576   ,       //  000110001100011000011000
                                     2082552   ,       //  000111111100011011111000
                                     1623600   ,       //  000110001100011000110000
                                     1536      ,       //  000000000000011000000000
                                     1536              //  000000000000011000000000
    };


    static uint32_t red_dot[11] = {
            32  ,       //  00000100000
            112 ,       //  00001110000
            248 ,       //  00011111000
            428 ,       //  00110101100
            32  ,       //  00000100000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            0           //  00000000000
    };
    static uint32_t yellow_dot[11] = {
            0   ,       //  00000000000
            0   ,       //  00000000000
            0   ,       //  00000000000
            594 ,       //  01001010010
            990 ,       //  01111011110
            508 ,       //  00111111100
            168 ,       //  00010101000
            32  ,       //  00000100000
            32  ,       //  00000100000
            32  ,       //  00000100000
            32          //  00000100000
        };
    static uint32_t blue_dot[11] = {
            0   ,       //  00000000000
            1025,       //  10000000001
            1025,       //  10000000001
            1025,       //  10000000001
            1025,       //  10000000001
            1539,       //  11000000011
            774 ,       //  01100000110
            396 ,       //  00110001100
            136 ,       //  00010001000
            0   ,       //  00000000000
            0           //  00000000000
        };


    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeXmtr()->play3D(SE_EXPLOSION);
        sayonara();
        //固有打ち返し
        UTIL::shotWay003(this,
                         CommonScene_getDepository(Shot004) , red_dot,
                         pConn_pShotDepo2_->peek(), yellow_dot,
                         pConn_pShotDepo3_->peek(), blue_dot,
                         PX_C(20),
                         11, 11,
                         D_ANG(1), D_ANG(1),
                         5000, 100,
                         2, 1, 0.9);
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}


void EnemyStraea::onInactive() {
    //レーザーデポジトリは遅れてから戻す
    for (int i = 0; i < laser_way_; i++) {
        for (int j = 0; j < laser_way_; j++) {
            if (papapLaserChipDepo_[i][j]) {
                papapLaserChipDepo_[i][j]->sayonara(SEC_F(10));
            }
        }
    }
    sayonara();
}


EnemyStraea::~EnemyStraea() {
    pConn_pRefractionEffectDepository_->close();
    pConn_pDepoStore_laser_set->close();
    pConn_pShotDepo2_->close();
    pConn_pShotDepo3_->close();
    for (int i = 0; i < laser_way_; i++) {
        GGAF_DELETEARR(papaPosLaser_[i]);
        GGAF_DELETEARR(papapLaserChipDepo_[i]);
    }
    GGAF_DELETEARR(papaPosLaser_);
    GGAF_DELETEARR(papapLaserChipDepo_);
}
