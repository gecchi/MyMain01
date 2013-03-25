#include "stdafx.h"
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
    _pUvFlipper->setFlipPtnRange(0, 3);   //アニメ範囲を０～１５
    _pUvFlipper->exec(FLIP_ORDER_LOOP, 5); //アニメ順序
}

void EffectLockon001_Sub::onActive() {
    EffectLockon001::onActive();
    _TRACE_(getActivePartFrame()<<",EffectLockon001_Sub::onActive()、this="<<getName()<<"("<<this<<") pTarget_="<<pTarget_);
    pEffectLockon001_Main_ = (EffectLockon001_Main*)getParent()->getSubFirst();
    _pUvFlipper->setActivePtnToTop();
    setAlpha(0.01);
    _SX = _SY = _SZ = pEffectLockon001_Main_->_SX;
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);        //右回転
    //_pSeTx->play3D(0); //ロックオンSE
    if (pTarget_) {
        locateWith(pTarget_);
        _pProg->reset(LOCKON001_PROG_LOCK);
    } else {
        setAlpha(0.00);
        _pProg->reset(LOCKON001_PROG_RELEASE);
    }
}

void EffectLockon001_Sub::processBehavior() {
    EffectLockon001::processBehavior();

    if (_pProg->get() == LOCKON001_PROG_LOCK) {
        if (getAlpha() < 0.7) {
            if (pEffectLockon001_Main_->_pProg->get() == LOCKON001_PROG_LOCK) {
                addAlpha(0.07);
            } else if (pEffectLockon001_Main_->_pProg->get() == LOCKON001_PROG_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
         }
         //縮小完了後、Mainのビートに合わせる
         _SX = _SY = _SZ = pEffectLockon001_Main_->_SX;
         _pKurokoA->_angveloFace[AXIS_Z] = pEffectLockon001_Main_->_pKurokoA->_angveloFace[AXIS_Z];
         if (pTarget_) {
             if (pTarget_->isActiveInTheTree() || pTarget_->_will_activate_after_flg) {
                 if (ABS(pTarget_->_X-_X) <= PX_C(200) &&
                     ABS(pTarget_->_Y-_Y) <= PX_C(200) &&
                     ABS(pTarget_->_Z-_Z) <= PX_C(200)) {
                     locateWith(pTarget_);
                     _pKurokoA->setMvVelo(0);
                 } else {
                     _pKurokoA->setMvAngTwd(pTarget_);
                     _pKurokoA->setMvVelo(PX_C(200));
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
        _SX = _SY = _SZ = pEffectLockon001_Main_->_SX;
        _pKurokoA->_angveloFace[AXIS_Z] = pEffectLockon001_Main_->_pKurokoA->_angveloFace[AXIS_Z];
        if ( getAlpha() < 0.0f) {
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pKurokoA->behave();
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

    if (_pProg->get() == LOCKON001_PROG_LOCK) {
    } else if (_pProg->get() == LOCKON001_PROG_RELEASE) {
        _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);   //右回転
        _pProg->change(LOCKON001_PROG_LOCK);
    }

}
void EffectLockon001_Sub::releaseLockon() {

    if (isActiveInTheTree()) {
        if (_pProg->get() == LOCKON001_PROG_LOCK) {
            _pKurokoA->setFaceAngVelo(AXIS_Z, _pKurokoA->_angveloFace[AXIS_Z]*-3); //速く逆回転
            _pProg->change(LOCKON001_PROG_RELEASE);
        } else if (_pProg->get() == LOCKON001_PROG_RELEASE) {
            //何も無し
        }
    }
    pTarget_ = nullptr;
}

EffectLockon001_Sub::~EffectLockon001_Sub() {
}

