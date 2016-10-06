#include "EnemyEmiliaFragment2.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/FormationEmilia.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment2::EnemyEmiliaFragment2(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", STATUS(EnemyEmiliaFragment2)) {
}

void EnemyEmiliaFragment2::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    EnemyEmiliaBase::onDispatched(prm_pOrg, prm_pFormationEmilia);
    locateAs(prm_pOrg);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->takeoverMvFrom(prm_pOrg->getKuroko());
    pKuroko->setMvVelo(pKuroko->_velo_mv/2); //半分のスピードへ
    pKuroko->addRyMvAng(RND(D_ANG(-90), D_ANG(+90)));
    pKuroko->addRzMvAng(RND(D_ANG(-90), D_ANG(+90)));
}

void EnemyEmiliaFragment2::onCreateModel() {
}

void EnemyEmiliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(50));
    getKuroko()->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(6), D_ANG(9));
}

void EnemyEmiliaFragment2::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragment2Status(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment2::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment2::processStaminaEnd(const GgafDxGeometricActor* prm_pOther) {
    pFormationEmilia_->appearFragment3(this);
}

EnemyEmiliaFragment2::~EnemyEmiliaFragment2() {
}
