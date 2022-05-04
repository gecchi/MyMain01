#include "EnemyOebius.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
#include "FormationOebius.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};
enum {
    PHASE_INIT   ,
    PHASE_ENTRY  ,
    PHASE_MOVE_BEGIN ,
    PHASE_CURVE ,
    PHASE_SCATTER ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};

EnemyOebius::EnemyOebius(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Oebius", StatusReset(EnemyOebius)) {
    _class_name = "EnemyOebius";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");
    pVehicleLeader_ = nullptr; //�t�H�[���[�V�����I�u�W�F�N�g���ݒ肷��
    scatter_flg_ = false;
    delay_ = 0;
}

void EnemyOebius::onCreateModel() {
//    pModel->setSpecular(5.0, 1.0);
}

void EnemyOebius::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->linkFaceAngByMvAng(true);
    pVecVehicle->forceMvVeloRange(PX_C(15));
}

void EnemyOebius::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyOebius::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            setHitAble(false);
            setAlpha(0);
            pVecVehicle->setRollFaceAngVelo(D_ANG(3));
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
                pAlphaFader->transitionLinearUntil(1.0, frame_of_entering);
            }
            if (pPhase->hasArrivedFrameAt(frame_of_entering)) {
                setHitAble(true);
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_MOVE_BEGIN: {
            if (pPhase->hasJustChanged()) {

            }
            if (pPhase->hasArrivedFrameAt(120)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_CURVE: {
            if (pPhase->hasJustChanged()) {
                getVecVehicle()->setMvAcce(0); //�����x������ꍇ�͐؂��Ă���
                pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, -1); //-1�͖������[�v
            }

            FormationOebius* pFormation = (FormationOebius*)getFormation();
            pVehicleLeader_->setStartPosition(pFormation->geo_.x, pFormation->geo_.y, pFormation->geo_.z);
            pVehicleLeader_->setStartAngle(pFormation->geo_.rx, pFormation->geo_.ry, pFormation->geo_.rz);
            pVehicleLeader_->behave(); //�J�[�u�ړ�����悤��Driver�𑀍�

            if (scatter_flg_) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_SCATTER: {
            if (pPhase->hasJustChanged()) {
                delay_ = RND(0, 120);
            }
            if (pPhase->hasArrivedFrameAt(delay_)) {
                //�U��U��ɂȂ�
                pVehicleLeader_->stop();
                pVecVehicle->turnRzRyMvAngTo(RND_ABOUT(pVecVehicle->_rz_mv, D_ANG(90)), RND_ABOUT(pVecVehicle->_ry_mv, D_ANG(90)),
                                         D_ANG(2), 0, TURN_CLOSE_TO,false);
                pVecVehicle->setMvAcce(100);
            }

            if (pPhase->hasArrivedFrameAt(delay_ + 200)) {
                pPhase->changeNext();
            }
            break;
        }

        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAlphaFader->transitionLinearUntil(0.0, 30);
            }
            if (pPhase->hasArrivedFrameAt(60)) {
                sayonara();
                pPhase->changeNothing(); //�����܂��I
            }
            break;
        }
        default :
            break;
    }

    pAlphaFader->behave();
    pVecVehicle->behave();
}

void EnemyOebius::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOebius::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyOebius::onInactive() {
    if (getBehaveingFrame() > 10) {
        //EnemyOebiusCore�ɊǗ�����Ă���B���߂�Inactive()�ł��邽�߁B
        sayonara();
    }
}
void EnemyOebius::scatter() {
    //Formation����w��������B
    scatter_flg_ = true;
}

EnemyOebius::~EnemyOebius() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
