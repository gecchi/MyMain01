#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyEunomia::EnemyEunomia(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Eunomia", STATUS(EnemyEunomia)) {
    _class_name = "EnemyEunomia";
    _iMovePatternNo = 0;
    _pSplSeq = NULL;
    _pDepo_Shot = NULL;
    _pDepo_ShotEffect = NULL;
    _pFormation = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    useProgress(10);
}

void EnemyEunomia::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEunomia::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, -4000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEunomia::onReset() {
    _pStatus->reset();
    setHitAble(true);
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _iMovePatternNo = 0; //行動パターンリセット
    _pProg->change(1);
}


void EnemyEunomia::onActive() {
    if (_pSplSeq == NULL) {
        throwGgafCriticalException("EnemyEunomiaはスプライン必須ですconfigして下さい");
    }
    reset();
}

void EnemyEunomia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //【パターン1：スプライン移動】
    if (_pProg->isJustChangedTo(1)) {
        _pSplSeq->exec(ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
    }
    if (_pProg->get() == 1) {
        //スプライン移動終了待ち
        if (_pSplSeq->isExecuting()) {
            //待ちぼうけ
        } else {
            _pProg->changeNext(); //次のパターンへ
        }
    }

    switch (_iMovePatternNo) {
        case 0:  //【パターン０：スプライン移動開始】
            if (_pSplSeq) {
                _pSplSeq->exec(ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
            }
            _iMovePatternNo++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：スプライン移動終了待ち】
            if (_pSplSeq) {
                //スプライン移動有り
                if (!(_pSplSeq->isExecuting())) {
                    _iMovePatternNo++; //スプライン移動が終了したら次の行動パターンへ
                }
            } else {
                //スプライン移動無し
                _iMovePatternNo++; //すぐに次の行動パターンへ
            }
            break;

        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
            if (_pDepo_Shot) {
                //放射状ショット
                int way = R_EnemyEunomia_ShotWay; //ショットWAY数
                angle* paAngWay = NEW angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDepo_Shot->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateAs(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAngWay[i], ANGLE90);
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //ショット発射エフェクト
                if (_pDepo_ShotEffect) {
                    GgafDx9DrawableActor* pTestActor_Shot = (GgafDx9DrawableActor*)_pDepo_ShotEffect->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->locateAs(this);
                    }
                }
            }
//            //自機へ方向転換
            _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                                                2000, 0,
                                                TURN_CLOSE_TO);
            _iMovePatternNo++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３】

            break;
        default:
            break;
    }


    if (_pSplSeq) {
        _pSplSeq->behave(); //スプライン移動を振る舞い
    }
    _pKurokoA->behave();
    //_pSeTransmitter->behave();
}

void EnemyEunomia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEunomia::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyEunomia::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyEunomia::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;

    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }

        //自機側に撃たれて消滅の場合、
        if (_pFormation && (pOther->getKind() & KIND_MY)) {
            //フォーメーションに自身が撃たれた事を伝える。
            _pFormation->wasDestroyedFollower(this);
            //アイテム出現
            Item* pItem = (Item*)P_COMMON_SCENE->_pDP_MagicPointItem001->dispatch();
            if (pItem) {
                pItem->locateAs(this);
            }
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();
    }
}

void EnemyEunomia::onInactive() {
    if (_pFormation) {
        //_TRACE_("EnemyEunomia::onInactive() _pFormation="<<_pFormation->getName());
        _pFormation->wasInactiveFollower();
    }
    DELETE_POSSIBLE_NULL(_pSplSeq);
//    sayonara();
}

EnemyEunomia::~EnemyEunomia() {
    DELETE_POSSIBLE_NULL(_pSplSeq);
}


