#include "EnemyEmiliaFragment3.h"

#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment3::EnemyEmiliaFragment3(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia") {
    getStatus()->reset(statusResetFunction(EnemyEmiliaFragment3));
}

void EnemyEmiliaFragment3::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    EnemyEmiliaBase::onDispatched(prm_pOrg, prm_pFormationEmilia);
    setPositionAt(prm_pOrg);
    GgafDx::Kuroko* pKuroko = getKuroko();
    pKuroko->takeoverMvFrom(prm_pOrg->getKuroko());
    pKuroko->setMvVelo(pKuroko->_velo_mv/2); //半分のスピードへ
    pKuroko->addRyMvAng(RND(D_ANG(-90), D_ANG(+90)));
    pKuroko->addRzMvAng(RND(D_ANG(-90), D_ANG(+90)));
}

void EnemyEmiliaFragment3::onCreateModel() {
}

void EnemyEmiliaFragment3::initialize() {
    setHitAble(true);
    setScaleR(0.04);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(30));
    getKuroko()->setRollPitchYawFaceAngVelo(D_ANG(0), D_ANG(0), D_ANG(12));
}

void EnemyEmiliaFragment3::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaFragment3Status(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment3::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment3::processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) {
    //おしまし
}

EnemyEmiliaFragment3::~EnemyEmiliaFragment3() {
}
