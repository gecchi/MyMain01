#include "stdafx.h"
#include "EnemyAssaliaFragment2.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAssaliaFragment2::EnemyAssaliaFragment2(const char* prm_name) :
        EnemyAssaliaBase(prm_name, "Assalia", STATUS(EnemyAssaliaFragment2)) {
}

void EnemyAssaliaFragment2::onCreateModel() {
}

void EnemyAssaliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(30));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyAssaliaFragment2::onActive() {
    //ステータスリセット
    UTIL::resetEnemyAssaliaFragment2Status(_pStatus);
    setHitAble(true);
}

void EnemyAssaliaFragment2::onInactive() {
    sayonara();
}

void EnemyAssaliaFragment2::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("AssaliaFragment3");
}

EnemyAssaliaFragment2::~EnemyAssaliaFragment2() {
}
