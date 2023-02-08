#include "EnemyOrtuna.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    MPH_OPEN = 1,
};
enum {
    SE_EXPLOSION ,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE01 ,
    PHASE_MOVE02 ,
    PHASE_MOVE03 ,
    PHASE_BANPEI,
};

EnemyOrtuna::EnemyOrtuna(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Ortuna", StatusReset(EnemyOrtuna)) {
    _class_name = "EnemyOrtuna";
    _sx=_sy=_sz=100;
    stagnating_pos_frames_ = 1;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
}

void EnemyOrtuna::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOrtuna::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyOrtuna::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyOrtuna::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
         case PHASE_INIT: {
             setHitAble(false);
             setPositionAt(&entry_pos_);
             setAlpha(0);
             pVecVehicle->setMvVelo(0);
             pVecVehicle->linkFaceAngByMvAng(true);
             pVecVehicle->setMvAngTwd(&stagnating_pos_);
             velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
             pVecVehicle->setRollFaceAngVelo(mv_velo); //���邮��`
             setMorphWeight(0.0);
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
             break;
         }
         case PHASE_MOVE01: {
             if (pPhase->hasJustChanged()) {
                 //�܂�Ԃ��|�C���g��GO!
                 //velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
                 velo mv_velo = PX_C(20);
                 coord d = UTIL::getDistance(this, &stagnating_pos_);
                 pVecVehicle->setMvVelo(mv_velo);//�����悭�|�[����
                 stagnating_pos_frames_ = pVecVehicle->setMvAcceByD(d, PX_C(1));
             }

             pVecVehicle->setRollFaceAngVelo(pVecVehicle->_velo_mv); //�����ɔ�Ⴕ�Ă��邮��`

             if (pPhase->getFrame() > stagnating_pos_frames_) {
                 pVecVehicle->setMvVelo(PX_C(1));
                 pVecVehicle->setMvAcce(0);
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE02: {
             if (pPhase->hasJustChanged()) {
                 //�����]��
                 //������莩�@�̕��֌�������
                 pVecVehicle->turnMvAngTwd(pMYSHIP, D_ANG(3), 0, TURN_CLOSE_TO, true);
                 getMorpher()->transitionLinearUntil(MPH_OPEN, 1.0, 60);
             }
             //�ؗ���
             if (pPhase->getFrame() % 16U == 0) {
                 if (pVecVehicle->isTurningMvAng()) {
                     //���傭���傭���@�����߂�
                     pVecVehicle->turnFaceAngTwd(pMYSHIP, D_ANG(1), 0, TURN_CLOSE_TO, true);
                 }
             }

             if (pPhase->hasArrivedFrameAt(60)) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num = RF_EnemyOrtuna_ShotWay(G_RANK); //�e���A�����N�ϓ�
                 velo shot_velo = RF_EnemyOrtuna_ShotMvVelo(G_RANK); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDx::FigureActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         GgafDx::VecVehicle* pShot_pVecVehicle = pShot->getVecVehicle();
                         pShot_pVecVehicle->setRzRyMvAng(_rz, _ry);
                         pShot_pVecVehicle->setMvVelo(shot_velo);
                         pShot_pVecVehicle->setMvAcce(100);
                     }
                 }
             }
             if (pPhase->hasArrivedFrameAt(60)) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE03: {
             //����Ȃ�`
             if (pPhase->hasJustChanged()) {
                 pVecVehicle->setMvVelo(PX_C(4));
                 pVecVehicle->setMvAcce(100);
             }
             break;
         }

         default: {
             break;
         }
     }

    pVecVehicle->behave();
    getMorpher()->behave();
    getAlphaFader()->behave();
    //getSeTransmitter()->behave();
}

void EnemyOrtuna::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOrtuna::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyOrtuna::onInactive() {
    sayonara();
}

EnemyOrtuna::~EnemyOrtuna() {
}
