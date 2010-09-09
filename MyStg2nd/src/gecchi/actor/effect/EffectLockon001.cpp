#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockOn001::EffectLockOn001(const char* prm_name) : DefaultSpriteSetActor(prm_name, "8/LockOn001") {
    _class_name = "EffectLockOn001";
    //_pTarget = NULL;
    _max_lock_num = 5;
    inactivateImmediately();
    defineRotMvWorldMatrix(GgafDx9Util::setWorldMatrix_RzBxyzMv); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    chengeEffectTechnique("DestBlendOne"); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnable(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //Z�o�b�t�@�͏������ݖ����ɋ���
    setSpecialDrawDepth(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    setAlpha(9.9);          //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B

    setHitAble(false); //�����蔻�薳��
    _pSeTransmitter->useSe(1);                                                //�g�p���ʉ����錾
    _pSeTransmitter->set(0, "humei10", GgafRepeatSeq::nextVal("CH_humei10")); //���ʉ���`

//    _pEffectLockOn_Release = NEW EffectLockOn001_Release("EffectLockOn001_R", this);
//    _pEffectLockOn_Release->inactivateImmediately();
//    addSubGroup(_pEffectLockOn_Release);

    setProgress(EffectLockOn001_PROG_NOTHING);
}

void EffectLockOn001::initialize() {
    _pUvFlipper->forcePtnNoRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //�A�j������
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void EffectLockOn001::onActive() {
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //��]
    _pSeTransmitter->play3D(0); //���b�N�I��SE
    setProgress(EffectLockOn001_PROG_LOCK);
}

void EffectLockOn001::processBehavior() {
    if (getProgress() == EffectLockOn001_PROG_LOCK) {
        if (getAlpha() < 1.0) {
             addAlpha(0.01);
         }
         if (_pScaler->_method[0] == NOSCALE) {
             //�k��������ABeat
             _pScaler->forceScaleRange(2000, 4000);
             _pScaler->beat(30, 2, 2, -1); //�������[�v
         }
    }

    if (getProgress() == EffectLockOn001_PROG_RELEASE) {
        addAlpha(-0.04);
        if (_pScaler->_method[0] == NOSCALE) {
            setProgress(EffectLockOn001_PROG_NOTHING);
            inactivate();
        }
    }

    if (_pTarget) {
        if (_pTarget->isActive() || _pTarget->_will_activate_after_flg) {
            if (abs(_pTarget->_X-_X) <= 200000 &&
                abs(_pTarget->_Y-_Y) <= 200000 &&
                abs(_pTarget->_Z-_Z) <= 200000) {
                setGeometry(_pTarget);
                _pMover->setMvVelo(0);
            } else {
                _pMover->setMvAng(_pTarget);
                _pMover->setMvVelo(200000);
            }
        } else {
            setProgress(EffectLockOn001_PROG_RELEASE);
        }
    } else {
        setProgress(EffectLockOn001_PROG_RELEASE);
    }

    if (getProgress() != EffectLockOn001_PROG_NOTHING) {
        _pUvFlipper->behave();
        _pMover->behave();
        _pScaler->behave();
    }
}

void EffectLockOn001::processJudgement() {

//    if (_fAlpha < 0) {
//        inactivate();
//    }
}

void EffectLockOn001::onInactive() {
}

void EffectLockOn001::lockOn(GgafDx9GeometricActor* prm_pTarget) {
    if (ringTarget.indexOf(prm_pTarget) >= 0) {
        if (getProgress() == EffectLockOn001_PROG_NOTHING) {
            setGeometry(prm_pTarget);
            setProgress(EffectLockOn001_PROG_RELEASE);
        } else if (getProgress() == EffectLockOn001_PROG_LOCK && _pTarget != prm_pTarget) {
            _pSeTransmitter->play3D(0); //���b�N�I��SE
        } else if (getProgress() == EffectLockOn001_PROG_RELEASE && _pTarget != prm_pTarget) {
            _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
            _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
            _pMover->setFaceAngVelo(AXIS_Z, 1000);   //��]
            _pSeTransmitter->play3D(0); //���b�N�I��SE
            setProgress(EffectLockOn001_PROG_RELEASE);
        }
        _ringTarget.addLast(prm_pTarget);
    }
}


void EffectLockOn001::releaseLockOn() {
    if (getProgress() == EffectLockOn001_PROG_NOTHING) {
        setProgress(EffectLockOn001_PROG_RELEASE);
        inactivate();
    } else if (getProgress() == EffectLockOn001_PROG_RELEASE) {
        //��������
    } else if (getProgress() == EffectLockOn001_PROG_LOCK) {
        _pScaler->forceScaleRange(20000, 2000); //�X�P�[�����O�E�͈�
        _pScaler->intoTargetScaleLinerUntil(20000, 50);//�X�P�[�����O
        _pMover->setFaceAngVelo(AXIS_Z, _pMover->_angveloFace[AXIS_Z]*-3); //�����t��]
        setProgress(EffectLockOn001_PROG_RELEASE);
    }
    _pTarget = NULL;
}

EffectLockOn001::~EffectLockOn001() {
}

