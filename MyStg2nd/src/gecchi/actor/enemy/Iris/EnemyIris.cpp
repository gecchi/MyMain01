#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool EnemyIris::_is_init_class = false;

EnemyIris::EnemyIris(const char* prm_name) : DefaultMeshSetActor(prm_name, "Iris") {
    _class_name = "EnemyIris";
    MyStgUtil::resetEnemyIrisStatus(_pStatus);
    _iMovePatternNo = 0;
    _pProgram_IrisMove = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
}

void EnemyIris::initEnemyIrisClass() {
    _pGgafDx9Model->_pTextureBlinker->setBlinkRange(0.5, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(30, 3, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void EnemyIris::initialize() {
    if (EnemyIris::_is_init_class == false) {
        initEnemyIrisClass();
        EnemyIris::_is_init_class = true;
    }
    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    _pMover->setFaceAngVelo(AXIS_X, 5000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    useSe2("bomb1");     //爆発
}

void EnemyIris::onActive() {
    MyStgUtil::resetEnemyIrisStatus(_pStatus);
    if (_pProgram_IrisMove) {
        _pMover->executeSplineMoveProgram(_pProgram_IrisMove, 0); //スプライン移動をプログラムしておく
    }
    _iMovePatternNo = 0;
}

void EnemyIris::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_iMovePatternNo == 0) {
        //スプライン移動中
        if (!(_pProgram_IrisMove->isExecuting())) {
            _iMovePatternNo++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (_iMovePatternNo == 1) {
        //スプライン移動終了時
        _pMover->execTagettingMvAngSequence(pMYSHIP->_X+800000, pMYSHIP->_Y, pMYSHIP->_Z,
                                                   2000, 0,
                                                   TURN_CLOSE_TO);
        if (_pDispatcher_Shot) {
            //放射状ショット発射
            int way = 5+5*_RANK_;
            angle* aAngWay = new angle[way];
            GgafDx9Util::getRadiationAngle2D(0, way, aAngWay);
            GgafDx9DrawableActor* pActor;
            for (int i = 0; i < way; i++) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->setGeometry(this);
                    pActor->_pMover->relateRzRyFaceAngToMvAng(true);
                    pActor->_pMover->setRzRyMvAng(-ANGLE180 + aAngWay[i], ANGLE90);
                    pActor->activate();
                }
            }
            //ショット発射エフェクト
            if (_pDispatcher_ShotEffect) {
                pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pActor) {
                    pActor->setGeometry(_X, _Y, _Z);
                }
            }

        }
        _iMovePatternNo++; //次の行動パターンへ
    }

    if (_iMovePatternNo == 2) {
        if (_Z-10000 < pMYSHIP->_Z && pMYSHIP->_Z < _Z+10000) {
            //自機とZ軸が接近
            _pMover->execTagettingMvAngSequence(MyShip::_lim_behaind - 500000 , _Y, _Z,
                                                       2000, 0,
                                                       TURN_CLOSE_TO);
            _pMover->setMvAcce(100);
            _iMovePatternNo++;
        }
    }

    if (_iMovePatternNo == 3) {

    }

    _pMover->behave();

}

void EnemyIris::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyIris::onHit(GgafActor* prm_pOtherActor) {
    //_TRACE_("EnemyIris::onHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    //_TRACE_("EnemyIris::onHit!!! prm_pOtherActor="<<prm_pOtherActor->getName()<<"("<<prm_pOtherActor->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {

        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        playSe2();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        inactivate();
    }
}

void EnemyIris::onInactive() {
    adios();
}

EnemyIris::~EnemyIris() {
    DELETE_POSSIBLE_NULL(_pProgram_IrisMove);
}
