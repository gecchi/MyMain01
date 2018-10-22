#include "MyMagicEnergyCore.h"

#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyMagicEnergy.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MAX_SCALSE_MagicEnergyCore (R_SC(2))
MyMagicEnergyCore::MyMagicEnergyCore(const char* prm_name) :
        DefaultMeshActor(prm_name, "MagicEnergyCore", STATUS(MyMagicEnergyCore)) {
    _class_name = "MyMagicEnergyCore";
    MyMagicEnergy* p = NEW MyMagicEnergy("MyMagicEnergy", this);
    appendChild(p);
    setAlpha(0.7);
}

void MyMagicEnergyCore::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void MyMagicEnergyCore::initialize() {
    setHitAble(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 1);
}

void MyMagicEnergyCore::onActive() {
    getTrucker()->execGravitationMvSequenceTwd(
                      pMYSHIP,
                      +PX_C(90), 0, 0,
                      PX_C(10), 1000, PX_C(20));
}

void MyMagicEnergyCore::processBehavior() {
    double s = (pMYSHIP->mp_ * (1.0 / MY_SHIP_MAX_MP));
    GgafDxKuroko* const pKuroko = getKuroko();
    //MPに連動して大きくなる
    getScaler()->transitionLinearStep(
                s * MAX_SCALSE_MagicEnergyCore,
                100
             );
    CollisionChecker* pChecker = getCollisionChecker();
    if (s > 0.0) {
        pChecker->enable(0);
        pChecker->setColliSphere(0, s*PX_C(100));
    } else {
        pChecker->disable(0);
    }
    getScaler()->behave();
    getTrucker()->behave();
    pKuroko->behave();
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
