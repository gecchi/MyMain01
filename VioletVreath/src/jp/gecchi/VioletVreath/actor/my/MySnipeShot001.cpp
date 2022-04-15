#include "MySnipeShot001.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

MySnipeShot001::MySnipeShot001(const char* prm_name) :
        VvMyActor<SingleLaser>(prm_name, "MySnipeShot001", StatusReset(MySnipeShot001)) { //SingleLaser�͍ő�27�Z�b�g�ł���
    _class_name = "MySnipeShot001";
}

void MySnipeShot001::initialize() {
    setHitAble(false);
    setScaleR(4.0);
    setCullingDraw(false);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -PX_C(80), -PX_C(5), -PX_C(5),
                                PX_C(80),  PX_C(5),  PX_C(5));
    getVecVehicle()->setRollFaceAngVelo(D_ANG(12));
    getVecVehicle()->linkFaceAngByMvAng(true);
}

void MySnipeShot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
}

void MySnipeShot001::processBehavior() {
    getVecVehicle()->behave();
}

void MySnipeShot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void MySnipeShot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*)prm_pOtherActor;
    setHitAble(false);
    UTIL::activateExplosionEffectOf(this);
    sayonara(); //�ђʂ��Ȃ�
}


//void MySnipeShot001::drawHitArea() {
//    CollisionChecker::drawHitArea(_pColliChecker);
//}
MySnipeShot001::~MySnipeShot001() {
}
