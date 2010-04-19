#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyJuno::EnemyJuno(const char* prm_name) : DefaultMeshSetActor(prm_name, "Ceres") {
    _class_name = "EnemyJuno";
    MyStgUtil::resetEnemyJunoStatus(_pStatus);
    _pDispatcher_ShotEffect = NULL;
    _pDispatcher_Shot = NULL;
    _iMovePatternNo = 0;
    _nMaxShot = 1;
    _nShot = 0;
    _can_Shot = false;
    _do_Shot = false;
    _pSeReflector->useSe(1);
    _pSeReflector->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
}


void EnemyJuno::initialize() {
    setHitAble(false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliBox(0, -10000, -10000, 10000, 10000);
    _pMover->setFaceAngVelo(AXIS_X, 5000);
    _pMover->forceMvVeloRange(1, _pMover->_veloMv);
}

void EnemyJuno::onActive() {
    MyStgUtil::resetEnemyJunoStatus(_pStatus);
    setHitAble(true);
    _do_Shot = false;
    _can_Shot = ((CmRandomNumberGenerator::getInstance()->genrand_int32() % 2) == 0) ? true : false;
    _nShot = 0;
    _frame_when_shot = 0;
}

void EnemyJuno::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_do_Shot) {
        if (getPartFrame() == _frame_when_shot - 30) {
            _pMover->setMvVelo(0); //減速
            chengeEffectTechniqueInterim("Flush", 2); //フラッシュ
        } else if (getPartFrame() == _frame_when_shot) {
            if (_pDispatcher_Shot) {
                GgafDx9DrawableActor* pShot = (GgafDx9DrawableActor*)_pDispatcher_Shot->employ();
                if (pShot) {
                    _nShot++;
                    pShot->setGeometry(this);
                    pShot->_pMover->relateRzRyFaceAngToMvAng(true);
                    pShot->_pMover->setMvAng(pMYSHIP);
                    pShot->activate();
                    _do_Shot = false;
                    chengeEffectTechniqueInterim("Flush", 2); //フラッシュ
                }
                //ショット発射エフェクト
                if (_pDispatcher_ShotEffect) {
                }
                _pMover->setMvVelo(1000000); //加速
            }
        }
    } else {
        if (_can_Shot) {
            if (pMYSHIP->_Z - 500000 < _Z && _Z < pMYSHIP->_Z + 500000 &&
                pMYSHIP->_Y - 500000 < _Y && _Y < pMYSHIP->_Y + 500000 &&
                _nMaxShot > _nShot
            ) {
                _frame_when_shot = getPartFrame() + (CmRandomNumberGenerator::getInstance()->genrand_int32() % 60);
                _do_Shot = true;
            }
        }
    }





    _pMover->behave();
}

void EnemyJuno::processJudgement() {
    if (isOutOfGameSpace()) {
        inactivate();
    }
}

void EnemyJuno::onInactive() {
    setHitAble(false);
}

void EnemyJuno::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        _pSeReflector->play3D(0);
        EffectExplosion001* pExplo001 = (EffectExplosion001*)GameGlobal::_pSceneCommon->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        inactivate();
    }
}

EnemyJuno::~EnemyJuno() {
}
