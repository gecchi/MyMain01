#include "stdafx.h"
#include "MyMagicEnergyCore.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "MyMagicEnergy.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


#define MAX_SCALSE_MagicEnergyCore (R_SC(2))
MyMagicEnergyCore::MyMagicEnergyCore(const char* prm_name) :
        DefaultMeshActor(prm_name, "MagicEnergyCore", STATUS(MyMagicEnergyCore)) {
    _class_name = "MyMagicEnergyCore";

    MyMagicEnergy* p = NEW MyMagicEnergy("MyMagicEnergy", this);
    addSubLast(p);
}

void MyMagicEnergyCore::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergyCore::initialize() {
    setHitAble(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, (P_MYSHIP->mp_ * (1.0 / MY_SHIP_MAX_MP)) * MAX_SCALSE_MagicEnergyCore); //TODO:
}

void MyMagicEnergyCore::onActive() {
    _pKurokoB->execGravitationMvSequenceTwd(P_MYSHIP, 10000, 200, 2000);
}

void MyMagicEnergyCore::processBehavior() {
    _pScaler->scaleLinerStep(
                (P_MYSHIP->mp_ * (1.0 / MY_SHIP_MAX_MP)) * MAX_SCALSE_MagicEnergyCore,
                100
             );
    _pScaler->behave();
    _pKurokoB->behave();
    _pKurokoA->behave();
}

void MyMagicEnergyCore::processJudgement() {
}

void MyMagicEnergyCore::execOptionMagic() {
    ((MyMagicEnergy*)getSubFirst())->effectFlush(10);
}

int MyMagicEnergyCore::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool MyMagicEnergyCore::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}


MyMagicEnergyCore::~MyMagicEnergyCore() {
}
