#include "EnemyAllas.h"

#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION ,
};

EnemyAllas::EnemyAllas(const char* prm_name) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Allas", StatusReset(EnemyAllas)) {
    _class_name = "EnemyAllas";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(10);
}

void EnemyAllas::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyAllas::initialize() {
    setHitAble(true);
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Z, -7000);
    pKuroko->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyAllas::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwCriticalException("EnemyAllasはスプライン必須ですconfigして下さい");
    }

    getStatus()->reset();
   iMovePatternNo_ = 0; //行動パターンリセット
   getProgress()->change(1);
}

void EnemyAllas::processBehavior() {
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafCore::Progress* const pProg = getProgress();
    //【パターン1：スプライン移動】
    if (pProg->hasJustChangedTo(1)) {
        pKurokoLeader_->start(ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
    }
    if (pProg->get() == 1) {
        //スプライン移動終了待ち
        if (pKurokoLeader_->isFinished()) {
            pProg->changeNext(); //次のパターンへ
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //【パターン０：スプライン移動開始】
            if (pKurokoLeader_) {
                pKurokoLeader_->start(ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
            }
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：スプライン移動終了待ち】
            if (pKurokoLeader_) {
                //スプライン移動有り
                if (pKurokoLeader_->isFinished()) {
                    iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
                }
            } else {
                //スプライン移動無し
                iMovePatternNo_++; //すぐに次の行動パターンへ
            }
            break;

        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
            if (pDepo_shot_) {
                //放射状ショット
                int way = RF_EnemyAllas_ShotWay(G_RANK); //ショットWAY数
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDx::FigureActor* pActor_shot;
                for (int i = 0; i < way; i++) {
                    pActor_shot = (GgafDx::FigureActor*)pDepo_shot_->dispatch();
                    if (pActor_shot) {
                        pActor_shot->setPositionAt(this);
                        pActor_shot->getKuroko()->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_shot->activate();
                    }
                }
                GGAF_DELETEARR(paAng_way);
                //ショット発射エフェクト
                if (pDepo_effect_) {
                    GgafDx::FigureActor* pTestActor_Shot = (GgafDx::FigureActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->setPositionAt(this);
                    }
                }
            }
//            //自機へ方向転換
            pKuroko->turnMvAngTwd(pMYSHIP->_x, _y, pMYSHIP->_z,
                                    2000, 0,
                                    TURN_CLOSE_TO, true);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:   //【行動パターン３】

            break;
        default:
            break;
    }

    if (pKurokoLeader_) {
        pKurokoLeader_->behave(); //スプライン移動を振る舞い
    }
    pKuroko->behave();
    //getSeTransmitter()->behave();
}

void EnemyAllas::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyAllas::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyAllas::onInactive() {
    sayonara();
}

EnemyAllas::~EnemyAllas() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
