#include "stdafx.h"
#include "EnemyErmioneArmBody.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArmBody::EnemyErmioneArmBody(const char* prm_name) :
        EnemyErmioneArm(prm_name, "ErmioneArmBody", STATUS(EnemyErmioneArmBody)) {
    _class_name = "EnemyErmioneArmBody";
}

void EnemyErmioneArmBody::onCreateModel() {
}

void EnemyErmioneArmBody::initialize() {
    EnemyErmioneArm::initialize();
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, 40000);
}

void EnemyErmioneArmBody::onHit(GgafActor* prm_pOtherActor) {
}

EnemyErmioneArmBody::~EnemyErmioneArmBody() {
}
