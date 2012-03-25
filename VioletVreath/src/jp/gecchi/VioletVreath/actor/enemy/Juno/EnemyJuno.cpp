#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyJuno::EnemyJuno(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Pallas", STATUS(EnemyJuno)) {
    _class_name = "EnemyJuno";
    pDepo_ShotEffect_ = NULL;
    pDepo_Shot_ = NULL;
    iMovePatternNo_ = 0;
    max_shots_ = 1;
    shot_num_ = 0;
    can_Shot_ = false;
    do_Shot_ = false;
    velo_mv_begin_ = 0;
    _pSeTransmitter->useSe(2);
    _pSeTransmitter->set(0, "bomb1", GgafRepeatSeq::nextVal("CH_bomb1"));     //����
    _pSeTransmitter->set(1, "cm-22", GgafRepeatSeq::nextVal("CH_cm-22"));     //����
}

void EnemyJuno::onCreateModel() {
//    _pModel->_pTextureBlinker->forceBlinkRange(0.5, 2.0);
//    _pModel->_pTextureBlinker->setBlink(0.5);
//    _pModel->_pTextureBlinker->beat(60, 3, 1, -1);
//    _pModel->blink_threshold_ = 0.8;
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
    do_Shot_ = false;
    //can_Shot_ = ((CmRandomNumberGenerator::getInstance()->genrand_int32() % 2) == 0) ? true : false;
    can_Shot_ = true;
    shot_num_ = 0;
    frame_when_shot_ = 0;
    velo_mv_begin_ = _pKurokoA->_veloMv; //�����ړ����x��ۑ�
    _pKurokoA->setFaceAng(AXIS_X, 0);
    //_pKurokoA->execTurnMvAngSequence(P_MYSHIP, 50, 0, TURN_CLOSE_TO, false);
}

void EnemyJuno::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    if (do_Shot_) {
        if (getActivePartFrame() == frame_when_shot_) {
            _pKurokoA->setMvVelo(500); //����
            _pKurokoA->execTurnRxSpinAngSequence(D180ANG, 8000, 0, TURN_CLOCKWISE);
        } else if (getActivePartFrame() == frame_when_shot_ + 20) {
            if (pDepo_Shot_) {
                GgafDxDrawableActor* pShot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                if (pShot) {
                    shot_num_++;
                    pShot->locateAs(this);
                    pShot->_pKurokoA->relateFaceAngWithMvAng(true);
                    pShot->_pKurokoA->setMvAng(P_MYSHIP);
                    pShot->reset();
                    do_Shot_ = false;
                    changeEffectTechniqueInterim("Flush", 2); //�t���b�V��
                    _pSeTransmitter->play3D(1);

                }
                //�V���b�g���˃G�t�F�N�g
                if (pDepo_ShotEffect_) {
                }
                _pKurokoA->setMvVelo(velo_mv_begin_); //�ĉ���
            }
        }
    } else {
        if (can_Shot_) {
            if (P_MYSHIP->_Z - 500000 < _Z && _Z < P_MYSHIP->_Z + 500000 &&
                P_MYSHIP->_Y - 500000 < _Y && _Y < P_MYSHIP->_Y + 500000 &&
                max_shots_ > shot_num_
            ) {
                frame_when_shot_ = getActivePartFrame() + (CmRandomNumberGenerator::getInstance()->genrand_int32() % 60) + 1;
                do_Shot_ = true;
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
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->pDP_EffectExplosion001_->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
            pExplo001->_pKurokoA->takeoverMvFrom(_pKurokoA);
        }
        sayonara();
    }
}

EnemyJuno::~EnemyJuno() {
}