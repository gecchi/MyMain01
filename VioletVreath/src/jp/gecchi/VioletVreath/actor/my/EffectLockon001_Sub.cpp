#include "EffectLockon001_Sub.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "EffectLockon001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EffectLockon001_Sub::EffectLockon001_Sub(const char* prm_name) :
        EffectLockon001(prm_name, "10/Lockon001_Sub") {
    _class_name = "EffectLockon001_Sub";
    pEffectLockon001_Main_ = nullptr;
}

void EffectLockon001_Sub::initialize() {
    EffectLockon001::initialize();
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //ÉAÉjÉÅîÕàÕÇÇOÅ`ÇPÇT
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //ÉAÉjÉÅèáèò
}

void EffectLockon001_Sub::onActive() {
    EffectLockon001::onActive();
//    _TRACE_(FUNC_NAME<<" "<<getActiveFrame()<<", this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    pEffectLockon001_Main_ = (EffectLockon001_Main*)getParent()->getSubFirst();
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    _sx = _sy = _sz = pEffectLockon001_Main_->_sx;
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //âEâÒì]
    //getSeTransmitter()->play3D(0); //ÉçÉbÉNÉIÉìSE
    if (pTarget_) {
        placeAs(pTarget_);
        getProgress()->reset(LOCKON001_PROG_LOCK);
    } else {
        setAlpha(0.00);
        getProgress()->reset(LOCKON001_PROG_RELEASE);
    }
}

void EffectLockon001_Sub::processBehavior() {
    EffectLockon001::processBehavior();
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK) {
        if (getAlpha() < 0.7) {
            if (pEffectLockon001_Main_->getProgress()->get() == LOCKON001_PROG_LOCK) {
                addAlpha(0.07);
            } else if (pEffectLockon001_Main_->getProgress()->get() == LOCKON001_PROG_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
        }
        //èkè¨äÆóπå„ÅAMainÇÃÉrÅ[ÉgÇ…çáÇÌÇπÇÈ
        _sx = _sy = _sz = pEffectLockon001_Main_->_sx;
        pKuroko->_angvelo_face[AXIS_Z] = pEffectLockon001_Main_->getKuroko()->_angvelo_face[AXIS_Z];
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->willActivateAfter()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    placeAs(pTarget_);
                    pKuroko->setMvVelo(0);
                } else {
                    pKuroko->setMvAngTwd(pTarget_);
                    pKuroko->setMvVelo(PX_C(200));
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
        _sx = _sy = _sz = pEffectLockon001_Main_->_sx;
        pKuroko->_angvelo_face[AXIS_Z] = pEffectLockon001_Main_->getKuroko()->_angvelo_face[AXIS_Z];
        if ( getAlpha() < 0.0f) {
            inactivate();
        }
    }

    getUvFlipper()->behave();
    pKuroko->behave();
}

void EffectLockon001_Sub::processJudgement() {
    EffectLockon001::processJudgement();
}

void EffectLockon001_Sub::onInactive() {
    EffectLockon001::onInactive();
}

void EffectLockon001_Sub::lockon(GgafDxGeometricActor* prm_pTarget) {

    if (prm_pTarget == nullptr || pTarget_ == prm_pTarget || MyLockonController::lockon_num_ == 0) {
        return;
    }
    pTarget_ = prm_pTarget;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
        pKuroko->setFaceAngVelo(AXIS_Z, 1000);   //âEâÒì]
        pProg->change(LOCKON001_PROG_LOCK);
    }

}
void EffectLockon001_Sub::releaseLockon() {

    if (isActiveInTheTree()) {
        GgafDxKuroko* const pKuroko = getKuroko();
        GgafProgress* const pProg = getProgress();
        if (pProg->get() == LOCKON001_PROG_LOCK) {
            pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angvelo_face[AXIS_Z]*-3); //ë¨Ç≠ãtâÒì]
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
            //âΩÇ‡ñ≥Çµ
        }
    }
    pTarget_ = nullptr;
}

EffectLockon001_Sub::~EffectLockon001_Sub() {
}

