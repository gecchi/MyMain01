#include "EnemyEmilia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmilia::EnemyEmilia(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", STATUS(EnemyEmilia)) {
}

void EnemyEmilia::onCreateModel() {
}

void EnemyEmilia::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(100));
    getKuroko()->setRollPitchYawFaceAngVelo(D_ANG(1), D_ANG(2), D_ANG(3));
    setScaleR(0.5);
}

void EnemyEmilia::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaStatus(getStatus());
    setHitAble(true);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvAngTwd(0, D180ANG);
    pKuroko->addRyMvAng(RND(D_ANG(-5), D_ANG(+5)));
    pKuroko->addRzMvAng(RND(D_ANG(-5), D_ANG(+5)));
}

void EnemyEmilia::onInactive() {
    sayonara();
}

void EnemyEmilia::processStaminaEnd(const GgafDxGeometricActor* prm_pOther) {
    appearFragment("EmiliaFragment"); //断片出現
}

EnemyEmilia::~EnemyEmilia() {
}
