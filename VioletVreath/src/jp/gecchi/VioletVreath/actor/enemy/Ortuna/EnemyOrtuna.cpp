#include "EnemyOrtuna.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
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
    PROG_INIT   ,
    PROG_ENTRY  ,
    PROG_MOVE01 ,
    PROG_MOVE02 ,
    PROG_MOVE03 ,
    PROG_BANPEI,
};

EnemyOrtuna::EnemyOrtuna(const char* prm_name) :
        VvEnemyActor<DefaultMorphMeshActor>(prm_name, "Ortuna_1", StatusReset(EnemyOrtuna)) {
    _class_name = "EnemyOrtuna";
    _sx=_sy=_sz=100;
    stagnating_pos_frames_ = 1;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyOrtuna::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOrtuna::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyOrtuna::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyOrtuna::processBehavior() {
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             setPositionAt(&entry_pos_);
             setAlpha(0);
             pRikisha->setMvVelo(0);
             pRikisha->linkFaceAngByMvAng(true);
             pRikisha->setMvAngTwd(&stagnating_pos_);
             velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
             pRikisha->setRollFaceAngVelo(mv_velo); //���邮��`
             setMorphWeight(0.0);
             pProg->changeNext();
             break;
         }
         case PROG_ENTRY: {
             EffectBlink* pEffectEntry = nullptr;
             if (pProg->hasJustChanged()) {
                 pEffectEntry = UTIL::activateEntryEffectOf(this);
             }
             static const frame frame_of_summons_begin = pEffectEntry->getFrameOfSummonsBegin();
             static const frame frame_of_entering = pEffectEntry->getSummoningFrames() + frame_of_summons_begin;
             if (pProg->hasArrivedAt(frame_of_summons_begin)) {
                 getAlphaFader()->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pProg->hasArrivedAt(frame_of_entering)) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }
         case PROG_MOVE01: {
             if (pProg->hasJustChanged()) {
                 //�܂�Ԃ��|�C���g��GO!
                 //velo mv_velo = RF_EnemyOrtuna_MvVelo(G_RANK);
                 velo mv_velo = PX_C(20);
                 coord d = UTIL::getDistance(this, &stagnating_pos_);
                 pRikisha->setMvVelo(mv_velo);//�����悭�|�[����
                 stagnating_pos_frames_ = pRikisha->setMvAcceByD(d, PX_C(1));
             }

             pRikisha->setRollFaceAngVelo(pRikisha->_velo_mv); //�����ɔ�Ⴕ�Ă��邮��`

             if (pProg->getFrame() > stagnating_pos_frames_) {
                 pRikisha->setMvVelo(PX_C(1));
                 pRikisha->setMvAcce(0);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE02: {
             if (pProg->hasJustChanged()) {
                 //�����]��
                 //������莩�@�̕��֌�������
                 pRikisha->turnMvAngTwd(pMYSHIP,
                                        D_ANG(3), 0, TURN_CLOSE_TO, true);
                 getMorpher()->transitionLinearUntil(MPH_OPEN, 1.0, 60);
             }
             //�ؗ���
             if (pProg->getFrame() % 16U == 0) {
                 if (pRikisha->isTurningMvAng()) {
                     //���傭���傭���@�����߂�
                     pRikisha->turnFaceAngTwd(pMYSHIP,
                                              D_ANG(1), 0, TURN_CLOSE_TO, true);
                 }
             }

             if (pProg->hasArrivedAt(60)) {
                 //���@�̕��Ɍ�������G�e���ˁI
                 int shot_num = RF_EnemyOrtuna_ShotWay(G_RANK); //�e���A�����N�ϓ�
                 velo shot_velo = RF_EnemyOrtuna_ShotMvVelo(G_RANK); //�e���A�����N�ϓ�
                 for (int i = 0; i < shot_num; i++) {
                     GgafDx::FigureActor* pShot = UTIL::activateAttackShotOf(this);
                     if (pShot) {
                         pShot->activateDelay(1+(i*10)); //�΂�����Bactivate �^�C�~���O�㏑���I
                         GgafDx::Rikisha* pShot_pRikisha = pShot->callRikisha();
                         pShot_pRikisha->setRzRyMvAng(_rz, _ry);
                         pShot_pRikisha->setMvVelo(shot_velo);
                         pShot_pRikisha->setMvAcce(100);
                     }
                 }
             }
             if (pProg->hasArrivedAt(60)) {
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE03: {
             //����Ȃ�`
             if (pProg->hasJustChanged()) {
                 pRikisha->setMvVelo(PX_C(4));
                 pRikisha->setMvAcce(100);
             }
             break;
         }

         default: {
             break;
         }
     }

    pRikisha->behave();
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
