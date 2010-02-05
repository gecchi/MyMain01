#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

bool EnemyTamago01::_is_init_class = false;

EnemyTamago01::EnemyTamago01(const char* prm_name) : DefaultMeshActor(prm_name, "Flora") {
    _class_name = "EnemyTamago01";
    MyStgUtil::resetEnemyTamago01Status(_pStatus);
    _iMovePatternNo = 0;
    _pProgram_Tamago01Move = NULL;
    _pDispatcher_Shot = NULL;
    _pDispatcher_ShotEffect = NULL;
}

void EnemyTamago01::initEnemyTamago01Class() {
    _pGgafDx9Model->_pTextureBlinker->setBlinkRange(0.1, 1.0);
    _pGgafDx9Model->_pTextureBlinker->setBlink(0.1);
    _pGgafDx9Model->_pTextureBlinker->beat(120, 60, 1, -1);
    _pGgafDx9Model->_fBlinkThreshold = 0.9;
}

void EnemyTamago01::initialize() {
    if (EnemyTamago01::_is_init_class == false) {
        initEnemyTamago01Class();
        EnemyTamago01::_is_init_class = true;
    }
    setHitAble(true);
    _pMover->relateRzRyFaceAngToMvAng(true);
    //_pMover->setFaceAngVelo(AXIS_X, 5000);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliSphere(0, 90000);
    //_pCollisionChecker->setColliBox(0, -30000, -30000, -30000, 30000, 30000, 30000);
    useSe2("bomb1");     //爆発
    _X = 300000;
    _Y = 300000;
    _Z = 300000;
    _pScaler->setScale(5000);
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
        _pMover->execTagettingMvAngSequence(pMYSHIP->_X+800000, pMYSHIP->_Y, pMYSHIP->_Z,
                                                   2000, 0,
                                                   TURN_CLOSE_TO);
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
    if (_frame_of_active % 180 == 0) {
        _pMover->execTagettingMvAngSequence(pMYSHIP, 2000,0,TURN_CLOSE_TO);
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
