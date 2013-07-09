#include "stdafx.h"
#include "EnemyEmilia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

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
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, PX_C(100));
    _pKurokoA->setFaceAngVelo(D_ANG(1), D_ANG(2), D_ANG(3));
    setScaleR(0.5);
}

void EnemyEmilia::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaStatus(_pStatus);
    setHitAble(true);
    static coord appearances_renge_Z = (MyShip::lim_Z_left_ - MyShip::lim_Z_right_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_Y_top_ - MyShip::lim_Y_bottom_) * 3;
    _X = GgafDxUniverse::_X_gone_right - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    _pKurokoA->setMvAngTwd(0, D180ANG);
    _pKurokoA->addRyMvAng(RND(D_ANG(-5), D_ANG(+5)));
    _pKurokoA->addRzMvAng(RND(D_ANG(-5), D_ANG(+5)));
}


void EnemyEmilia::onInactive() {
    sayonara();
}

void EnemyEmilia::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("EmiliaFragment");
}

EnemyEmilia::~EnemyEmilia() {
}
