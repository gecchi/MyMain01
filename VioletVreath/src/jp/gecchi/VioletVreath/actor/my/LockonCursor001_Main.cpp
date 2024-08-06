#include "LockonCursor001_Main.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
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
    pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
    getScaler()->setRange(60000, 2000); //スケーリング・範囲
}

void LockonCursor001_Main::onActive() {
    LockonCursor001::onActive();
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    getScaler()->setRange(60000, 2000); //スケーリング・範囲
    setScale(60000); //(6000%)
    getScaler()->transitionLinearUntil(2000, 25);//スケーリング・25F費やして2000(200%)に縮小
    getLocusVehicle()->setFaceAngVelo(AXIS_Z, 1000);        //回転
    getSeXmtr()->play3D(0); //ロックオンSE

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
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK || pPhase->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
            addAlpha(0.05);
        }
        if (!pScaler->isTransitioning()) {
            //縮小完了後、Beat
            pScaler->setRange(2000, 4000);
            pScaler->beat(50, 4, 0, 46, -1); //無限ループ
            pPhase->change(LOCKON001_PHASE_LOCK);
        }
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->isActivateScheduled()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(200) &&
                    ABS(pTarget_->_y-_y) <= PX_C(200) &&
                    ABS(pTarget_->_z-_z) <= PX_C(200)) {
                    setPositionAt(pTarget_);
                    pLocusVehicle->setMvVelo(0);
                    pLocusVehicle->_angvelo_face[AXIS_Z] = 1000;
                } else {
                    pLocusVehicle->_angvelo_face[AXIS_Z] = 3000; //速周り
                    pLocusVehicle->setMvAngTwd(pTarget_);
                    pLocusVehicle->setMvVelo(PX_C(200));
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
    pLocusVehicle->behave();
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
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Phase* pPhase = getPhase();
    if (pPhase->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {

    } else if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
    } else if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
        pScaler->setRange(60000, 2000); //スケーリング・範囲
        pScaler->transitionLinearUntil(2000, 25);//スケーリング・20F費やして2000(200%)に縮小
        pLocusVehicle->setFaceAngVelo(AXIS_Z, 1000);   //回転
        getSeXmtr()->play3D(0); //ロックオンSE
        pPhase->change(LOCKON001_PHASE_FIRST_LOCK);
    }

}
void LockonCursor001_Main::releaseLockon() {
    if (isActiveInTheTree()) {
        GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
        GgafDx::Scaler* const pScaler = getScaler();
        GgafCore::Phase* pPhase = getPhase();
        if (pPhase->getCurrent() == LOCKON001_PHASE_FIRST_LOCK) {
            pScaler->setRange(60000, 2000); //スケーリング・範囲
            pScaler->transitionLinearUntil(60000, 60);//スケーリング
            pLocusVehicle->setFaceAngVelo(AXIS_Z, pLocusVehicle->_angvelo_face[AXIS_Z]*-3); //速く逆回転
            pPhase->change(LOCKON001_PHASE_RELEASE);
        } else if (pPhase->getCurrent() == LOCKON001_PHASE_LOCK) {
            pScaler->setRange(60000, 2000); //スケーリング・範囲
            pScaler->transitionLinearUntil(60000, 60);//スケーリング
            pLocusVehicle->setFaceAngVelo(AXIS_Z, pLocusVehicle->_angvelo_face[AXIS_Z]*-3); //速く逆回転
            pPhase->change(LOCKON001_PHASE_RELEASE);
        } else if (pPhase->getCurrent() == LOCKON001_PHASE_RELEASE) {
            //何も無し
        }
    }
    pTarget_ = nullptr;
}

LockonCursor001_Main::~LockonCursor001_Main() {
}

