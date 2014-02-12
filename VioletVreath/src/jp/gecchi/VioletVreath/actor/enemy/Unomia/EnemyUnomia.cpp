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
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_BANPEI);
}

void EnemyUnomia::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyUnomia::initialize() {
    _pKuroko->relateFaceWithMvAng(true);
    _pKuroko->setFaceAngVelo(AXIS_X, -4000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyUnomia::onReset() {
}

void EnemyUnomia::config(
        GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}


void EnemyUnomia::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyUnomiaはスプライン必須ですconfigして下さい");
    }
    _pStatus->reset();
    setHitAble(true);
    setRzFaceAng(0);
    iMovePatternNo_ = 0; //行動パターンリセット
    _pProg->reset(PROG_ENTRY);
}

void EnemyUnomia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD);
            _pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVE: {
            if (pKurokoLeader_->isFinished()) {
                _pProg->changeNext(); //次へ
            }
            break;
        }
        case PROG_MOVE01_1: {
            if (_pProg->isJustChanged()) {
                //自機へ方向転換
                _pKuroko->turnMvAngTwd(
                               P_MYSHIP->_x, _y, P_MYSHIP->_z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_Shot_) {
//                //放射状ショット
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->positionAs(this);
//                        pActor_Shot->_pKuroko->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->positionAs(this);
//                    }
//                }
//            }
            break;
        }
        default:
            break;
    }

//
//
//
//
//    //【パターン1：スプライン移動】
//    if (_pProg->isJustChangedTo(1)) {
//        pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
//    }
//    if (_pProg->get() == 1) {
//        //スプライン移動終了待ち
//        if (pKurokoLeader_->isLeading()) {
//            //待ちぼうけ
//        } else {
//            _pProg->changeNext(); //次のパターンへ
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
//            if (pDepo_Shot_) {
//                //放射状ショット
//                int way = RF_EnemyUnomia_ShotWay(G_RANK); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->positionAs(this);
//                        pActor_Shot->_pKuroko->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                GGAF_DELETEARR(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->positionAs(this);
//                    }
//                }
//            }
////            //自機へ方向転換
//            _pKuroko->turnMvAngTwd(P_MYSHIP->_x, _y, P_MYSHIP->_z,
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
    _pKuroko->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
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


