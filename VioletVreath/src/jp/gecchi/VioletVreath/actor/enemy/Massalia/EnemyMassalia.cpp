#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyMassalia::EnemyMassalia(const char* prm_name) :
        EnemyMassaliaBase(prm_name, "Massalia", STATUS(EnemyMassalia)) {
}

void EnemyMassalia::onCreateModel() {
}

void EnemyMassalia::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(100));
    _pKurokoA->setFaceAngVelo(D_ANG(1), D_ANG(2), D_ANG(3));
    setScaleR(0.5);
}

void EnemyMassalia::onActive() {
    //ステータスリセット
    UTIL::resetEnemyMassaliaStatus(_pStatus);
    setHitAble(true);
    static coord appearances_renge_Z = (MyShip::lim_zleft_ - MyShip::lim_zright_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_top_ - MyShip::lim_bottom_) * 3;
    _X = GgafDxUniverse::_X_goneRight - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    _pKurokoA->setMvAng(0, D180ANG);
    _pKurokoA->addRyMvAng(RND(D_ANG(-5), D_ANG(+5)));
    _pKurokoA->addRzMvAng(RND(D_ANG(-5), D_ANG(+5)));
}


void EnemyMassalia::onInactive() {
    sayonara();
}

void EnemyMassalia::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("DpCon_MassaliaFragment");
}

EnemyMassalia::~EnemyMassalia() {
}
