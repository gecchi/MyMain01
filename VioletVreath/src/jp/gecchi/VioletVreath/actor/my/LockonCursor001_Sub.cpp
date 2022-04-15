#include "LockonCursor001_Sub.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
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
    pUvFlipper->setFlipPtnRange(0, 3);   //Ajออ๐O`PT
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //Aj
}

void LockonCursor001_Sub::onActive() {
    LockonCursor001::onActive();
//    _TRACE_(FUNC_NAME<<" "<<getActiveFrame()<<", this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    pLockonCursor001_Main_ = (LockonCursor001_Main*)getParent()->getChildFirst();
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    _sx = _sy = _sz = pLockonCursor001_Main_->_sx;
    getVecVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //E๑]
    //getSeTransmitter()->play3D(0); //bNISE
    if (pTarget_) {
        setPositionAt(pTarget_);
        getProgress()->reset(LOCKON001_PROG_LOCK);
    } else {
        setAlpha(0.00);
        getProgress()->reset(LOCKON001_PROG_RELEASE);
    }
}

void LockonCursor001_Sub::processBehavior() {
    LockonCursor001::processBehavior();
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK) {
        if (getAlpha() < 0.7) {
            if (pLockonCursor001_Main_->getProgress()->get() == LOCKON001_PROG_LOCK) {
                addAlpha(0.07);
            } else if (pLockonCursor001_Main_->getProgress()->get() == LOCKON001_PROG_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
        }
        //kฌฎนใAMainฬr[gษํน้
        _sx = _sy = _sz = pLockonCursor001_Main_->_sx;
        pVecVehicle->_angvelo_face[AXIS_Z] = pLockonCursor001_Main_->getVecVehicle()->_angvelo_face[AXIS_Z];
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->isActivateScheduled()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    setPositionAt(pTarget_);
                    pVecVehicle->setMvVelo(0);
                } else {
                    pVecVehicle->setMvAngTwd(pTarget_);
                    pVecVehicle->setMvVelo(PX_C(200));
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
        _sx = _sy = _sz = pLockonCursor001_Main_->_sx;
        pVecVehicle->_angvelo_face[AXIS_Z] = pLockonCursor001_Main_->getVecVehicle()->_angvelo_face[AXIS_Z];
        if ( getAlpha() < 0.0f) {
            inactivate();
        }
    }

    getUvFlipper()->behave();
    pVecVehicle->behave();
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
    GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
        pVecVehicle->setFaceAngVelo(AXIS_Z, 1000);   //E๑]
        pProg->change(LOCKON001_PROG_LOCK);
    }

}
void LockonCursor001_Sub::releaseLockon() {

    if (isActiveInTheTree()) {
        GgafDx::VecVehicle* const pVecVehicle = getVecVehicle();
        GgafCore::Progress* const pProg = getProgress();
        if (pProg->get() == LOCKON001_PROG_LOCK) {
            pVecVehicle->setFaceAngVelo(AXIS_Z, pVecVehicle->_angvelo_face[AXIS_Z]*-3); //ฌญt๑]
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
            //ฝเณต
        }
    }
    pTarget_ = nullptr;
}

LockonCursor001_Sub::~LockonCursor001_Sub() {
}

