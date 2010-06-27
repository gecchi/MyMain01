#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyPallas::EnemyPallas(const char* prm_name) : DefaultMeshSetActor(prm_name, "Pallas") {
    _class_name = "EnemyPallas";
    MyStgUtil::resetEnemyPallasStatus(_pStatus);
    _iMovePatternNo = 0;
    _pSplineProgram = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
    _pSeReflector->useSe(1);
    _pSeReflector->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}

void EnemyPallas::onCreateModel() {
}

void EnemyPallas::initialize() {
    setHitAble(true);
	_pMover->setFaceAngVelo(AXIS_Z, -7000);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 40000);
}

void EnemyPallas::onActive() {
    MyStgUtil::resetEnemyPallasStatus(_pStatus);

    _iMovePatternNo = 0; //行動パターンリセット
}

void EnemyPallas::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

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
                int way = 5+5*_RANK_; //ショットWAY数
                angle* paAngWay = new angle[way];
                GgafDx9Util::getRadialAngle2D(0, way, paAngWay);
                GgafDx9DrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                    if (pActor_Shot) {
                        pActor_Shot->setGeometry(this);
                        pActor_Shot->_pMover->setRzRyMvAng(paAngWay[i], ANGLE90);
                        pActor_Shot->activate();
                    }
                }
                DELETEARR_IMPOSSIBLE_NULL(paAngWay);
                //ショット発射エフェクト
                if (_pDispatcher_ShotEffect) {
                    GgafDx9DrawableActor* pActo_Effect = (GgafDx9DrawableActor*)_pDispatcher_ShotEffect->employ();
                    if (pActo_Effect) {
                        pActo_Effect->setGeometry(this);
                        pActo_Effect->activate();
                    }
                }
            }
//            //自機へ方向転換
            _pMover->execTagettingMvAngSequence(pMYSHIP->_X, _Y, pMYSHIP->_Z,
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
    _pMover->behave();
    //_pSeReflector->behave();
}

void EnemyPallas::processJudgement() {
    if (isOutOfGameSpace()) {
        sayonara();
    }
}

void EnemyPallas::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyPallas::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyPallas::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {

        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        _pSeReflector->play3D(0);
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        sayonara();
    }
}

void EnemyPallas::onInactive() {
    sayonara();
}

EnemyPallas::~EnemyPallas() {
    DELETE_POSSIBLE_NULL(_pSplineProgram);
}
