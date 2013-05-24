#include "stdafx.h"
#include "EnemyHermioneArmBody.h"
#include "EnemyHermione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHermioneArmBody::EnemyHermioneArmBody(const char* prm_name) :
        EnemyHermioneArm(prm_name, "HermioneArmBody", STATUS(EnemyHermioneArmBody)) {
    _class_name = "EnemyHermioneArmBody";
}

void EnemyHermioneArmBody::onCreateModel() {
}

void EnemyHermioneArmBody::initialize() {
    EnemyHermioneArm::initialize();
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyHermioneArmBody::onHit(GgafActor* prm_pOtherActor) {
}

EnemyHermioneArmBody::~EnemyHermioneArmBody() {
}
