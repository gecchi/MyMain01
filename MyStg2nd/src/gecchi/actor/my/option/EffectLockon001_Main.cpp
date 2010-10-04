#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001_Main::EffectLockon001_Main(const char* prm_name) : EffectLockon001(prm_name, "8/Lockon001") {
    _class_name = "EffectLockon001_Main";
}

void EffectLockon001_Main::initialize() {
    EffectLockon001::initialize();
    _pUvFlipper->forcePtnNoRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //�A�j������
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void EffectLockon001_Main::onActive() {
    EffectLockon001::onActive();
    _pUvFlipper->setPtnNoToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    _pMover->setFaceAngVelo(AXIS_Z, 1000);        //��]
    _pSeTransmitter->play3D(0); //���b�N�I��SE
    setGeometry(_pTarget);
    setProgress(EffectLockon001_PROG_FIRST_LOCK);
}

void EffectLockon001_Main::processBehavior() {
    EffectLockon001::processBehavior();



    if (getProgress() == EffectLockon001_PROG_LOCK || getProgress() == EffectLockon001_PROG_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
             addAlpha(0.01);
         }
         if (_pScaler->_method[0] == NOSCALE) {
             //�k��������ABeat
             _pScaler->forceScaleRange(2000, 4000);
             _pScaler->beat(30, 2, 2, -1); //�������[�v
             setProgress(EffectLockon001_PROG_LOCK);
         }
         if (_pTarget) {
             if (_pTarget->isActive() || _pTarget->_will_activate_after_flg) {
                 if (abs(_pTarget->_X-_X) <= 200000 &&
                     abs(_pTarget->_Y-_Y) <= 200000 &&
                     abs(_pTarget->_Z-_Z) <= 200000) {
                     setGeometry(_pTarget);
                     _pMover->setMvVelo(0);
                     _pMover->_angveloFace[AXIS_Z] = 1000;
                 } else {
                     _pMover->_angveloFace[AXIS_Z] = 3000; //������
                     _pMover->setMvAng(_pTarget);
                     _pMover->setMvVelo(200000);
                 }
             } else {
                 setProgress(EffectLockon001_PROG_RELEASE);
             }
         } else {
             setProgress(EffectLockon001_PROG_RELEASE);
         }
    }

    if (getProgress() == EffectLockon001_PROG_RELEASE) {
        _pTarget = NULL;
        addAlpha(-0.05);
        if (_pScaler->_method[0] == NOSCALE || getAlpha() <= 0.0) {
            _pScaler->setScale(2000);
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pMover->behave();
    _pScaler->behave();

}

void EffectLockon001_Main::processJudgement() {
    EffectLockon001::processJudgement();
}

void EffectLockon001_Main::onInactive() {
    EffectLockon001::onInactive();
}

void EffectLockon001_Main::lockon(GgafDx9GeometricActor* prm_pTarget) {
    if (prm_pTarget == NULL || _pTarget == prm_pTarget) {
        return;
    }
    _pTarget = prm_pTarget;

    if (getProgress() == EffectLockon001_PROG_FIRST_LOCK) {

    } else if (getProgress() == EffectLockon001_PROG_LOCK) {
    } else if (getProgress() == EffectLockon001_PROG_RELEASE) {
        _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
        _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
        _pMover->setFaceAngVelo(AXIS_Z, 1000);   //��]
        _pSeTransmitter->play3D(0); //���b�N�I��SE
        setProgress(EffectLockon001_PROG_FIRST_LOCK);
    }

}
void EffectLockon001_Main::releaseLockon() {
    if (isActive()) {
        if (getProgress() == EffectLockon001_PROG_FIRST_LOCK) {
            _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
            _pScaler->intoTargetScaleLinerUntil(60000, 60);//�X�P�[�����O
            _pMover->setFaceAngVelo(AXIS_Z, _pMover->_angveloFace[AXIS_Z]*-3); //�����t��]
            setProgress(EffectLockon001_PROG_RELEASE);
        } else if (getProgress() == EffectLockon001_PROG_LOCK) {
            _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
            _pScaler->intoTargetScaleLinerUntil(60000, 60);//�X�P�[�����O
            _pMover->setFaceAngVelo(AXIS_Z, _pMover->_angveloFace[AXIS_Z]*-3); //�����t��]
            setProgress(EffectLockon001_PROG_RELEASE);
        } else if (getProgress() == EffectLockon001_PROG_RELEASE) {
            //��������
        }
    }
    _pTarget = NULL;
}

EffectLockon001_Main::~EffectLockon001_Main() {
}
