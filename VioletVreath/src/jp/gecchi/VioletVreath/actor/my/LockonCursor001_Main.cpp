#include "LockonCursor001_Main.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"



using namespace GgafLib;
using namespace VioletVreath;

LockonCursor001_Main::LockonCursor001_Main(const char* prm_name) :
        LockonCursor001(prm_name, "10,Lockon001") {
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
//    _TRACE_(FUNC_NAME<<" "<<getActiveFrame()<<", this="<<NODE_INFO<<" pTarget_="<<pTarget_);
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
    getUvFlipper()->setActivePtnToTop();
    setAlpha(0.01);
    getScaler()->setRange(60000, 2000); //スケーリング・範囲
    setScale(60000); //(6000%)
    getScaler()->transitionLinearUntil(2000, 25);//スケーリング・25F費やして2000(200%)に縮小
    getKuroko()->setFaceAngVelo(AXIS_Z, 1000);        //回転
    getSeTransmitter()->play3D(0); //ロックオンSE

    if (pTarget_) {
        setPositionAt(pTarget_);
        getProgress()->reset(LOCKON001_PROG_FIRST_LOCK);
    } else {
        setAlpha(0.00);
        getProgress()->reset(LOCKON001_PROG_RELEASE);
    }
}

void LockonCursor001_Main::processBehavior() {
    LockonCursor001::processBehavior();
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_LOCK || pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
        if (getAlpha() < 1.0) {
            addAlpha(0.01);
        }
        if (!pScaler->isTransitioning()) {
            //縮小完了後、Beat
            pScaler->setRange(2000, 4000);
            pScaler->beat(50, 4, 0, 46, -1); //無限ループ
            pProg->change(LOCKON001_PROG_LOCK);
        }
        if (pTarget_) {
            if (pTarget_->isActiveInTheTree() || pTarget_->willActivateAfter()) {
                if (ABS(pTarget_->_x-_x) <= PX_C(250) &&
                    ABS(pTarget_->_y-_y) <= PX_C(250) &&
                    ABS(pTarget_->_z-_z) <= PX_C(250)) {
                    setPositionAt(pTarget_);
                    pKuroko->setMvVelo(0);
                    pKuroko->_angvelo_face[AXIS_Z] = 1000;
                } else {
                    pKuroko->_angvelo_face[AXIS_Z] = 3000; //速周り
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
        if (!pScaler->isTransitioning() || getAlpha() < 0.0f) {
            setScale(2000);
            inactivate();
        }
    }

    getUvFlipper()->behave();
    pKuroko->behave();
    pScaler->behave();

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
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafDx::Scaler* const pScaler = getScaler();
    GgafCore::Progress* const pProg = getProgress();
    if (pProg->get() == LOCKON001_PROG_FIRST_LOCK) {

    } else if (pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
        pScaler->setRange(60000, 2000); //スケーリング・範囲
        pScaler->transitionLinearUntil(2000, 25);//スケーリング・20F費やして2000(200%)に縮小
        pKuroko->setFaceAngVelo(AXIS_Z, 1000);   //回転
        getSeTransmitter()->play3D(0); //ロックオンSE
        pProg->change(LOCKON001_PROG_FIRST_LOCK);
    }

}
void LockonCursor001_Main::releaseLockon() {
    if (isActiveInTheTree()) {
        GgafDx::Kuroko* const pKuroko = getKuroko();
        GgafDx::Scaler* const pScaler = getScaler();
        GgafCore::Progress* const pProg = getProgress();
        if (pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
            pScaler->setRange(60000, 2000); //スケーリング・範囲
            pScaler->transitionLinearUntil(60000, 60);//スケーリング
            pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angvelo_face[AXIS_Z]*-3); //速く逆回転
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_LOCK) {
            pScaler->setRange(60000, 2000); //スケーリング・範囲
            pScaler->transitionLinearUntil(60000, 60);//スケーリング
            pKuroko->setFaceAngVelo(AXIS_Z, pKuroko->_angvelo_face[AXIS_Z]*-3); //速く逆回転
            pProg->change(LOCKON001_PROG_RELEASE);
        } else if (pProg->get() == LOCKON001_PROG_RELEASE) {
            //何も無し
        }
    }
    pTarget_ = nullptr;
}

LockonCursor001_Main::~LockonCursor001_Main() {
}

