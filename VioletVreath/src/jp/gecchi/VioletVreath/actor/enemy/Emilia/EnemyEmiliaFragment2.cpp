#include "stdafx.h"
#include "EnemyEmiliaFragment2.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment2::EnemyEmiliaFragment2(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", STATUS(EnemyEmiliaFragment2)) {
}

void EnemyEmiliaFragment2::onCreateModel() {
}

void EnemyEmiliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(30));
    getKuroko()->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyEmiliaFragment2::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragment2Status(_pStatus);
    setHitAble(true);
}

void EnemyEmiliaFragment2::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment2::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("EmiliaFragment3");
}

EnemyEmiliaFragment2::~EnemyEmiliaFragment2() {
}
