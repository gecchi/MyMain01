#include "stdafx.h"
#include "EnemyDrastea.h"

#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyDrastea::EnemyDrastea(const char* prm_name) :
        CubeMapMeshSetActor(prm_name, "Drastea", STATUS(EnemyDrastea)) {
    _class_name = "EnemyDrastea";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    colli_box_dx_ = 1;
    colli_box_dy_ = 1;
    colli_box_dz_ = 1;
    box_num_x_ = 1;
    box_num_y_ = 1;
    box_num_z_ = 1;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyDrastea::config(
    coord prm_colli_box_dx,
    coord prm_colli_box_dy,
    coord prm_colli_box_dz,
    int prm_box_num_x,
    int prm_box_num_y,
    int prm_box_num_z
) {
    colli_box_dx_  = prm_colli_box_dx;
    colli_box_dy_  = prm_colli_box_dy;
    colli_box_dz_  = prm_colli_box_dz;
    box_num_x_     = prm_box_num_x;
    box_num_y_     = prm_box_num_y;
    box_num_z_     = prm_box_num_z;
}

void EnemyDrastea::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDrastea::initialize() {
    setAlpha(0.7);
//    effectBlendOne();
    setCubeMap("BkSky_cubemap.dds",0.3);
    config(PX_C(30),PX_C(30),PX_C(30),
           6, 1, 6);
    int colli_areas = box_num_x_ * box_num_y_ * box_num_z_;
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(colli_areas);
    int n = 0;
    coord actor_width_dx = colli_box_dx_*box_num_x_;
    coord actor_width_dy = colli_box_dy_*box_num_y_;
    coord actor_width_dz = colli_box_dz_*box_num_z_;
    for (int nx = 0; nx < box_num_x_; nx++) {
        for (int ny = 0; ny < box_num_y_; ny++) {
            for (int nz = 0; nz < box_num_z_; nz++) {
                pColliChecker->setColliAAB(n,
                                   -(actor_width_dx/2) + (colli_box_dx_*nx),
                                   -(actor_width_dy/2) + (colli_box_dy_*ny),
                                   -(actor_width_dz/2) + (colli_box_dz_*nz),
                                   -(actor_width_dx/2) + (colli_box_dx_*nx) + colli_box_dx_,
                                   -(actor_width_dy/2) + (colli_box_dy_*ny) + colli_box_dy_,
                                   -(actor_width_dz/2) + (colli_box_dz_*nz) + colli_box_dz_,
                                   true, true, true );
                n++;
            }
        }
    }
}

void EnemyDrastea::onActive() {
    getStatus()->reset();
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(0);
    pKuroko->setFaceAngVelo(AXIS_Z, 1000);
    pKuroko->setFaceAngVelo(AXIS_Y, 300);
    pKuroko->setFaceAngVelo(AXIS_X, 700);
    pAxsMver_->setVxMvVelo(-3000);
    static coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    static coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    _x = GgafDxUniverse::_x_gone_right - 1000;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));
    setHitAble(true);
}

void EnemyDrastea::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    UTIL::updateEnemyRankPoint(this);
    //À•W‚É”½‰f
    getKuroko()->behave();
    pAxsMver_->behave();
    getSeTx()->behave();
}

void EnemyDrastea::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyDrastea::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        getSeTx()->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyDrastea::onInactive() {
    sayonara();
}

EnemyDrastea::~EnemyDrastea() {
    GGAF_DELETE(pAxsMver_);
}

