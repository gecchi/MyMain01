#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

EffectLockon001_Sub::EffectLockon001_Sub(const char* prm_name) : EffectLockon001(prm_name, "8/Lockon001_Sub") {
    _class_name = "EffectLockon001_Sub";
    _pPrg->change(EffectLockon001_SCENE_PROG_LOCK);
}

void EffectLockon001_Sub::initialize() {
    EffectLockon001::initialize();
    _pUvFlipper->forcePtnNoRange(0, 3);   //アニメ範囲を０～１５
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 5); //アニメ順序
}

void EffectLockon001_Sub::onActive() {
    EffectLockon001::onActive();
    _pEffectLockon001_Main = (EffectLockon001_Main*)getParent()->getSubFirst();
    _pUvFlipper->setActivePtnNoToTop();
    setAlpha(0.01);
    _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
    _pMvNavigator->setFaceAngVelo(AXIS_Z, 1000);        //右回転
    //_pSeTransmitter->play3D(0); //ロックオンSE
    locateAs(_pTarget);

    _pPrg->change(EffectLockon001_SCENE_PROG_LOCK);
}

void EffectLockon001_Sub::processBehavior() {
    EffectLockon001::processBehavior();

    if (_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
        if (getAlpha() < 0.7) {
            if (_pEffectLockon001_Main->_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
                addAlpha(0.07);
            } else if (_pEffectLockon001_Main->_pPrg->get() == EffectLockon001_SCENE_PROG_FIRST_LOCK) {
                addAlpha(0.01);
            } else {
                addAlpha(0.01);
            }
         }
         //縮小完了後、Mainのビートに合わせる
         _SX = _SY = _SZ = _pEffectLockon001_Main->_SX;
         _pMvNavigator->_angveloFace[AXIS_Z] = _pEffectLockon001_Main->_pMvNavigator->_angveloFace[AXIS_Z];
         if (_pTarget) {
             if (_pTarget->isActiveActor() || _pTarget->_will_activate_after_flg) {
                 if (abs(_pTarget->_X-_X) <= 200000 &&
                     abs(_pTarget->_Y-_Y) <= 200000 &&
                     abs(_pTarget->_Z-_Z) <= 200000) {
                     locateAs(_pTarget);
                     _pMvNavigator->setMvVelo(0);
                 } else {
                     _pMvNavigator->setMvAng(_pTarget);
                     _pMvNavigator->setMvVelo(200000);
                 }
             } else {
                 _pPrg->change(EffectLockon001_SCENE_PROG_RELEASE);
             }
         } else {
             _pPrg->change(EffectLockon001_SCENE_PROG_RELEASE);
         }
    }

    if (_pPrg->get() == EffectLockon001_SCENE_PROG_RELEASE) {
        addAlpha(-0.05);
        if (getAlpha() <= 0.0) {
            inactivate();
        }
    }

    _pUvFlipper->behave();
    _pMvNavigator->behave();
    _pScaler->behave();
}

void EffectLockon001_Sub::processJudgement() {
    EffectLockon001::processJudgement();
}

void EffectLockon001_Sub::onInactive() {
    EffectLockon001::onInactive();
}

void EffectLockon001_Sub::lockon(GgafDx9GeometricActor* prm_pTarget) {
    if (prm_pTarget == NULL || _pTarget == prm_pTarget) {
        return;
    }
    _pTarget = prm_pTarget;

    if (_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
    } else if (_pPrg->get() == EffectLockon001_SCENE_PROG_RELEASE) {
        _pMvNavigator->setFaceAngVelo(AXIS_Z, 1000);   //右回転
        _pPrg->change(EffectLockon001_SCENE_PROG_LOCK);
    }

}
void EffectLockon001_Sub::releaseLockon() {
    if (isActiveActor()) {
        if (_pPrg->get() == EffectLockon001_SCENE_PROG_LOCK) {
            _pScaler->forceScaleRange(60000, 2000); //スケーリング・範囲
            _pScaler->intoTargetScaleLinerUntil(60000, 60);//スケーリング
            _pMvNavigator->setFaceAngVelo(AXIS_Z, _pMvNavigator->_angveloFace[AXIS_Z]*-3); //速く逆回転
            _pPrg->change(EffectLockon001_SCENE_PROG_RELEASE);
        } else if (_pPrg->get() == EffectLockon001_SCENE_PROG_RELEASE) {
            //何も無し
        }
    }
    _pTarget = NULL;
}

EffectLockon001_Sub::~EffectLockon001_Sub() {
}

