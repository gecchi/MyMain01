#include "LockonCursor001_Sub.h"

#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"



using namespace GgafLib;
using namespace VioletVreath;

LockonCursor001_Sub::LockonCursor001_Sub(const char* prm_name) :
        LockonCursor001(prm_name, "Lockon001_Sub") {
    _class_name = "LockonCursor001_Sub";
    pLockonCursor001_Main_ = nullptr;
}

void LockonCursor001_Sub::initialize() {
    LockonCursor001::initialize();
    GgafDx::UvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //ÉAÉjÉÅîÕàÕÇÇOÅ`ÇPÇT
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //ÉAÉjÉÅèáèò
}

void LockonCursor001_Sub::onActive() {
    LockonCursor001::onActive();
//    _TRACE_(FUNC_NAME<<" "<<getActiveFrame()<<", this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    pLockonCursor001_Main_ = (LockonCursor001_Main*)getParent()->getChildFirst();
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    _sx = _sy = _sz = pLockonCursor001_Main_->_sx;
    getLocoVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //âEâÒì]
    //getSeTransmitter()->play3D(0); //ÉçÉbÉNÉIÉìSE
    if (pTarget_) {
        setPositionAt(pTarget_);
        getPhase()->reset(LOCKON001_PHASE_LOCK);
    } else {
        setAlpha(0.00);
        getPhase()->reset(LOCKON001_PHASE_RELEASE);
    }
}

void LockonCursor001_Sub::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
        if (getAlpha() < 0.7) {
            if (pLockonCursor001_Main_->getPhase()->getCurrent() == LOCKON001_PHASE_LOCK) {
                addAlpha(0.07);
            } else if (pLockonCursor001_Main_->getPhase()->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
        }
        //èkè¨äÆóπå„ÅAMainÇÃÉrÅ[ÉgÇ…çáÇÌÇπÇÈ
        _sx = _sy = _sz = pLockonCursor001_Main_->_sx;
        pLocoVehicle->_angvelo_face[AXIS_Z] = pLockonCursor001_Main_->getLocoVehicle()->_angvelo_face[AXIS_Z];
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->isActivateScheduled()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    setPositionAt(pTarget_);
                    pLocoVehicle->setMvVelo(0);
                } else {
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
        _sx = _sy = _sz = pLockonCursor001_Main_->_sx;
        pLocoVehicle->_angvelo_face[AXIS_Z] = pLockonCursor001_Main_->getLocoVehicle()->_angvelo_face[AXIS_Z];
        if ( getAlpha() < 0.0f) {
            inactivate();
        }
    }

    getUvFlipper()->behave();
    pLocoVehicle->behave();
    LockonCursor001::processBehavior();
}

void LockonCursor001_Sub::processJudgement() {
    LockonCursor001::processJudgement();
}

void LockonCursor001_Sub::onInactive() {
    LockonCursor001::onInactive();
}

void LockonCursor001_Sub::lockon(GgafDx::GeometricActor* prm_pTarget) {

    if (prm_pTarget == nullptr || pTarget_ == prm_pTarget || MyLockonController::lockon_num_ == 0) {
        return;
    }
    pTarget_ = prm_pTarget;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
    } else if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
        pLocoVehicle->setFaceAngVelo(AXIS_Z, 1000);   //âEâÒì]
        pPhase->change(LOCKON001_PHASE_LOCK);
    }

}
void LockonCursor001_Sub::releaseLockon() {

    if (isActiveInTheTree()) {
        GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
        GgafCore::Phase* pPhase = getPhase();
        if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
            pLocoVehicle->setFaceAngVelo(AXIS_Z, pLocoVehicle->_angvelo_face[AXIS_Z]*-3); //ë¨Ç≠ãtâÒì]
            pPhase->change(LOCKON001_PHASE_RELEASE);
        } else if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
            //âΩÇ‡ñ≥Çµ
        }
    }
    pTarget_ = nullptr;
}

LockonCursor001_Sub::~LockonCursor001_Sub() {
}

