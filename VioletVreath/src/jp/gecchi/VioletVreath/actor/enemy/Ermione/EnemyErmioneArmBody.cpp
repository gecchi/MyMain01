#include "EnemyErmioneArmBody.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmBody::EnemyErmioneArmBody(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmBody") {
    _class_name = "EnemyErmioneArmBody";
    getStatus()->reset(statusResetFunction(EnemyErmioneArmBody));
}

void EnemyErmioneArmBody::onCreateModel() {
}

void EnemyErmioneArmBody::initialize() {
    EnemyErmioneArm::initialize();
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyErmioneArmBody::onHit(const GgafCore::Actor* prm_pOtherActor) {
}

EnemyErmioneArmBody::~EnemyErmioneArmBody() {
}
