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
    colli_box_dX_ = 1;
    colli_box_dY_ = 1;
    colli_box_dZ_ = 1;
    box_num_x_ = 1;
    box_num_y_ = 1;
    box_num_z_ = 1;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyDrastea::config(
    coord prm_colli_box_dx,
    coord prm_colli_box_dY,
    coord prm_colli_box_dZ,
    int prm_box_num_x,
    int prm_box_num_y,
    int prm_box_num_z
) {
    colli_box_dX_  = prm_colli_box_dx;
    colli_box_dY_  = prm_colli_box_dY;
    colli_box_dZ_  = prm_colli_box_dZ;
    box_num_x_     = prm_box_num_x;
    box_num_y_     = prm_box_num_y;
    box_num_z_     = prm_box_num_z;
}

void EnemyDrastea::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyDrastea::initialize() {
    setAlpha(0.7);
//    effectBlendOne();
    setCubeMap("BkSky_cubemap.dds",0.3);
    config(PX_C(30),PX_C(30),PX_C(30),
           6, 1, 6);
    int colli_areas = box_num_x_ * box_num_y_ * box_num_z_;
    _pColliChecker->makeCollision(colli_areas);
    int n = 0;
    coord actor_width_dX = colli_box_dX_*box_num_x_;
    coord actor_width_dY = colli_box_dY_*box_num_y_;
    coord actor_width_dZ = colli_box_dZ_*box_num_z_;
    for (int nx = 0; nx < box_num_x_; nx++) {
        for (int ny = 0; ny < box_num_y_; ny++) {
            for (int nz = 0; nz < box_num_z_; nz++) {
                _pColliChecker->setColliAAB(n,
                                   -(actor_width_dX/2) + (colli_box_dX_*nx),
                                   -(actor_width_dY/2) + (colli_box_dY_*ny),
                                   -(actor_width_dZ/2) + (colli_box_dZ_*nz),
                                   -(actor_width_dX/2) + (colli_box_dX_*nx) + colli_box_dX_,
                                   -(actor_width_dY/2) + (colli_box_dY_*ny) + colli_box_dY_,
                                   -(actor_width_dZ/2) + (colli_box_dZ_*nz) + colli_box_dZ_,
                                   true, true, true );
                n++;
            }
        }
    }
}

void EnemyDrastea::onActive() {
    _pStatus->reset();
    _pKuroko->setMvVelo(0);
    pAxsMver_->setVxMvVelo(-3000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 1000);
    _pKuroko->setFaceAngVelo(AXIS_Y, 300);
    _pKuroko->setFaceAngVelo(AXIS_X, 700);
    static coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    static coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    _x = GgafDxUniverse::_x_gone_right - 1000;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));
    setHitAble(true);
}

void EnemyDrastea::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //À•W‚É”½‰f
    _pKuroko->behave();
    pAxsMver_->behave();
    _pSeTx->behave();
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
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyDrastea::onInactive() {
    sayonara();
}

EnemyDrastea::~EnemyDrastea() {
    GGAF_DELETE(pAxsMver_);
}

