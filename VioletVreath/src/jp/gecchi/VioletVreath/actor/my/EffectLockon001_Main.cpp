#include "stdafx.h"
#include "EffectLockon001_Main.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockon001_Main::EffectLockon001_Main(const char* prm_name) :
        EffectLockon001(prm_name, "8/Lockon001") {
    _class_name = "EffectLockon001_Main";
    pScaler_ = NEW GgafDxScaler(this);
}

void EffectLockon001_Main::initialize() {
    EffectLockon001::initialize();
    _pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������
    pScaler_->forceRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void EffectLockon001_Main::onActive() {
    EffectLockon001::onActive();
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.01);
    pScaler_->forceRange(60000, 2000); //�X�P�[�����O�E�͈�
    setScale(60000); //(6000%)
    pScaler_->transitionLinerUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    _pKuroko->setFaceAngVelo(AXIS_Z, 1000);        //��]
    _pSeTx->play3D(0); //���b�N�I��SE

    if (pTarget_) {
        positionAs(pTarget_);
        _pProg->reset(LOCKON001_PROG_FIRST_LOCK);
    } else {
        setAlpha(0.00);
        _pProg->reset(LOCKON001_PROG_RELEASE);
    }
}

void EffectLockon001_Main::processBehavior() {
    EffectLockon001::processBehavior();

    if (_pProg->get() == LOCKON001_PROG_LOCK || _pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
            addAlpha(0.01);
        }
        if (!pScaler_->isTransitioning()) {
            //�k��������ABeat
            pScaler_->forceRange(2000, 4000);
            pScaler_->beat(50, 4, 0, 46, -1); //�������[�v
            _pProg->change(LOCKON001_PROG_LOCK);
        }
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->_will_activate_after_flg) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    positionAs(pTarget_);
                    _pKuroko->setMvVelo(0);
                    _pKuroko->_angveloFace[AXIS_Z] = 1000;
                } else {
                    _pKuroko->_angveloFace[AXIS_Z] = 3000; //������
                    _pKuroko->setMvAngTwd(pTarget_);
                    _pKuroko->setMvVelo(PX_C(200));
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
        if (!pScaler_->isTransitioning() || getAlpha() < 0.0f) {
            setScale(2000);
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pKuroko->behave();
    pScaler_->behave();

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
        pScaler_->forceRange(60000, 2000); //�X�P�[�����O�E�͈�
        pScaler_->transitionLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
        _pKuroko->setFaceAngVelo(AXIS_Z, 1000);   //��]
        _pSeTx->play3D(0); //���b�N�I��SE
        _pProg->change(LOCKON001_PROG_FIRST_LOCK);
    }

}
void EffectLockon001_Main::releaseLockon() {
    if (isActiveInTheTree()) {
        if (_pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
            pScaler_->forceRange(60000, 2000); //�X�P�[�����O�E�͈�
            pScaler_->transitionLinerUntil(60000, 60);//�X�P�[�����O
            _pKuroko->setFaceAngVelo(AXIS_Z, _pKuroko->_angveloFace[AXIS_Z]*-3); //�����t��]
            _pProg->change(LOCKON001_PROG_RELEASE);
        } else if (_pProg->get() == LOCKON001_PROG_LOCK) {
            pScaler_->forceRange(60000, 2000); //�X�P�[�����O�E�͈�
            pScaler_->transitionLinerUntil(60000, 60);//�X�P�[�����O
            _pKuroko->setFaceAngVelo(AXIS_Z, _pKuroko->_angveloFace[AXIS_Z]*-3); //�����t��]
            _pProg->change(LOCKON001_PROG_RELEASE);
        } else if (_pProg->get() == LOCKON001_PROG_RELEASE) {
            //��������
        }
    }
    pTarget_ = nullptr;
}

EffectLockon001_Main::~EffectLockon001_Main() {
    GGAF_DELETE(pScaler_);
}

