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
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������
    pScaler_->setRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void EffectLockon001_Main::onActive() {
    EffectLockon001::onActive();
//    _TRACE_(FUNC_NAME<<" "<<getActiveFrame()<<", this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    pScaler_->setRange(60000, 2000); //�X�P�[�����O�E�͈�
    setScale(60000); //(6000%)
    pScaler_->transitionLinerUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //��]
    getSeTx()->play3D(0); //���b�N�I��SE

    if (pTarget_) {
        positionAs(pTarget_);
        getProgress()->reset(LOCKON001_PROG_FIRST_LOCK);
    } else {
        setAlpha(0.00);
        getProgress()->reset(LOCKON001_PROG_RELEASE);
    }
}

void EffectLockon001_Main::processBehavior() {
    EffectLockon001::processBehavior();
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK || pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
            addAlpha(0.01);
        }
        if (!pScaler_->isTransitioning()) {
            //�k��������ABeat
            pScaler_->setRange(2000, 4000);
            pScaler_->beat(50, 4, 0, 46, -1); //�������[�v
            pProg->change(LOCKON001_PROG_LOCK);
        }
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->willActivateAfter()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(250) &&
                    ABS(pTarget_->_y-_y) <= PX_C(250) &&
                    ABS(pTarget_->_z-_z) <= PX_C(250)) {
                    positionAs(pTarget_);
                    pKuroko->setMvVelo(0);
                    pKuroko->_angvelo_face[AXIS_Z] = 1000;
                } else {
                    pKuroko->_angvelo_face[AXIS_Z] = 3000; //������
                    pKuroko->setMvAngTwd(pTarget_);
                    pKuroko->setMvVelo(PX_C(250));
                }
            } else {
                pProg->change(LOCKON001_PROG_RELEASE);
            }
        } else {
            pProg->change(LOCKON001_PROG_RELEASE);
        }
    }

    if (pProg->get() == LOCKON001_PROG_RELEASE) {
        pTarget_ = nullptr;
        addAlpha(-0.05);
        if (!pScaler_->isTransitioning() || getAlpha() < 0.0f) {
            setScale(2000);
            inactivate();
        }
    }

    getUvFlipper()->behave();
    pKuroko->behave();
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
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_FIRST_LOCK) {

    } else if (pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
        pScaler_->setRange(60000, 2000); //�X�P�[�����O�E�͈�
        pScaler_->transitionLinerUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
        pKuroko->setFaceAngVelo(AXIS_Z, 1000);   //��]
        getSeTx()->play3D(0); //���b�N�I��SE
        pProg->change(LOCKON001_PROG_FIRST_LOCK);
    }

}
void EffectLockon001_Main::releaseLockon() {
    if (isActiveInTheTree()) {
        GgafDxKuroko* const pKuroko = getKuroko();
        GgafProgress* const pProg = getProgress();
        if (pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
            pScaler_->setRange(60000, 2000); //�X�P�[�����O�E�͈�
            pScaler_->transitionLinerUntil(60000, 60);//�X�P�[�����O
            pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angvelo_face[AXIS_Z]*-3); //�����t��]
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_LOCK) {
            pScaler_->setRange(60000, 2000); //�X�P�[�����O�E�͈�
            pScaler_->transitionLinerUntil(60000, 60);//�X�P�[�����O
            pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angvelo_face[AXIS_Z]*-3); //�����t��]
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
            //��������
        }
    }
    pTarget_ = nullptr;
}

EffectLockon001_Main::~EffectLockon001_Main() {
    GGAF_DELETE(pScaler_);
}

