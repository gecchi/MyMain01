#include "EnemyIda.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT ,
    PROG_ENTRY,
    PROG_MOVE01,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
};

EnemyIda::EnemyIda(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ida", StatusReset(EnemyIda)) {
    _class_name = "EnemyIda";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");     //����
}

void EnemyIda::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyIda::initialize() {
    getVecDriver()->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyIda::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyIda::processBehavior() {
    changeGeoLocal(); //���[�J�����W�n��

    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            pVecDriver->setRollFaceAngVelo(D_ANG(4));
            setAlpha(0);
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
            }
            //���@�֌�����
            GgafDx::GeometricActor* pTargetActor = pMYSHIP;
            coord mvx = pTargetActor->_x - _x_final; //_x_final�͐�΍��W
            coord mvy = pTargetActor->_y - _y_final;
            coord mvz = pTargetActor->_z - _z_final;
            //�x�[�X�܂ł�(��]�~���s�ړ�)�s��̋t�s��擾
            D3DXMATRIX* pBaseInvMat = _pActor_base->getInvMatWorldRotMv();
            //���[�J�����W�Ō����Ă����ׂ������x�N�g���v�Z
            coord tvx = mvx*pBaseInvMat->_11 + mvy*pBaseInvMat->_21 + mvz*pBaseInvMat->_31;
            coord tvy = mvx*pBaseInvMat->_12 + mvy*pBaseInvMat->_22 + mvz*pBaseInvMat->_32;
            coord tvz = mvx*pBaseInvMat->_13 + mvy*pBaseInvMat->_23 + mvz*pBaseInvMat->_33;

            angle rz_target, ry_target;
            UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target); //RzRy�ɒu��������
            pVecDriver->setRzRyMvAng(rz_target, ry_target);
            break;
        }
    }

    getAlphaFader()->behave();
    pVecDriver->behave();

    changeGeoFinal(); //��΍��W�n��
}

void EnemyIda::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyIda::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyIda::onInactive() {
}

EnemyIda::~EnemyIda() {
}


