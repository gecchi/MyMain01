#include "EnemyAntiope.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Kago.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};
enum {
    PROG_INIT  ,
    PROG_ENTRY ,
    PROG_MOVE01,
    PROG_LEAVE ,
    PROG_RUSH,
    PROG_BANPEI,
};


EnemyAntiope::EnemyAntiope(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "EnemyAntiope";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pP_ = nullptr;
}

void EnemyAntiope::onCreateModel() {
//    GgafDx::Model* pModel = getModel();
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyAntiope::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAntiope::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyAntiope::processBehavior() {
    GgafDx::Rikisha* const pRikisha = callRikisha();
    GgafDx::Kago* const pKago = callKago();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();

    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
         case PROG_INIT: {
             setHitAble(false);
             setAlpha(0);
             pRikisha->stopMv();
             pRikisha->setRollFaceAngVelo(D_ANG(10));
             pKago->setZeroVxyzMvVelo();
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
                 pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
             }
             if (pProg->hasArrivedAt(frame_of_entering)) {
                 setHitAble(true);
                 pProg->changeNext();
             }
             break;
         }

         case PROG_MOVE01: { //�������̂悤�ȓ���
             if (pProg->hasJustChanged()) {
                 pRikisha->setMvVelo(PX_C(30));
                 pRikisha->setMvAcce(-1000);
                 //���s�ړ����x�̕����x�N�g�� mv_velo_twd_ �̓t�H�[���[�V�������ݒ�
                 pKago->setVxyzMvVelo(mv_velo_twd_.x, mv_velo_twd_.y, mv_velo_twd_.z);
             }

             if (pRikisha->_velo_mv <= (-PX_C(30) + 1000)) {
                 if (pP_) {
                     pRikisha->stopMv();
                     pKago->setZeroVxyzMvVelo();
                     pProg->change(PROG_LEAVE);
                 } else {
                     pKago->setVxyzMvVelo(
                                  mv_velo_twd_.x + (pRikisha->_vX * pRikisha->_velo_mv),
                                  mv_velo_twd_.y + (pRikisha->_vY * pRikisha->_velo_mv),
                                  mv_velo_twd_.z + (pRikisha->_vZ * pRikisha->_velo_mv)
                                );
                     pRikisha->stopMv();
                     pProg->change(PROG_RUSH);
                 }
             }
             break;
         }

         case PROG_LEAVE: {
             if (pProg->hasJustChanged()) {
                 UTIL::activateLeaveEffectOf(this);
                 pAlphaFader->transitionLinearUntil(0.0, 15);
             }
             if (pProg->hasArrivedAt(15)) {
                 setHitAble(false);
                 sayonara();
             }
             break;
         }

         case PROG_RUSH: {
             //���������Ȃ��Ȃ����ꍇ
             if (pProg->hasJustChanged()) {
                 pKago->execGravitationMvSequenceTwd(pMYSHIP, PX_C(30), 200, PX_C(50));
                 pRikisha->keepOnTurningFaceAngTwd(pMYSHIP, D_ANG(2), 0, TURN_CLOSE_TO, false);
             }
             break;
         }

         default: {
             break;
         }
     }

//    _TRACE_(this<<":"<<getActiveFrame()<<" "<<_x<<","<<_y<<","<<_z<<"  ("<<_pRikisha->_velo_mv<<") "<<_pRikisha->_vX<<","<<_pRikisha->_vY<<","<<_pRikisha->_vZ<<"");
    pRikisha->behave();
    pKago->behave();
    pAlphaFader->behave();
}

void EnemyAntiope::processJudgement() {
    if (isOutOfSpacetime()) {
        pP_ = nullptr;
        sayonara();
    }
}

void EnemyAntiope::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        if (pP_) {
            if (pP_->pP_) {
                pP_->pP_ = nullptr;
            }
        }
        pP_ = nullptr;
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyAntiope::onInactive() {
    pP_ = nullptr;
    sayonara();
}

EnemyAntiope::~EnemyAntiope() {
}
