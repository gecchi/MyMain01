#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyEunomia::EnemyEunomia(const char* prm_name) : DefaultMeshSetActor(prm_name, "Eunomia") {
    _class_name = "EnemyEunomia";
    MyStgUtil::resetEnemyEunomiaStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSplineProgram = NULL;
    _pStore_Shot = NULL;
    _pStore_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    useProgress(10);
}

void EnemyEunomia::onCreateModel() {
    _pGgafDx9Model->setSpecular(5.0, 1.0);
}

void EnemyEunomia::initialize() {
    setHitAble(true);
    _pMvNavigator->setFaceAngVelo(AXIS_X, -4000);
    _pMvNavigator->relateFaceAngWithMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEunomia::onReset() {
    MyStgUtil::resetEnemyEunomiaStatus(_pStatus);
    _iMovePatternNo = 0; //行動パターンリセット
    _pPrg->change(1);
}


void EnemyEunomia::onActive() {
    if (_pSplineProgram == NULL) {
        throwGgafCriticalException("EnemyEunomiaはスプライン必須ですconfigして下さい");
    }
    reset();
}

void EnemyEunomia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //【パターン1：スプライン移動】
    if (_pPrg->isJustChangedTo(1)) {
        _pSplineProgram->begin(0); //スプライン移動を開始(1:座標相対)
    }
    if (_pPrg->get() == 1) {
        //スプライン移動終了待ち
        if (_pSplineProgram->isExecuting()) {
            //待ちぼうけ
        } else {
            _pPrg->changeNext(); //次のパターンへ
        }
    }

    switch (_iMovePatternNo) {
        case 0:  //【パターン０：スプライン移動開始】
            if (_pSplineProgram) {
                _pSplineProgram->begin(0); //スプライン移動を開始(1:座標相対)
            }
            _iMovePatternNo++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：スプライン移動終了待ち】
            if (_pSplineProgram) {
                //スプライン移動有り
                if (!(_pSplineProgram->isExecuting())) {
                    _iMovePatternNo++; //スプライン移動が終了したら次の行動パターンへ
                }
            } else {
                //スプライン移動無し
                _iMovePatternNo++; //すぐに次の行動パターンへ
            }
            break;

        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
            if (_pStore_Shot) {
                //放射状ショット
                int way = 10+_RANK_*10; //ショットWAY数
                angle* paAngWay = NEW angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pStore_Shot->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->locateAs(this);
                        pActor_Shot->_pMvNavigator->setRzRyMvAng(paAngWay[i], ANGLE90);
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //ショット発射エフェクト
                if (_pStore_ShotEffect) {
                    GgafDx9DrawableActor* pTestActor_Shot = (GgafDx9DrawableActor*)_pStore_ShotEffect->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->locateAs(this);
                    }
                }
            }
//            //自機へ方向転換
            _pMvNavigator->execTurnMvAngSequence(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
                                                2000, 0,
                                                TURN_CLOSE_TO);
            _iMovePatternNo++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３】

            break;
        default:
            break;
    }


    if (_pSplineProgram) {
        _pSplineProgram->behave(); //スプライン移動を振る舞い
    }
    _pMvNavigator->behave();
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
            pExplo001->_pMvNavigator->takeoverMvFrom(_pMvNavigator);
        }

        //自機側に撃たれて消滅、かつフォメーション所属の場合、
        //フォーメーションに自身が撃たれた事を伝える。
        if ((pOther->getKind() & KIND_MY) && (getParent()->_obj_class & Obj_GgafDx9FormationActor)) {
            ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();

        Item* pItem = (Item*)P_COMMON_SCENE->_pDP_MagicPointItem001->dispatch();
        if (pItem) {
            pItem->locateAs(this);
        }
    }
}

void EnemyEunomia::onInactive() {
    sayonara();
}

EnemyEunomia::~EnemyEunomia() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}


