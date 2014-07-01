#include "stdafx.h"
#include "EnemyEmiliaFragment.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment::EnemyEmiliaFragment(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", STATUS(EnemyEmiliaFragment)) {
}

void EnemyEmiliaFragment::onCreateModel() {
}

void EnemyEmiliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, PX_C(50));
    getKuroko()->setFaceAngVelo(D_ANG(0), D_ANG(10), D_ANG(0));
}

void EnemyEmiliaFragment::onActive() {
    //�X�e�[�^�X���Z�b�g
    UTIL::resetEnemyEmiliaFragmentStatus(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment::onInactive() {
    sayonara();
}
void EnemyEmiliaFragment::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("EmiliaFragment2");
}

EnemyEmiliaFragment::~EnemyEmiliaFragment() {
}
