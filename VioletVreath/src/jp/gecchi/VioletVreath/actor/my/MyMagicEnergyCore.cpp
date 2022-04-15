#include "MyMagicEnergyCore.h"

#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/GeoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
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
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 1);
}

void MyMagicEnergyCore::onActive() {
    getGeoVehicle()->execGravitationMvSequenceTwd(
                      pMYSHIP,
                      +PX_C(90), 0, 0,
                      PX_C(10), PX_C(1), PX_C(20));
    getScaler()->beat(40, 5, 32, 3, -1); //�ۓ����ۂ�����
}

void MyMagicEnergyCore::processBehavior() {
    static const double max_mp_rate = 1.0 / MY_SHIP_MAX_MP;
    double s = pMYSHIP->mp_ * max_mp_rate;
    //MP�ɘA�����đ傫���Ȃ�
    getScaler()->setRange(s*MAX_SCALSE_MagicEnergyCore*0.7, s*MAX_SCALSE_MagicEnergyCore);
    CollisionChecker* pChecker = getCollisionChecker();
    if (s > 0.0) {
        pChecker->enable(0);
        pChecker->changeColliSphereR(0, s*PX_C(100));
    } else {
        pChecker->disable(0);
    }
    getScaler()->behave();
    getGeoVehicle()->behave();
}

void MyMagicEnergyCore::processJudgement() {
}

int MyMagicEnergyCore::isOutOfView() {
    //��ʊO���薳��
    return 0;
}

bool MyMagicEnergyCore::isOutOfSpacetime() const {
    //�Q�[�����W�͈͊O���薳��
    return false;
}

MyMagicEnergyCore::~MyMagicEnergyCore() {
}
