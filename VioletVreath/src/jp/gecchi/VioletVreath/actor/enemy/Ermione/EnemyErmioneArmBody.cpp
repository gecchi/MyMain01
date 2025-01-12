#include "EnemyErmioneArmBody.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmBody::EnemyErmioneArmBody(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmBody", StatusReset(EnemyErmioneArmBody)) {
    _class_name = "EnemyErmioneArmBody";
}

void EnemyErmioneArmBody::onCreateModel() {
}

void EnemyErmioneArmBody::initialize() {
    EnemyErmioneArm::initialize();
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
}

void EnemyErmioneArmBody::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
}

EnemyErmioneArmBody::~EnemyErmioneArmBody() {
}
