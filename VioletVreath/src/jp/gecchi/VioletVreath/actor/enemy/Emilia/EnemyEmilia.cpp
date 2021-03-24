#include "EnemyEmilia.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Emilia/FormationEmilia.h"


using namespace GgafLib;
using namespace VioletVreath;

EnemyEmilia::EnemyEmilia(const char* prm_name) :
        EnemyEmiliaBase(prm_name, "Emilia", StatusReset(EnemyEmilia)) {
}

void EnemyEmilia::onDispatched(EnemyEmiliaBase* prm_pOrg, FormationEmilia* prm_pFormationEmilia) {
    EnemyEmiliaBase::onDispatched(prm_pOrg, prm_pFormationEmilia);
    //prm_pOrg �͖���(nullptr)
    const coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    const coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    setPosition(pSpacetime->_x_bound_right,
                      RND(-(appearances_renge_y/2) , +(appearances_renge_y/2)),
                      RND(-(appearances_renge_z/2) , +(appearances_renge_z/2)) );
    callVecDriver()->setMvVelo(RF_FormationEmilia_MvVelo(G_RANK) );
}

void EnemyEmilia::onCreateModel() {
}

void EnemyEmilia::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, PX_C(170));
    callVecDriver()->setRollPitchYawFaceAngVelo(D_ANG(1), D_ANG(2), D_ANG(3));
    setScaleR(0.5);
}

void EnemyEmilia::onActive() {
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    setHitAble(true);
    GgafDx::VecDriver* const pVecDriver = callVecDriver();
    pVecDriver->setMvAngTwd(0, D180ANG);
    pVecDriver->addRyMvAng(RND(D_ANG(-5), D_ANG(+5)));
    pVecDriver->addRzMvAng(RND(D_ANG(-5), D_ANG(+5)));
}

void EnemyEmilia::onInactive() {
    sayonara();
}

void EnemyEmilia::processStaminaEnd(const GgafDx::GeometricActor* prm_pOther) {
    pFormationEmilia_->appearFragment(this);
}

EnemyEmilia::~EnemyEmilia() {
}


