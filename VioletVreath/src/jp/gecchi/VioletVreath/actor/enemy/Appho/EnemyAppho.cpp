#include "EnemyAppho.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicleMvAssistant.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE01 ,
    PHASE_MOVE02 ,
    PHASE_MOVE03 ,
    PHASE_MOVE04 ,
    PHASE_BANPEI ,
};

EnemyAppho::EnemyAppho(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Appho", StatusReset(EnemyAppho)) {
    _class_name = "EnemyAppho";
}

void EnemyAppho::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAppho::initialize() {
    setScale(100);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAppho::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyAppho::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {

         case PHASE_INIT: {
             setHitAble(false);
             setPositionAt(&entry_pos_);
             setFaceAngTwd(stagnating_pos_.x, stagnating_pos_.y, stagnating_pos_.z);
             setAlpha(0);
             pLocusVehicle->linkFaceAngByMvAng(false);
             pLocusVehicle->setMvVelo(0);
             pLocusVehicle->setMvAngTwd(&stagnating_pos_);
             pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
             pPhase->changeNext();
             break;
         }
         case PHASE_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pPhase->hasJustChanged()) {
                 pEffectEntry = (EffectBlink*)UTIL::activateCommonEffectOf(this, STAT_EntryEffectKind);
                 pLocusVehicle->setRollFaceAngVelo(D_ANG(3));
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
                 //�ؗ��|�C���g��GO!
                 velo mv_velo = RF_EnemyAppho_MvVelo(G_RANK);
                 coord d = UTIL::getDistance(this, &stagnating_pos_);
                 pLocusVehicle->asstMv()->slideByVd(mv_velo, d,
                                               0.2, 0.8, 200, true);
             }
             //�ؗ��|�C���g�܂ňړ���
             if (pPhase->getFrame() % 32U == 0) {
                 //���傭���傭���@�����߂�
                 pLocusVehicle->turnFaceAngTwd(pMYSHIP, D_ANG(0.5), 0,
                                         TURN_CLOSE_TO, true);
             }
             if (pLocusVehicle->asstMv()->hasJustFinishedSliding()) {
                 pPhase->changeNext();
             }
             //_TRACE_("PHASE_MOVE01:"<<_x<<","<<_y<<","<<_z<<","<<_pLocusVehicle->_velo_mv<<","<<_pLocusVehicle->_acc_mv);
             break;
         }

         case PHASE_MOVE02: {
             if (pPhase->hasJustChanged()) {
                 //�ؗ��|�C���g�����A���@�����փW�����ړ�������
                 pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                       100, 0, TURN_CLOSE_TO, false);
                 //������莩�@�̕��֌�������
                 pLocusVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             //�ؗ���
             //���@�����߂�
             pLocusVehicle->turnFaceAngTwd(pMYSHIP,
                                     D_ANG(1), 0, TURN_CLOSE_TO, true);

             if (pPhase->hasArrivedFrameAt(180)) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num   = RF_EnemyAppho_ShotWay(G_RANK);    //�e���A�����N�ϓ�
                 velo shot_velo = RF_EnemyAppho_ShotMvVelo(G_RANK); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDx::FigureActor* pShot = UTIL::activateCommonAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         GgafDx::LocusVehicle* pShot_pLocusVehicle = pShot->getLocusVehicle();
                         pShot_pLocusVehicle->setRzRyMvAng(_rz, _ry);
                         pShot_pLocusVehicle->setMvVelo(shot_velo);
                         pShot_pLocusVehicle->setMvAcce(100);
                     }
                 }
             }
             if (pPhase->hasArrivedFrameAt(240)) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE03: {
             //����Ȃ珀��
             if (pPhase->hasJustChanged()) {
                 //������肳��Ȃ�|�C���g�֌�����
                 pLocusVehicle->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), D_ANG(1), TURN_CLOSE_TO, false);
                 pLocusVehicle->setMvAcce(10);
             }
             if (pPhase->getFrame() % 16U == 0) {
                 pLocusVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             if (!pLocusVehicle->isTurningMvAng()) {
                 pPhase->changeNext();
             }
             break;
         }

         case PHASE_MOVE04: {
             //����Ȃ�`
             if (pPhase->hasJustChanged()) {
                 pLocusVehicle->turnMvAngTwd(&leave_pos_,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
                 pLocusVehicle->setMvAcce(100+(G_RANK*200));
             }
             if (pPhase->getFrame() % 16U == 0) {
                 //���傭���傭���@�����߂�
                 pLocusVehicle->turnFaceAngTwd(pMYSHIP,
                                         D_ANG(1), 0, TURN_CLOSE_TO, true);
             }
             break;
         }

         default: {
             break;
         }
     }
    pLocusVehicle->behave();
    getAlphaFader()->behave();
}

void EnemyAppho::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyAppho::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyAppho::onInactive() {
    sayonara();
}

EnemyAppho::~EnemyAppho() {
}
