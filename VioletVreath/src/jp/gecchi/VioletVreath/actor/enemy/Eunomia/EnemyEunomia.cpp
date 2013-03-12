#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEunomia::EnemyEunomia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Eunomia", STATUS(EnemyEunomia)) {
    _class_name = "EnemyEunomia";
    iMovePatternNo_ = 0;
    pSplSeq_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(10);
}

void EnemyEunomia::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEunomia::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, -4000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEunomia::onReset() {

}

void EnemyEunomia::config(
        GgafLib::SplineSequence* prm_pSplSeq,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    DELETE_POSSIBLE_NULL(pSplSeq_);
    pSplSeq_ = prm_pSplSeq;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}


void EnemyEunomia::onActive() {
    if (pSplSeq_ == nullptr) {
        throwGgafCriticalException("EnemyEunomiaはスプライン必須ですconfigして下さい");
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    iMovePatternNo_ = 0; //行動パターンリセット
    _pProg->set(PROG_ENTRY);
}

void EnemyEunomia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_ENTRY: {
            pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
            _pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVE: {
            if (pSplSeq_->isExecuting()) {
                //スプライン移動終了の待ちぼうけ
            } else {
                _pProg->changeNext(); //次へ
            }
            break;
        }
        case PROG_MOVE01_1: {
            if (_pProg->isJustChanged()) {
                //自機へ方向転換
                _pKurokoA->execTurnRzRyMvAngSequenceTwd(
                               P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                               2000, 0,
                               TURN_CLOSE_TO, true
                           );
            }

//            if (pDepo_Shot_) {
//                //放射状ショット
//                int way = RR_EnemyEunomia_ShotWay(_RANK_); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->locateWith(this);
//                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                DELETEARR_IMPOSSIBLE_NULL(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->locateWith(this);
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
//        pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
//    }
//    if (_pProg->get() == 1) {
//        //スプライン移動終了待ち
//        if (pSplSeq_->isExecuting()) {
//            //待ちぼうけ
//        } else {
//            _pProg->changeNext(); //次のパターンへ
//        }
//    }
//
//    switch (iMovePatternNo_) {
//        case 0:  //【パターン０：スプライン移動開始】
//            if (pSplSeq_) {
//                pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
//            }
//            iMovePatternNo_++; //次の行動パターンへ
//            break;
//
//        case 1:  //【パターン１：スプライン移動終了待ち】
//            if (pSplSeq_) {
//                //スプライン移動有り
//                if (!(pSplSeq_->isExecuting())) {
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
//                int way = RR_EnemyEunomia_ShotWay(_RANK_); //ショットWAY数
//                angle* paAng_way = NEW angle[way];
//                UTIL::getRadialAngle2D(0, way, paAng_way);
//                GgafDxDrawableActor* pActor_Shot;
//                for (int i = 0; i < way; i++) {
//                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
//                    if (pActor_Shot) {
//                        pActor_Shot->locateWith(this);
//                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
//                    }
//                }
//                DELETEARR_IMPOSSIBLE_NULL(paAng_way);
//                //ショット発射エフェクト
//                if (pDepo_ShotEffect_) {
//                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
//                    if (pTestActor_Shot) {
//                        pTestActor_Shot->locateWith(this);
//                    }
//                }
//            }
////            //自機へ方向転換
//            _pKurokoA->execTurnRzRyMvAngSequenceTwd(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
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

    pSplSeq_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();
}

void EnemyEunomia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEunomia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //破壊された場合
        setHitAble(false); //以降同一フレーム内でヒットさせない。
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
        _pSeTx->play3D(SE_EXPLOSION);          //爆発音再生
        if (pOther->getKind() & KIND_MY) { //自機側に撃たれて消滅の場合は
            UTIL::activateItemOf(this); //アイテム出現
        }
        sayonara();
    } else {
        //一発で死ぬのでココは通らないハズ。
    }
}

void EnemyEunomia::onInactive() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}

EnemyEunomia::~EnemyEunomia() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}


