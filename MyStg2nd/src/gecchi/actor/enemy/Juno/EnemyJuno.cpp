#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EnemyJuno::EnemyJuno(const char* prm_name) : DefaultMeshSetActor(prm_name, "Pallas") {
    _class_name = "EnemyJuno";
    MyStgUtil::resetEnemyJunoStatus(_pStatus);
    _pDispatcher_ShotEffect = NULL;
    _pDispatcher_Shot = NULL;
    _iMovePatternNo = 0;
    _nMaxShot = 1;
    _nShot = 0;
    _can_Shot = false;
    _do_Shot = false;
    _veloMv_begin = 0;
    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //爆発
    _pSeTransmitter->set(1, "cm-22", GgafRepeatSeq::nextVal("CH_cm-22"));     //発射
}

void EnemyJuno::onCreateModel() {
//    _pGgafDx9Model->_pTextureBlinker->forceBlinkRange(0.5, 2.0);
//    _pGgafDx9Model->_pTextureBlinker->setBlink(0.5);
//    _pGgafDx9Model->_pTextureBlinker->beat(60, 3, 1, -1);
//    _pGgafDx9Model->_fBlinkThreshold = 0.8;
}

void EnemyJuno::initialize() {
    setHitAble(false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 45000);
    _pMover->setFaceAngVelo(AXIS_Z, -7000);
    _pMover->forceMvVeloRange(1, _pMover->_veloMv);
}

void EnemyJuno::onActive() {
    MyStgUtil::resetEnemyJunoStatus(_pStatus);
    setHitAble(true);
    _do_Shot = false;
    //_can_Shot = ((CmRandomNumberGenerator::getInstance()->genrand_int32() % 2) == 0) ? true : false;
    _can_Shot = true;
    _nShot = 0;
    _frame_when_shot = 0;
    _veloMv_begin = _pMover->_veloMv; //初期移動速度を保存
    _pMover->setFaceAng(AXIS_X, 0);
    //_pMover->execTagettingMvAngSequence(pMYSHIP, 50, 0, TURN_CLOSE_TO, false);
}

void EnemyJuno::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_do_Shot) {
        if (getActivePartFrame() == _frame_when_shot) {
            _pMover->setMvVelo(500); //減速
            _pMover->execTagettingRxSpinAngleSequence(ANGLE180, 8000, 0, TURN_CLOCKWISE);
        } else if (getActivePartFrame() == _frame_when_shot + 20) {
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
                    _pSeTransmitter->play3D(1);

                }
                //ショット発射エフェクト
                if (_pDispatcher_ShotEffect) {
                }
                _pMover->setMvVelo(_veloMv_begin); //再加速
            }
        }
    } else {
        if (_can_Shot) {
            if (pMYSHIP->_Z - 500000 < _Z && _Z < pMYSHIP->_Z + 500000 &&
                pMYSHIP->_Y - 500000 < _Y && _Y < pMYSHIP->_Y + 500000 &&
                _nMaxShot > _nShot
            ) {
                _frame_when_shot = getActivePartFrame() + (CmRandomNumberGenerator::getInstance()->genrand_int32() % 60) + 1;
                _do_Shot = true;
            }
        }
    }





    _pMover->behave();
}

void EnemyJuno::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyJuno::onInactive() {
    setHitAble(false);
}

void EnemyJuno::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        _pSeTransmitter->play3D(0);
        EffectExplosion001* pExplo001 = (EffectExplosion001*)pCOMMONSCENE->_pDispatcher_EffectExplosion001->employ();
        if (pExplo001 != NULL) {
            pExplo001->activate();
            pExplo001->setGeometry(this);
        }
        sayonara();
    }
}

EnemyJuno::~EnemyJuno() {
}
