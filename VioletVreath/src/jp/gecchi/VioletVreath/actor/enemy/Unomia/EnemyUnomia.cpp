#include "stdafx.h"
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
    iMovePatternNo_ = 0;
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
    GgafDxKuroko* pKuroko = getKuroko();
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
    iMovePatternNo_ = 0; //行動パターンリセット
    getProgress()->reset(PROG_ENTRY);
}

void EnemyUnomia::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_ENTRY: {
            pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD);
            pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVE: {
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
//                GgafDxDrawableActor* pActor_shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_shot = (GgafDxDrawableActor*)pDepo_shot_->dispatch();
//                    if (pActor_shot) {
//                        pActor_shot->positionAs(this);
//                        pActor_shot->getKuroko()->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_effect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_effect_->dispatch();
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

//
//
//
//
//    //【パターン1：スプライン移動】
//    if (pProg->isJustChangedTo(1)) {
//        pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
//    }
//    if (pProg->get() == 1) {
//        //スプライン移動終了待ち
//        if (pKurokoLeader_->isLeading()) {
//            //待ちぼうけ
//        } else {
//            pProg->changeNext(); //次のパターンへ
//        }
//    }
//
//    switch (iMovePatternNo_) {
//        case 0:  //【パターン０：スプライン移動開始】
//            if (pKurokoLeader_) {
//                pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
//            }
//            iMovePatternNo_++; //次の行動パターンへ
//            break;
//
//        case 1:  //【パターン１：スプライン移動終了待ち】
//            if (pKurokoLeader_) {
//                //スプライン移動有り
//                if (!(pKurokoLeader_->isLeading())) {
//                    iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
//                }
//            } else {
//                //スプライン移動無し
//                iMovePatternNo_++; //すぐに次の行動パターンへ
//            }
//            break;
//
//        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
//            if (pDepo_shot_) {
//                //放射状ショット
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_shot = (GgafDxDrawableActor*)pDepo_shot_->dispatch();
//                    if (pActor_shot) {
//                        pActor_shot->positionAs(this);
//                        pActor_shot->getKuroko()->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_effect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_effect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->positionAs(this);
//                    }
//                }
//            }
////            //自機へ方向転換
//            pKuroko->turnMvAngTwd(P_MYSHIP->_x, _y, P_MYSHIP->_z,
//                                                2000, 0,
//                                                TURN_CLOSE_TO);
//            iMovePatternNo_++; //次の行動パターンへ
//            break;
//
//        case 3:  //【行動パターン３】
//
//            break;
//        default:
//            break;
//    }

    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    pKuroko->behave();
}

void EnemyUnomia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyUnomia::onHit(GgafActor* prm_pOtherActor) {
    if (strcmp(_name, "Unomia[0]") == 0) {
        _TRACE_("EnemyUnomia::onHit()");
    }

    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyUnomia::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

EnemyUnomia::~EnemyUnomia() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}


