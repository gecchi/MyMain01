#include "LockonCursor001_Main.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"


using namespace GgafLib;
using namespace VioletVreath;

LockonCursor001_Main::LockonCursor001_Main(const char* prm_name) :
        LockonCursor001(prm_name, "Lockon001") {
    _class_name = "LockonCursor001_Main";
}

void LockonCursor001_Main::initialize() {
    LockonCursor001::initialize();
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //�A�j���͈͂��O�`�P�T
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //�A�j������
    getScaler()->setRange(60000, 2000); //�X�P�[�����O�E�͈�
}

void LockonCursor001_Main::onActive() {
    LockonCursor001::onActive();
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    getScaler()->setRange(60000, 2000); //�X�P�[�����O�E�͈�
    setScale(60000); //(6000%)
    getScaler()->transitionLinearUntil(2000, 25);//�X�P�[�����O�E25F��₵��2000(200%)�ɏk��
    getLocoVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //��]
    getSeXmtr()->play3D(0); //���b�N�I��SE

    if (pTarget_) {
        setPositionAt(pTarget_);
        getPhase()->reset(LOCKON001_PHASE_FIRST_LOCK);
    } else {
        setAlpha(0.00);
        getPhase()->reset(LOCKON001_PHASE_RELEASE);
    }

    //_TRACE_(FUNC_NAME<<" ! "<<getActiveFrame()<<", Alpha="<<getAlpha()<<" _sx="<<_sx<<" this="<<NODE_INFO<<" pTarget_="<<pTarget_);

}

void LockonCursor001_Main::processBehavior() {
    //_TRACE_(FUNC_NAME<<" B "<<getActiveFrame()<<", Alpha="<<getAlpha()<<" _sx="<<_sx<<" this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK || pPhase->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
            addAlpha(0.05);
        }
        if (!pScaler->isTransitioning()) {
            //�k��������ABeat
            pScaler->setRange(2000, 4000);
            pScaler->beat(50, 4, 0, 46, -1); //�������[�v
            pPhase->change(LOCKON001_PHASE_LOCK);
        }
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->isActivateScheduled()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    setPositionAt(pTarget_);
                    pLocoVehicle->setMvVelo(0);
                    pLocoVehicle->_angvelo_face[AXIS_Z] = 1000;
                } else {
                    pLocoVehicle->_angvelo_face[AXIS_Z] = 3000; //������
                    pLocoVehicle->setMvAngTwd(pTarget_);
                    pLocoVehicle->setMvVelo(PX_C(200));
                }
            } else {
                pPhase->change(LOCKON001_PHASE_RELEASE);
            }
        } else {
            pPhase->change(LOCKON001_PHASE_RELEASE);
        }
    }

    if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
        pTarget_ = nullptr;
        addAlpha(-0.05);
        if (!pScaler->isTransitioning() || getAlpha() < 0.0f) {
            setScale(2000);
            inactivate();
        }
    }

    getUvFlipper()->behave();
    pLocoVehicle->behave();
    pScaler->behave();
    LockonCursor001::processBehavior();
    //_TRACE_(FUNC_NAME<<" E "<<getActiveFrame()<<", Alpha="<<getAlpha()<<" _sx="<<_sx<<" this="<<NODE_INFO<<" pTarget_="<<pTarget_);
}

void LockonCursor001_Main::processJudgement() {
    LockonCursor001::processJudgement();
}

void LockonCursor001_Main::onInactive() {
    LockonCursor001::onInactive();
}

void LockonCursor001_Main::lockon(GgafDx::GeometricActor* prm_pTarget) {
    if (prm_pTarget == nullptr || pTarget_ == prm_pTarget || MyLockonController::lockon_num_ == 0) {
        return;
    }
    pTarget_ = prm_pTarget;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {

    } else if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
    } else if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
        pScaler->setRange(60000, 2000); //�X�P�[�����O�E�͈�
        pScaler->transitionLinearUntil(2000, 25);//�X�P�[�����O�E20F��₵��2000(200%)�ɏk��
        pLocoVehicle->setFaceAngVelo(AXIS_Z, 1000);   //��]
        getSeXmtr()->play3D(0); //���b�N�I��SE
        pPhase->change(LOCKON001_PHASE_FIRST_LOCK);
    }

}
void LockonCursor001_Main::releaseLockon() {
    if (isActiveInTheTree()) {
        GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
        GgafDx::Scaler* const pScaler = getScaler();
        GgafCore::Phase* pPhase = getPhase();
        if (pPhase->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {
            pScaler->setRange(60000, 2000); //�X�P�[�����O�E�͈�
            pScaler->transitionLinearUntil(60000, 60);//�X�P�[�����O
            pLocoVehicle->setFaceAngVelo(AXIS_Z, pLocoVehicle->_angvelo_face[AXIS_Z]*-3); //�����t��]
            pPhase->change(LOCKON001_PHASE_RELEASE);
        } else if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
            pScaler->setRange(60000, 2000); //�X�P�[�����O�E�͈�
            pScaler->transitionLinearUntil(60000, 60);//�X�P�[�����O
            pLocoVehicle->setFaceAngVelo(AXIS_Z, pLocoVehicle->_angvelo_face[AXIS_Z]*-3); //�����t��]
            pPhase->change(LOCKON001_PHASE_RELEASE);
        } else if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
            //��������
        }
    }
    pTarget_ = nullptr;
}

LockonCursor001_Main::~LockonCursor001_Main() {
}

