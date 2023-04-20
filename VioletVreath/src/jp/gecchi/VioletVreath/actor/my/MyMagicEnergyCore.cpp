#include "MyMagicEnergyCore.h"

#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergy.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

#define MAX_SCALSE_MagicEnergyCore (R_SC(2))
MyMagicEnergyCore::MyMagicEnergyCore(const char* prm_name) :
        VvMyActor<DefaultMeshActor>(prm_name, "MagicEnergyCore", StatusReset(MyMagicEnergyCore)) {
    _class_name = "MyMagicEnergyCore";
    MyMagicEnergy* p = NEW MyMagicEnergy("MyMagicEnergy", this);
    appendChild(p);
    setAlpha(0.7);
}

void MyMagicEnergyCore::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergyCore::initialize() {
    setHitAble(true);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, 1);
}

void MyMagicEnergyCore::onActive() {
    getCoordVehicle()->execGravitationMvSequenceTwd(
                      pMYSHIP,
                      +PX_C(90), 0, 0,
                      PX_C(10), PX_C(1), PX_C(20));
    getScaler()->beat(40, 5, 32, 3, -1); //鼓動っぽいもの
}

void MyMagicEnergyCore::processBehavior() {
    static const double max_mp_rate = 1.0 / MY_SHIP_MAX_MP;
    double s = pMYSHIP->mp_ * max_mp_rate;
    //MPに連動して大きくなる
    getScaler()->setRange(s*MAX_SCALSE_MagicEnergyCore*0.7, s*MAX_SCALSE_MagicEnergyCore);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    if (s > 0.0) {
        setHitAble(true);
        pChecker->changeColliSphereR(0, s*PX_C(100));
    } else {
        setHitAble(false);
//        pChecker->disable(0);
    }
    getScaler()->behave();
    getCoordVehicle()->behave();
}

void MyMagicEnergyCore::processJudgement() {
}

int MyMagicEnergyCore::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool MyMagicEnergyCore::isOutOfSpacetime() const {
    //ゲーム座標範囲外判定無し
    return false;
}

MyMagicEnergyCore::~MyMagicEnergyCore() {
}
