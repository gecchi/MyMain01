#include "MyMagicEnergyCore.h"

#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergy.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MAX_SCALSE_MagicEnergyCore (R_SC(2))
MyMagicEnergyCore::MyMagicEnergyCore(const char* prm_name) :
        DefaultMeshActor(prm_name, "MagicEnergyCore", STATUS(MyMagicEnergyCore)) {
    _class_name = "MyMagicEnergyCore";
    pScaler_ = NEW GgafDxScaler(this);
    pAxsMver_ = NEW GgafDxAxesMover(this);
    MyMagicEnergy* p = NEW MyMagicEnergy("MyMagicEnergy", this);
    addSubLast(p);
    setAlpha(0.7);
}

void MyMagicEnergyCore::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergyCore::initialize() {
    setHitAble(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, 1);
}

void MyMagicEnergyCore::onActive() {
    pAxsMver_->execGravitationMvSequenceTwd(P_MYSHIP, 10000, 200, 2000);
}

void MyMagicEnergyCore::processBehavior() {
    double s = (P_MYSHIP->mp_ * (1.0 / MY_SHIP_MAX_MP));
    GgafDxKuroko* const pKuroko = getKuroko();
    //MPに連動して大きくなる
    pScaler_->transitionLinerStep(
                s * MAX_SCALSE_MagicEnergyCore,
                100
             );
    CollisionChecker3D* pChecker = getCollisionChecker();
    if (s > 0.0) {
        pChecker->enable(0);
        pChecker->setColliSphere(0, s*PX_C(30));
    } else {
        pChecker->disable(0);
    }
    pScaler_->behave();
    pAxsMver_->behave();
    pKuroko->behave();
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

bool MyMagicEnergyCore::isOutOfUniverse() const {
    //ゲーム座標範囲外判定無し
    return false;
}

MyMagicEnergyCore::~MyMagicEnergyCore() {
    GGAF_DELETE(pScaler_);
    GGAF_DELETE(pAxsMver_);
}
