#include "EnemyEmiliaFragment.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/FormationEmilia.h"
#include "jp/gecchi/VioletVreath/God.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment::EnemyEmiliaFragment(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", STATUS(EnemyEmiliaFragment)) {
}

void EnemyEmiliaFragment::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    EnemyEmiliaBase::onDispatched(prm_pOrg, prm_pFormationEmilia);
    setPositionAt(prm_pOrg);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->takeoverMvFrom(prm_pOrg->getKuroko());
    pKuroko->setMvVelo(pKuroko->_velo_mv/2); //半分のスピードへ
    pKuroko->addRyMvAng(RND(D_ANG(-90), D_ANG(+90)));
    pKuroko->addRzMvAng(RND(D_ANG(-90), D_ANG(+90)));
}

void EnemyEmiliaFragment::onCreateModel() {
}

void EnemyEmiliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(80));
    getKuroko()->setRollPitchYawFaceAngVelo(D_ANG(2), D_ANG(4), D_ANG(8));
}

void EnemyEmiliaFragment::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragmentStatus(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment::processStaminaEnd(const GgafDxGeometricActor* prm_pOther) {
    pFormationEmilia_->appearFragment2(this);
}

EnemyEmiliaFragment::~EnemyEmiliaFragment() {
}

