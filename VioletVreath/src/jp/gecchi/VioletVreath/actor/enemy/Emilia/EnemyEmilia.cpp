#include "EnemyEmilia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
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
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, PX_C(100));
    getKuroko()->setFaceAngVelo(D_ANG(1), D_ANG(2), D_ANG(3));
    setScaleR(0.5);
}

void EnemyEmilia::onActive() {
    //ステータスリセット
    UTIL::resetEnemyEmiliaStatus(getStatus());
    setHitAble(true);
    static coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    static coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    _x = GgafDxUniverse::_x_gone_right - 1000;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvAngTwd(0, D180ANG);
    pKuroko->addRyMvAng(RND(D_ANG(-5), D_ANG(+5)));
    pKuroko->addRzMvAng(RND(D_ANG(-5), D_ANG(+5)));
}

void EnemyEmilia::onInactive() {
    sayonara();
}

void EnemyEmilia::processStaminaEnd(GgafDxGeometricActor* prm_pOther) {
    appearFragment("EmiliaFragment"); //断片出現
}

EnemyEmilia::~EnemyEmilia() {
}
