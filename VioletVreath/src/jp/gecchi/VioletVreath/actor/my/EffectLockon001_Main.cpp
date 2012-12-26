#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockon001_Main::EffectLockon001_Main(const char* prm_name) :
        EffectLockon001(prm_name, "8/Lockon001") {
    _class_name = "EffectLockon001_Main";
}

void EffectLockon001_Main::initialize() {
    EffectLockon001::initialize();
    _pUvFlipper->forcePtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //�A�j������
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void EffectLockon001_Main::onActive() {
    EffectLockon001::onActive();
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.01);
    _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
    _pScaler->setScale(60000); //(6000%)
    _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //��]
    _pSeTx->play3D(0); //���b�N�I��SE


    if (pTarget_) {
        locateWith(pTarget_);
        _pProg->set(LOCKON001_PROG_FIRST_LOCK);
    } else {
        setAlpha(0.00);
        _pProg->set(LOCKON001_PROG_RELEASE);
    }
}

void EffectLockon001_Main::processBehavior() {
    EffectLockon001::processBehavior();

    if (_pProg->get() == LOCKON001_PROG_LOCK || _pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
             addAlpha(0.01);
         }
         if (_pScaler->_method[0] == NOSCALE) {
             //�k��������ABeat
             _pScaler->forceScaleRange(2000, 4000);
             _pScaler->beat(30, 2, 2, -1); //�������[�v
             _pProg->change(LOCKON001_PROG_LOCK);
         }
         if (pTarget_) {
             if (pTarget_->isActiveInTheTree() || pTarget_->_will_activate_after_flg) {
                 if (ABS(pTarget_->_X-_X) <= 200000 &&
                     ABS(pTarget_->_Y-_Y) <= 200000 &&
                     ABS(pTarget_->_Z-_Z) <= 200000) {
                     locateWith(pTarget_);
                     _pKurokoA->setMvVelo(0);
                     _pKurokoA->_angveloFace[AXIS_Z] = 1000;
                 } else {
                     _pKurokoA->_angveloFace[AXIS_Z] = 3000; //������
                     _pKurokoA->setRzRyMvAngTwd(pTarget_);
                     _pKurokoA->setMvVelo(200000);
                 }
             } else {
                 _pProg->change(LOCKON001_PROG_RELEASE);
             }
         } else {
             _pProg->change(LOCKON001_PROG_RELEASE);
         }
    }

    if (_pProg->get() == LOCKON001_PROG_RELEASE) {
        pTarget_ = nullptr;
        addAlpha(-0.05);
        if (_pScaler->_method[0] == NOSCALE || getAlpha() < 0.0f) {
            _pScaler->setScale(2000);
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pKurokoA->behave();
    _pScaler->behave();

}

void EffectLockon001_Main::processJudgement() {
    EffectLockon001::processJudgement();
}

void EffectLockon001_Main::onInactive() {
    EffectLockon001::onInactive();
}

void EffectLockon001_Main::lockon(GgafDxGeometricActor* prm_pTarget) {
    if (prm_pTarget == nullptr || pTarget_ == prm_pTarget || MyLockonController::lockon_num_ == 0) {
        return;
    }
    pTarget_ = prm_pTarget;

    if (_pProg->get() == LOCKON001_PROG_FIRST_LOCK) {

    } else if (_pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (_pProg->get() == LOCKON001_PROG_RELEASE) {
        _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
        _pScaler->intoTargetScaleLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
        _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);   //��]
        _pSeTx->play3D(0); //���b�N�I��SE
        _pProg->change(LOCKON001_PROG_FIRST_LOCK);
    }

}
void EffectLockon001_Main::releaseLockon() {
    if (isActiveInTheTree()) {
        if (_pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
            _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
            _pScaler->intoTargetScaleLinerUntil(60000, 60);//�X�P�[�����O
            _pKurokoA->setFaceAngVelo(AXIS_Z, _pKurokoA->_angveloFace[AXIS_Z]*-3); //�����t��]
            _pProg->change(LOCKON001_PROG_RELEASE);
        } else if (_pProg->get() == LOCKON001_PROG_LOCK) {
            _pScaler->forceScaleRange(60000, 2000); //�X�P�[�����O�E�͈�
            _pScaler->intoTargetScaleLinerUntil(60000, 60);//�X�P�[�����O
            _pKurokoA->setFaceAngVelo(AXIS_Z, _pKurokoA->_angveloFace[AXIS_Z]*-3); //�����t��]
            _pProg->change(LOCKON001_PROG_RELEASE);
        } else if (_pProg->get() == LOCKON001_PROG_RELEASE) {
            //��������
        }
    }
    pTarget_ = nullptr;
}

EffectLockon001_Main::~EffectLockon001_Main() {
}

