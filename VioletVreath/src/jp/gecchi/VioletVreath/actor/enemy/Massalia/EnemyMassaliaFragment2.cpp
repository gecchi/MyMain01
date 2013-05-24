#include "stdafx.h"
#include "EnemyMassaliaFragment2.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassaliaFragment2::EnemyMassaliaFragment2(const char* prm_name) :
        EnemyMassaliaBase(prm_name, "Massalia", STATUS(EnemyMassaliaFragment2)) {
}

void EnemyMassaliaFragment2::onCreateModel() {
}

void EnemyMassaliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(30));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyMassaliaFragment2::onActive() {
    //ステータスリセット
    UTIL::resetEnemyMassaliaFragment2Status(_pStatus);
    setHitAble(true);
}

void EnemyMassaliaFragment2::onInactive() {
    sayonara();
}

void EnemyMassaliaFragment2::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("MassaliaFragment3");
}

EnemyMassaliaFragment2::~EnemyMassaliaFragment2() {
}
