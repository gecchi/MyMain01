#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Item001::Item001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "vic2", NULL) {
    _class_name = "Item001";
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}

void Item001::initialize() {
//    _pUvFlipper->forcePtnNoRange(0, 63);
}

void Item001::onReset() {
}

void Item001::onActive() {
}

void Item001::processBehavior() {
    _pKurokoA->behave();
}

void Item001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Item001::onInactive() {
}

void Item001::onHit(GgafActor* prm_pOtherActor) {
    GgafDx9GeometricActor* pOther = (GgafDx9GeometricActor*)prm_pOtherActor;
    //ここにヒットエフェクト


    if (pOther->getKind() & KIND_MY_BODY)  {
        //P_MYSHIP_SCENE->_pEnagyBar->_value += 10;
        _pSeTransmitter->playImmediately(0);
        setHitAble(false);
        EffectExplosion001* pExplo001 = (EffectExplosion001*)P_COMMON_SCENE->_pDP_EffectExplosion001->dispatch();
        if (pExplo001) {
            pExplo001->locateAs(this);
        }
        sayonara();
    }


}

Item001::~Item001() {
}
