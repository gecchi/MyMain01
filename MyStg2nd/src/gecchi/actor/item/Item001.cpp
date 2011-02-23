#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

Item001::Item001(const char* prm_name)
               : DefaultMeshSetActor(prm_name, "vic2") {
    _class_name = "Item001";
    setZEnable(true);        //Zバッファは考慮有り
    setZWriteEnable(true);  //Zバッファは書き込み有り
}

void Item001::initialize() {
//    _pUvFlipper->forcePtnNoRange(0, 63);
}

void Item001::onReset() {
    setHitAble(true);
    _pKuroko->setFaceAngVelo(AXIS_X, 3*1000);
}

void Item001::onActive() {
}

void Item001::processBehavior() {
    _pKuroko->behave();
}

void Item001::processJudgement() {
}

void Item001::onInactive() {
}

Item001::~Item001() {
}
