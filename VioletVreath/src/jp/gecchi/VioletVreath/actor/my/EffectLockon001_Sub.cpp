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
        EffectLockon001(prm_name, "8/Lockon001_Sub") {
    _class_name = "EffectLockon001_Sub";
    pEffectLockon001_Main_ = nullptr;
}

void EffectLockon001_Sub::initialize() {
    EffectLockon001::initialize();
    GgafDxUvFlipper* pUvFlipper = getUvFlipper();
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
}

void EffectLockon001_Sub::onActive() {
    EffectLockon001::onActive();
    _TRACE_(getActiveFrame()<<",EffectLockon001_Sub::onActive()、this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    pEffectLockon001_Main_ = (EffectLockon001_Main*)getParent()->getSubFirst();
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    _sx = _sy = _sz = pEffectLockon001_Main_->_sx;
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //右回転
    //getSeTx()->play3D(0); //ロックオンSE
    if (pTarget_) {
        positionAs(pTarget_);
        getProgress()->reset(LOCKON001_PROG_LOCK);
    } else {
        setAlpha(0.00);
        getProgress()->reset(LOCKON001_PROG_RELEASE);
    }
}

void EffectLockon001_Sub::processBehavior() {
    EffectLockon001::processBehavior();
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
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
        //縮小完了後、Mainのビートに合わせる
        _sx = _sy = _sz = pEffectLockon001_Main_->_sx;
        pKuroko->_angvelo_face[AXIS_Z] = pEffectLockon001_Main_->getKuroko()->_angvelo_face[AXIS_Z];
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->_will_activate_after_flg) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    positionAs(pTarget_);
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
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
        pKuroko->setFaceAngVelo(AXIS_Z, 1000);   //右回転
        pProg->change(LOCKON001_PROG_LOCK);
    }

}
void EffectLockon001_Sub::releaseLockon() {

    if (isActiveInTheTree()) {
        GgafDxKuroko* pKuroko = getKuroko();
        GgafProgress* pProg = getProgress();
        if (pProg->get() == LOCKON001_PROG_LOCK) {
            pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angvelo_face[AXIS_Z]*-3); //速く逆回転
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
            //何も無し
        }
    }
    pTarget_ = nullptr;
}

EffectLockon001_Sub::~EffectLockon001_Sub() {
}

