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
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
    _pSeTransmitter->useSe(1);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    useProgress(10);
}

void EnemyEunomia::onCreateModel() {
}

void EnemyEunomia::initialize() {
    setHitAble(true);
    _pKuroko->setFaceAngVelo(AXIS_X, -4000);
    _pKuroko->relateRzRyFaceAngToMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyEunomia::onReset() {
    MyStgUtil::resetEnemyEunomiaStatus(_pStatus);
    _iMovePatternNo = 0; //行動パターンリセット
    _pProgress->change(1);
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
    if (_pProgress->wasChangedTo(1)) {
        _pSplineProgram->begin(0); //スプライン移動を開始(1:座標相対)
    }
    if (_pProgress->get() == 1) {
        //スプライン移動終了待ち
        if (_pSplineProgram->isExecuting()) {
            //待ちぼうけ
        } else {
            _pProgress->changeNext(); //次のパターンへ
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
            if (_pDispatcher_Shot) {
                //放射状ショット
                int way = 10+_RANK_*10; //ショットWAY数
                angle* paAngWay = NEW angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                    if (pActor_Shot) {
                        pActor_Shot->locateAs(this);
                        pActor_Shot->_pKuroko->setRzRyMvAng(paAngWay[i], ANGLE90);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //ショット発射エフェクト
                if (_pDispatcher_ShotEffect) {
                    GgafDx9DrawableActor* pEffectActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_ShotEffect->employ();
                    if (pEffectActor_Shot) {
                        pEffectActor_Shot->locateAs(this);
                        pEffectActor_Shot->activate();
                    }
                }
            }
//            //自機へ方向転換
            _pKuroko->orderTagettingMvAngSequence(P_MYSHIP->_X, _Y, P_MYSHIP->_Z,
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
    _pKuroko->behave();
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->employ();
        _pSeTransmitter->play3D(0);
        if (pExplo001) {
            pExplo001->activate();
            pExplo001->locateAs(this);
            pExplo001->_pKuroko->takeoverMvFrom(_pKuroko);
        }

        //自機側に撃たれて消滅、かつフォメーション所属の場合、
        //フォーメーションに自身が撃たれた事を伝える。
        if ((pOther->getKind() & KIND_MY) && (getParent()->_obj_class & Obj_GgafDx9FormationActor)) {
            ((GgafDx9FormationActor*)getParent())->wasDestroyedFollower(this);
        }
        setHitAble(false); //消滅した場合、同一フレーム内の以降の処理でヒットさせないため（重要）
        sayonara();

        Item* pItem = (Item*)P_COMMON_SCENE->_pDP_MagicPointItem001->employ();
        if (pItem) {
            pItem->locateAs(this);
            pItem->activate();
        }
    }
}

void EnemyEunomia::onInactive() {
    sayonara();
}

EnemyEunomia::~EnemyEunomia() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}
