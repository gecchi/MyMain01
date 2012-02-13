#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyJuno::EnemyJuno(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Pallas", STATUS(EnemyJuno)) {
    _class_name = "EnemyJuno";
    _pDepo_ShotEffect = NULL;
    _pDepo_Shot = NULL;
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
//    _pModel->_pTextureBlinker->forceBlinkRange(0.5, 2.0);
//    _pModel->_pTextureBlinker->setBlink(0.5);
//    _pModel->_pTextureBlinker->beat(60, 3, 1, -1);
//    _pModel->_blink_threshold = 0.8;
}

void EnemyJuno::initialize() {
    setHitAble(false);
    _pCollisionChecker->makeCollision(1);
    _pCollisionChecker->setColliAAB_Cube(0, 45000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -7000);
    _pKurokoA->forceMvVeloRange(1, _pKurokoA->_veloMv);
}

void EnemyJuno::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _do_Shot = false;
    //_can_Shot = ((CmRandomNumberGenerator::getInstance()->genrand_int32() % 2) == 0) ? true : false;
    _can_Shot = true;
    _nShot = 0;
    _frame_when_shot = 0;
    _veloMv_begin = _pKurokoA->_veloMv; //初期移動速度を保存
    _pKurokoA->setFaceAng(AXIS_X, 0);
    //_pKurokoA->execTurnMvAngSequence(P_MYSHIP, 50, 0, TURN_CLOSE_TO, false);
}

void EnemyJuno::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (_do_Shot) {
        if (getActivePartFrame() == _frame_when_shot) {
            _pKurokoA->setMvVelo(500); //減速
            _pKurokoA->execTurnRxSpinAngSequence(D180ANG, 8000, 0, TURN_CLOCKWISE);
        } else if (getActivePartFrame() == _frame_when_shot + 20) {
            if (_pDepo_Shot) {
                GgafDxDrawableActor* pShot = (GgafDxDrawableActor*)_pDepo_Shot->dispatch();
                if (pShot) {
                    _nShot++;
                    pShot->locateAs(this);
                    pShot->_pKurokoA->relateFaceAngWithMvAng(true);
                    pShot->_pKurokoA->setMvAng(P_MYSHIP);
                    pShot->reset();
                    _do_Shot = false;
                    changeEffectTechniqueInterim("Flush", 2); //フラッシュ
                    _pSeTransmitter->play3D(1);

                }
                //ショット発射エフェクト
                if (_pDepo_ShotEffect) {
                }
                _pKurokoA->setMvVelo(_veloMv_begin); //再加速
            }
        }
    } else {
        if (_can_Shot) {
            if (P_MYSHIP->_Z - 500000 < _Z && _Z < P_MYSHIP->_Z + 500000 &&
                P_MYSHIP->_Y - 500000 < _Y && _Y < P_MYSHIP->_Y + 500000 &&
                _nMaxShot > _nShot
            ) {
                _frame_when_shot = getActivePartFrame() + (CmRandomNumberGenerator::getInstance()->genrand_int32() % 60) + 1;
                _do_Shot = true;
            }
        }
    }
    _pKurokoA->behave();
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
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (MyStgUtil::calcEnemyStatus(_pStatus, getKind(), pOther->_pStatus, pOther->getKind()) <= 0) {
        _pSeTransmitter->play3D(0);
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        sayonara();
    }
}

EnemyJuno::~EnemyJuno() {
}
