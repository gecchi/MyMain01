#include "EnemyEmiliaFragment2.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/FormationEmilia.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"



using namespace GgafLib;
using namespace VioletVreath;

EnemyEmiliaFragment2::EnemyEmiliaFragment2(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", StatusReset(EnemyEmiliaFragment2)) {
}

void EnemyEmiliaFragment2::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    EnemyEmiliaBase::onDispatched(prm_pOrg, prm_pFormationEmilia);
    setPositionAt(prm_pOrg);
    GgafDx::VecDriver* pVecDriver = callVecDriver();
    pVecDriver->takeoverMvFrom(prm_pOrg->callVecDriver());
    pVecDriver->setMvVelo(pVecDriver->_velo_mv/2); //�����̃X�s�[�h��
    pVecDriver->addRyMvAng(RND(D_ANG(-90), D_ANG(+90)));
    pVecDriver->addRzMvAng(RND(D_ANG(-90), D_ANG(+90)));
}

void EnemyEmiliaFragment2::onCreateModel() {
}

void EnemyEmiliaFragment2::initialize() {
    setHitAble(true);
    setScaleR(0.1);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(50));
    callVecDriver()->setRollPitchYawFaceAngVelo(D_ANG(3), D_ANG(6), D_ANG(9));
}

void EnemyEmiliaFragment2::onActive() {
    //�X�e�[�^�X���Z�b�g
    UTIL::resetEnemyEmiliaFragment2Status(getStatus());
    setHitAble(true);
}

void EnemyEmiliaFragment2::onInactive() {
    sayonara();
}

void EnemyEmiliaFragment2::processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) {
    pFormationEmilia_->appearFragment3(this);
}

EnemyEmiliaFragment2::~EnemyEmiliaFragment2() {
}
