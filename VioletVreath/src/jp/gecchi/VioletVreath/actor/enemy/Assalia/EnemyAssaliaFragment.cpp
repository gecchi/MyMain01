#include "stdafx.h"
#include "EnemyAssaliaFragment.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAssaliaFragment::EnemyAssaliaFragment(const char* prm_name) :
        EnemyAssaliaBase(prm_name, "Assalia", STATUS(EnemyAssaliaFragment)) {
}

void EnemyAssaliaFragment::onCreateModel() {
}

void EnemyAssaliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(50));
    _pKurokoA->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyAssaliaFragment::onActive() {
    //ステータスリセット
    UTIL::resetEnemyAssaliaFragmentStatus(_pStatus);
    setHitAble(true);
}

void EnemyAssaliaFragment::onInactive() {
    sayonara();
}
void EnemyAssaliaFragment::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("AssaliaFragment2");
}

EnemyAssaliaFragment::~EnemyAssaliaFragment() {
}
