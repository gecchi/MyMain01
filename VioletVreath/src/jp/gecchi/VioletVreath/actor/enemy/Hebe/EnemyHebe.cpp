#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHebe::EnemyHebe(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Hebe", STATUS(EnemyHebe)) {
    _class_name = "EnemyHebe";
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;
    _pSeTx->useSe(1);
    _pSeTx->set(SE_EXPLOSION, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    useProgress(10);
}

void EnemyHebe::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyHebe::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, -4000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}


void EnemyHebe::config(
//        GgafLib::TreeFormation* prm_pFormation,
        GgafLib::SplineSequence* prm_pSplSeq,
        GgafCore::GgafActorDepository* prm_pDepo_Shot,
        GgafCore::GgafActorDepository* prm_pDepo_ShotEffect
        ) {
    DELETE_POSSIBLE_NULL(pSplSeq_);
    pSplSeq_ = prm_pSplSeq;
    pDepo_Shot_ = prm_pDepo_Shot;
    pDepo_ShotEffect_ = prm_pDepo_ShotEffect;
}


void EnemyHebe::onActive() {
    if (pSplSeq_ == NULL) {
        throwGgafCriticalException("EnemyHebeはスプライン必須ですconfigして下さい");
    }
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pProg->set(PROG_MOVE01_1);
}

void EnemyHebe::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    switch (_pProg->get()) {
        case PROG_MOVE01_1: {
            if (_pProg->getFrameInProgress() > (PX_C(300) / ABS(_pKurokoA->_veloMv))) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_SPLINE_MOVE: {
            if (_pProg->isJustChanged()) {
                pSplSeq_->exec(SplineSequence::RELATIVE_COORD);
            }
            if (!pSplSeq_->isExecuting()) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE02_1: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->execTurnMvAngSequence(_X - PX_C(300), _Y, _Z,
                                                 D_ANG(1), 0, TURN_CLOSE_TO, false);
            }

            break;
        }
    }



//
//
//    }
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
//                int way = 3;//R_EnemyHebe_ShotWay; //ショットWAY数
//                //R_FormationHebe_ShotWay
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
//            _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
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

    if (pSplSeq_) {
        pSplSeq_->behave(); //スプライン移動を振る舞い
    }
    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyHebe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHebe::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        setHitAble(false);
        //爆発エフェクト
        GgafDxDrawableActor* pExplo = UTIL::activateExplosionEffect(_pStatus);
        if (pExplo) {
            pExplo->locateWith(this);
            pExplo->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //フォーメーションに自身が撃たれた事を伝える。
            notifyFormationAboutDestroyed();
            //アイテム出現
            Item* pItem = UTIL::activateItem(_pStatus);
            if (pItem) {
                pItem->locateWith(this);
            }
        }
        sayonara();
    }
}

void EnemyHebe::onInactive() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}

EnemyHebe::~EnemyHebe() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}


