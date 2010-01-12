#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyIris::EnemyIris(const char* prm_name) : DefaultMeshSetActor(prm_name, "8/Iris") {
    _class_name = "EnemyIris";
    MyStgUtil::resetEnemyIrisStatus(this);
    _iMovePatternNo = 0;
    _pProgram_IrisMove = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
}

void EnemyIris::initialize() {
    setBumpable(true);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
    _pMover->setFaceAngleVelocity(AXIS_X, 5000);
    _pStgChecker->useHitAreaBoxNum(1);
    _pStgChecker->setHitAreaBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    _pStgChecker->setStatus(100, 99999, 99999, 99999);
    useSe2("bomb1");     //爆発
    onActive();
}

void EnemyIris::onActive() {
    MyStgUtil::resetEnemyIrisStatus(this);
    if (_pProgram_IrisMove) {
        _pMover->executeSplineMoveProgram(_pProgram_IrisMove, 0); //スプライン移動をプログラムしておく
    }
    _iMovePatternNo = 0;
}

void EnemyIris::processBehavior() {

    if (_iMovePatternNo == 0) {
        //スプライン移動中
        if (!(_pProgram_IrisMove->isExecuting())) {
            _iMovePatternNo++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (_iMovePatternNo == 1) {
        //スプライン移動終了時
        _pMover->executeTagettingMoveAngleSequence(pMYSHIP->_X+800000, pMYSHIP->_Y, pMYSHIP->_Z, 2000, TURN_CLOSE_TO);
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
                    pActor->_pMover->relateRzRyFaceAngleToMoveAngle(true);
                    pActor->_pMover->setRzRyMoveAngle(-ANGLE180 + aAngWay[i], ANGLE90);
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
            _pMover->executeTagettingMoveAngleSequence(MyShip::_lim_behaind - 500000 , _Y, _Z, 2000, TURN_CLOSE_TO);
            _pMover->setMoveVeloAcceleration(100);
            _iMovePatternNo++;
        }
    }

    if (_iMovePatternNo == 3) {

    }

    _pMover->behave();

}

void EnemyIris::processJudgement() {
    if (isOutOfGameSpace()) {
        adios();
    }
}

void EnemyIris::processOnHit(GgafActor* prm_pActor_Opponent) {
    //_TRACE_("EnemyIris::processOnHit!!! this="<<getName()<<"("<<_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");
	//_TRACE_("EnemyIris::processOnHit!!! prm_pActor_Opponent="<<prm_pActor_Opponent->getName()<<"("<<prm_pActor_Opponent->_pStatus->get(STAT_DEFAULT_ACTOR_KIND)<<")");


    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe2();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }
    adios();
}

EnemyIris::~EnemyIris() {
    DELETE_POSSIBLE_NULL(_pProgram_IrisMove);
}
