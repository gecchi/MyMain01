#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyPallas::EnemyPallas(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Pallas", STATUS(EnemyPallas)) {
    _class_name = "EnemyPallas";
    iMovePatternNo_ = 0;
    pSplSeq_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(10);
}

void EnemyPallas::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyPallas::initialize() {
    setHitAble(true);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -7000);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyPallas::onActive() {
    if (pSplSeq_ == nullptr) {
        throwGgafCriticalException("EnemyPallasはスプライン必須ですconfigして下さい");
    }

    _pStatus->reset();
   iMovePatternNo_ = 0; //行動パターンリセット
    _pProg->change(1);
}

void EnemyPallas::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //【パターン1：スプライン移動】
    if (_pProg->hasJustChangedTo(1)) {
        pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
    }
    if (_pProg->get() == 1) {
        //スプライン移動終了待ち
        if (pSplSeq_->isExecuting()) {
            //待ちぼうけ
        } else {
            _pProg->changeNext(); //次のパターンへ
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //【パターン０：スプライン移動開始】
            if (pSplSeq_) {
                pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
            }
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：スプライン移動終了待ち】
            if (pSplSeq_) {
                //スプライン移動有り
                if (!(pSplSeq_->isExecuting())) {
                    iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
                }
            } else {
                //スプライン移動無し
                iMovePatternNo_++; //すぐに次の行動パターンへ
            }
            break;

        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
            if (pDepo_Shot_) {
                //放射状ショット
                int way = RR_EnemyPallas_ShotWay(_RANK_); //ショットWAY数
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDxDrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateWith(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAng_way);
                //ショット発射エフェクト
                if (pDepo_ShotEffect_) {
                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->locateWith(this);
                    }
                }
            }
//            //自機へ方向転換
            _pKurokoA->execTurnRzRyMvAngSequenceTwd(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                                                2000, 0,
                                                TURN_CLOSE_TO, true);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３】

            break;
        default:
            break;
    }

    if (pSplSeq_) {
        pSplSeq_->behave(); //スプライン移動を振る舞い
    }
    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyPallas::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyPallas::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    }
}

void EnemyPallas::onInactive() {
    sayonara();
}

EnemyPallas::~EnemyPallas() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}
