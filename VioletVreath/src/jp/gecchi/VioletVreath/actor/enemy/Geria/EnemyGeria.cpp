#include "EnemyGeria.h"

#include "jp/ggaf/dx/actor/supporter/AlphaFader.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/GeoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT  ,
    PHASE_ENTRY ,
    PHASE_MOVE  ,
    PHASE_FIRE  ,
    PHASE_LEAVE ,
    PHASE_BANPEI,
};
enum {
    SE_EXPLOSION,
    SE_FIRE     ,
};

EnemyGeria::EnemyGeria(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Geria", StatusReset(EnemyGeria)) {
    _class_name = "EnemyGeria";
    iMovePatternNo_ = 0;
    max_shots_ = 1;
    shot_num_ = 0;
    can_Shot_ = false;
    will_shot_ = false;
    velo_mv_begin_ = 0;
    frame_when_shot_ = 0;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001");     //����
    pSeTx->set(SE_FIRE     , "SE_ENEMY_FIRE_SHOT_001");     //����
    migration_length_ = PX_C(10000);
    mvd_ = 0;
}

void EnemyGeria::onCreateModel() {
}

void EnemyGeria::initialize() {
    setHitAble(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 45000);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->setFaceAngVelo(AXIS_Z, -7000);
}

void EnemyGeria::onActive() {
    getStatus()->reset();
    setHitAble(true);
    will_shot_ = false;
    can_Shot_ = true;
    shot_num_ = 0;
    frame_when_shot_ = 0;
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    velo_mv_begin_ = pVecVehicle->getMvVelo(); //�����ړ����x��ۑ�
    pVecVehicle->setMvVelo(0);
    setRzFaceAng(0);
    setRxFaceAng(0);
    mvd_ = 0;
    getPhase()->reset(PHASE_INIT);
}

void EnemyGeria::processBehavior() {
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafDx::GeoVehicle* const pGeoVehicle = getGeoVehicle();
    GgafDx::AlphaFader* pAlphaFader = getAlphaFader();
    GgafCore::Phase* pPhase = getPhase();

    switch (pPhase->get()) {
        case PHASE_INIT: {
            max_shots_ = 1; //�ړ����Ɍ������ł���V���b�g�̍ő��
            shot_num_ = 0;  //�������V���b�g��
            setHitAble(false);
            setAlpha(0);
            pPhase->changeNext();
            break;
        }
        case PHASE_ENTRY: {  //�o��
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
        case PHASE_MOVE: {  //�ړ�
            if (pPhase->hasJustChanged()) {
                pVecVehicle->setMvVelo(velo_mv_begin_);
                will_shot_ = false;
            }
            if (will_shot_) {
                if (pPhase->hasArrivedFrameAt(frame_when_shot_)) {
                    pPhase->change(PHASE_FIRE);
                }
            } else {
                if (max_shots_ > shot_num_) {
                    MyShip* pM = pMYSHIP;
                    if (pM->_z - 500000 < _z && _z < pM->_z + 500000 &&
                        pM->_y - 500000 < _y && _y < pM->_y + 500000 )
                    {
                        frame_when_shot_ = pPhase->getFrame() + RND(1, 20); //�V���b�g�������߂܂ł̃��O��݂��ĎU��΂点��
                        will_shot_ = true;
                    }
                }
            }
            break;
        }
        case PHASE_FIRE: {  //����
            if (pPhase->hasJustChanged()) {
                pVecVehicle->setMvVelo(PX_C(3)); //����
                pVecVehicle->rollFaceAngTo(D180ANG, D_ANG(3), 0, TURN_CLOCKWISE); //�\������̂�����Ɖ�]
            }

            if (!pVecVehicle->isTurningFaceAng()) {
                MyShip* pM = pMYSHIP;
                GgafDx::GeometricActor* pLast =
                      UTIL::shotWay001(_x, _y, _z,
                                       pM->_x, pM->_y, pM->_z,
                                       getCommonDepository(Shot004),
                                       PX_C(10),
                                       10000, 100,
                                       3, 5, 0.9,
                                       EnemyGeria::callbackDispatched);
                if (pLast) {
                    shot_num_++;
                    will_shot_ = false;
                    effectFlush(3); //�t���b�V��
                    getSeTransmitter()->play3D(SE_FIRE);
                }
                pPhase->change(PHASE_MOVE);
            }
            break;
        }
        case PHASE_LEAVE: {
            if (pPhase->hasJustChanged()) {
                setHitAble(false);
                pVecVehicle->setMvVelo(0);
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
    pGeoVehicle->behave();
    pVecVehicle->behave();
    pAlphaFader->behave();
    mvd_ += pVecVehicle->getMvVelo();
    if (mvd_ > migration_length_) {
        getPhase()->change(PHASE_LEAVE);
    }
}

void EnemyGeria::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyGeria::onInactive() {
    setHitAble(false);
}

void EnemyGeria::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

EnemyGeria::~EnemyGeria() {
}

void EnemyGeria::callbackDispatched(GgafDx::FigureActor* prm_pDispatched, int prm_dispatched_seq, int prm_set_seq) {
}

