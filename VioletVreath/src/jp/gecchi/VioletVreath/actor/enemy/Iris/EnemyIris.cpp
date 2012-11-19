#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyIris::EnemyIris(const char* prm_name)
      : DefaultMeshSetActor(prm_name, "Iris", STATUS(EnemyIris)) {
    _class_name = "EnemyIris";
    iMovePatternNo_ = 0;
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;
    _pSeTxer->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
}

void EnemyIris::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.5, 2.0);
    _pModel->_pTextureBlinker->setBlink(0.5);
    _pModel->_pTextureBlinker->beat(60, 3, 1, -1);
}

void EnemyIris::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyIris::onActive() {
    _pStatus->reset();
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyIris::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (iMovePatternNo_) {
        case 0:  //【パターン０：スプライン移動開始】
            if (pSplSeq_) {
                pSplSeq_->exec(SplineSequence::ABSOLUTE_COORD); //スプライン移動を開始
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
                int way = RR_EnemyIris_ShotWay(_RANK_); //ショットWAY数
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDxDrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateWith(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
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
            //自機へ方向転換
            _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                3000, 0,
                                                TURN_CLOSE_TO);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３：自機へグルッと逆回転で方向転換開始】
            if (_Z-10000 < P_MYSHIP->_Z && P_MYSHIP->_Z < _Z+10000) {
                //自機とZ軸が接近したらグルッと逆回転で方向転換
                _pKurokoA->execTurnMvAngSequence(MyShip::lim_behaind_ - 500000 , _Y, _Z,
                                                   10000, 0,
                                                   TURN_CLOSE_TO);
                _pKurokoA->setMvAcce(100);
                iMovePatternNo_++;
            } else {
                //自機とZ軸が接近するまで待つ
            }
            break;
        default:
            break;
    }


    if (pSplSeq_) {
        pSplSeq_->behave(); //スプライン移動を振る舞い
    }
    _pKurokoA->behave();
    //_pSeTxer->behave();
}

void EnemyIris::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyIris::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTxer->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    }
}

void EnemyIris::onInactive() {
    sayonara();
}

EnemyIris::~EnemyIris() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}
