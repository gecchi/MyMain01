#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyTamago01::EnemyTamago01(const char* prm_name) : DefaultMeshActor(prm_name, "Tamago") {
    _class_name = "EnemyTamago01";
    MyStgUtil::resetEnemyTamago01Status(_pStatus);
    _iMovePatternNo = 0;
    _pProgram_Tamago01Move = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
}

void EnemyTamago01::initialize() {
    setCollisionable(true);
    _pMover->relateRzRyFaceAngleToMoveAngle(true);
    _pMover->setFaceAngleVelocity(AXIS_X, 5000);
    _pCollisionChecker->makeCollision(1);
    //_pCollisionChecker->setColliSphere(0, 50000);
    _pCollisionChecker->setColliBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    useSe2("bomb1");     //爆発
    _X = -100000;
    _Y = -100000;
    _Z = -100000;
    _pScaler->setScale(4000);
}

void EnemyTamago01::onActive() {
    MyStgUtil::resetEnemyTamago01Status(_pStatus);
    if (_pProgram_Tamago01Move) {
        _pMover->executeSplineMoveProgram(_pProgram_Tamago01Move, 0); //スプライン移動をプログラムしておく
    }
    _iMovePatternNo = 0;
}

void EnemyTamago01::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_iMovePatternNo == 0) {
        //スプライン移動中
        if (_pProgram_Tamago01Move && !(_pProgram_Tamago01Move->isExecuting())) {
            _iMovePatternNo++; //スプライン移動が終了したら次の行動パターンへ
        }
    }

    if (_iMovePatternNo == 1) {
        //スプライン移動終了時
        _pMover->executeTagettingMoveAngleSequence(pMYSHIP->_X+800000, pMYSHIP->_Y, pMYSHIP->_Z, 2000, TURN_CLOSE_TO);
        if (_pDispatcher_Shot) {
            //放射状ショット発射
            GgafDx9DrawableActor* pActor;
            pActor = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
            if (pActor) {
                pActor->setGeometry(this);
                pActor->activate();
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
        _iMovePatternNo++;
    }

    if (_iMovePatternNo == 3) {

    }

    _pMover->behave();
    _pScaler->behave();

}

void EnemyTamago01::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyTamago01::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
    playSe2();
    if (pExplo001 != NULL) {
        pExplo001->activate();
        pExplo001->setGeometry(this);
    }

    if (MyStgUtil::calcEnemyStamina(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {


        //inactivate();
    }
}

void EnemyTamago01::onInactive() {
    //adios();
}

EnemyTamago01::~EnemyTamago01() {
    DELETE_POSSIBLE_NULL(_pProgram_Tamago01Move);
}
