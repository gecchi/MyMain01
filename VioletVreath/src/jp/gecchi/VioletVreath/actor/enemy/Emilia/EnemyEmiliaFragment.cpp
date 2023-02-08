#include "EnemyEmiliaFragment.h"

#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/FormationEmilia.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"


using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment::EnemyEmiliaFragment(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", StatusReset(EnemyEmiliaFragment)) {
}

void EnemyEmiliaFragment::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    EnemyEmiliaBase::onDispatched(prm_pOrg, prm_pFormationEmilia);
    setPositionAt(prm_pOrg);
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    pVecVehicle->takeoverFrom(prm_pOrg->getVecVehicle());
    pVecVehicle->setMvVelo(pVecVehicle->_velo_mv/2); //半分のスピードへ
    pVecVehicle->addRyMvAng(RND(D_ANG(-90), D_ANG(+90)));
    pVecVehicle->addRzMvAng(RND(D_ANG(-90), D_ANG(+90)));
}

void EnemyEmiliaFragment::onCreateModel() {
}

void EnemyEmiliaFragment::initialize() {
    setHitAble(true);
    setScaleR(0.3);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(80));
    getVecVehicle()->setRollPitchYawFaceAngVelo(D_ANG(2), D_ANG(4), D_ANG(8));
}

void EnemyEmiliaFragment::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragmentStatus(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment::processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) {
    pFormationEmilia_->appearFragment2(this);
}

EnemyEmiliaFragment::~EnemyEmiliaFragment() {
}

