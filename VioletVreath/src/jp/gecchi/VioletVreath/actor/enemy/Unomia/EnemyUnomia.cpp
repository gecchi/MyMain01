#include "EnemyUnomia.h"

#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyUnomia::EnemyUnomia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Unomia", STATUS(EnemyUnomia)) {
    _class_name = "EnemyUnomia";
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_BANPEI);
}

void EnemyUnomia::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyUnomia::initialize() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->relateFaceByMvAng(true);
    pKuroko->setFaceAngVelo(AXIS_X, -4000);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyUnomia::onReset() {
}

void EnemyUnomia::config(
        GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
        GgafCore::GgafActorDepository* prm_pDepo_shot,
        GgafCore::GgafActorDepository* prm_pDepo_shotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_shot_ = prm_pDepo_shot;
    pDepo_effect_ = prm_pDepo_shotEffect;
}


void EnemyUnomia::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyUnomiaはスプライン必須ですconfigして下さい");
    }
    getStatus()->reset();
    setHitAble(true);
    setRzFaceAng(0);
    getProgress()->reset(PROG_ENTRY);
}

void EnemyUnomia::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_ENTRY: {
            pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD);
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
            if (pProg->isJustChanged()) {
                //自機へ方向転換
                pKuroko->turnMvAngTwd(
                               P_MYSHIP->_x, _y, P_MYSHIP->_z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_shot_) {
//                //放射状ショット
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxFigureActor* pActor_shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_shot = (GgafDxFigureActor*)pDepo_shot_->dispatch();
//                    if (pActor_shot) {
//                        pActor_shot->positionAs(this);
//                        pActor_shot->getKuroko()->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_effect_) {
//                    GgafDxFigureActor* pTestActor_Shot = (GgafDxFigureActor*)pDepo_effect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->positionAs(this);
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
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyUnomia::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
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


