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
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, PX_C(30));
    getKuroko()->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(0), D_ANG(10));
}

void EnemyEmiliaFragment2::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragment2Status(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment2::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment2::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("EmiliaFragment3"); //断片の断片の断片出現
}

EnemyEmiliaFragment2::~EnemyEmiliaFragment2() {
}
