#include "EnemyUnomia.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_ENTRY      ,
    PROG_SPLINE_MOVE,
    PROG_MOVE01_1   ,
    PROG_MOVE01_2   ,
    PROG_LEAVE      ,
    PROG_BANPEI,
};
enum {
    SE_EXPLOSION ,
};

EnemyUnomia::EnemyUnomia(const char* prm_name) :
        DefaultMassMeshActor(prm_name, "Unomia") {
    _class_name = "EnemyUnomia";
    getStatus()->reset(statusResetFunction(EnemyUnomia));
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_BANPEI);
}

void EnemyUnomia::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyUnomia::initialize() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(-4000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyUnomia::onReset() {
}

void EnemyUnomia::config(
        GgafLib::SplineLeader* prm_pKurokoLeader,
        GgafCore::ActorDepository* prm_pDepo_shot,
        GgafCore::ActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}


void EnemyUnomia::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwCriticalException("EnemyUnomiaはスプライン必須ですconfigして下さい");
    }
    getStatus()->reset();
    setHitAble(true);
    setRzFaceAng(0);
    getProgress()->reset(PROG_ENTRY);
}

void EnemyUnomia::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_ENTRY: {
            pKurokoLeader_->start(ABSOLUTE_COORD);
            pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVE: {
            pKurokoLeader_->behave(); //スプライン移動を振る舞い
            if (pKurokoLeader_->isFinished()) {
                pProg->changeNext(); //次へ
            }
            break;
        }
        case PROG_MOVE01_1: {
            if (pProg->hasJustChanged()) {
                //自機へ方向転換
                pKuroko->turnMvAngTwd(
                               pMYSHIP->_x, _y, pMYSHIP->_z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_shot_) {
//                //放射状ショット
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDx::FigureActor* pActor_shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_shot = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
//                    if (pActor_shot) {
//                        pActor_shot->setPositionAt(this);
//                        pActor_shot->getKuroko()->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
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

    pKuroko->behave();
}

void EnemyUnomia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyUnomia::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyUnomia::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyUnomia::~EnemyUnomia() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


