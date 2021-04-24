#include "EnemyUnomia.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_ENTRY      ,
    PROG_CURVE_MOVE,
    PROG_MOVE01_1   ,
    PROG_MOVE01_2   ,
    PROG_LEAVE      ,
    PROG_BANPEI,
};
enum {
    SE_EXPLOSION ,
};

EnemyUnomia::EnemyUnomia(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Unomia", StatusReset(EnemyUnomia)) {
    _class_name = "EnemyUnomia";
    pDriverLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //����
}

void EnemyUnomia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyUnomia::initialize() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setRollFaceAngVelo(-4000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyUnomia::onReset() {
}

void EnemyUnomia::config(
        GgafDx::DriverLeader* prm_pDriverLeader,
        GgafCore::ActorDepository* prm_pDepo_shot,
        GgafCore::ActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
    pDriverLeader_ = prm_pDriverLeader;
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}


void EnemyUnomia::onActive() {
    if (pDriverLeader_ == nullptr) {
        throwCriticalException("EnemyUnomia�̓X�v���C���K�{�ł�config���ĉ�����");
    }
    getStatus()->reset();
    setHitAble(true);
    setRzFaceAng(0);
    getProgress()->reset(PROG_ENTRY);
}

void EnemyUnomia::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_ENTRY: {
            pDriverLeader_->start(ABSOLUTE_COORD);
            pProg->changeNext();
            break;
        }
        case PROG_CURVE_MOVE: {
            pDriverLeader_->behave(); //�X�v���C���ړ���U�镑��
            if (pDriverLeader_->isFinished()) {
                pProg->changeNext(); //����
            }
            break;
        }
        case PROG_MOVE01_1: {
            if (pProg->hasJustChanged()) {
                //���@�֕����]��
                pVecDriver->turnMvAngTwd(
                               pMYSHIP->_x, _y, pMYSHIP->_z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_shot_) {
//                //���ˏ�V���b�g
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //�V���b�gWAY��
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDx::FigureActor* pActor_shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_shot = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
//                    if (pActor_shot) {
//                        pActor_shot->setPositionAt(this);
//                        pActor_shot->getVecDriver()->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //�V���b�g���˃G�t�F�N�g
//                if (pDepo_effect_) {
//                    GgafDx::FigureActor* pTestActor_Shot = (GgafDx::FigureActor*)pDepo_effect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->setPositionAt(this);
//                    }
//                }
//            }
            break;
        }
        default: {
            break;
        }
    }

    pVecDriver->behave();
}

void EnemyUnomia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyUnomia::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyUnomia::onInactive() {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
}

EnemyUnomia::~EnemyUnomia() {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
}


