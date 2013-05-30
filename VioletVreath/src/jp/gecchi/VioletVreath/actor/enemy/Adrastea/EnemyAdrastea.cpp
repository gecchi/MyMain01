#include "stdafx.h"
#include "EnemyAdrastea.h"

#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoB.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdrastea::EnemyAdrastea(const char* prm_name) :
        CubeMapMeshSetActor(prm_name, "Adrastea", STATUS(EnemyAdrastea)) {
    _class_name = "EnemyAdrastea";
    colli_box_dX_ = 1;
    colli_box_dY_ = 1;
    colli_box_dZ_ = 1;
    box_num_X_ = 1;
    box_num_Y_ = 1;
    box_num_Z_ = 1;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyAdrastea::config(
    coord prm_colli_box_dx,
    coord prm_colli_box_dY,
    coord prm_colli_box_dZ,
    int prm_box_num_X,
    int prm_box_num_Y,
    int prm_box_num_Z
) {
    colli_box_dX_  = prm_colli_box_dx;
    colli_box_dY_  = prm_colli_box_dY;
    colli_box_dZ_  = prm_colli_box_dZ;
    box_num_X_     = prm_box_num_X;
    box_num_Y_     = prm_box_num_Y;
    box_num_Z_     = prm_box_num_Z;
}

void EnemyAdrastea::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdrastea::initialize() {
    setAlpha(0.7);
//    effectBlendOne();
    setCubeMap("BkSky_cubemap.dds",0.3);
    config(PX_C(30),PX_C(30),PX_C(30),
           6, 1, 6);
    int colli_areas = box_num_X_ * box_num_Y_ * box_num_Z_;
    _pColliChecker->makeCollision(colli_areas);
    int n = 0;
    coord actor_width_dX = colli_box_dX_*box_num_X_;
    coord actor_width_dY = colli_box_dY_*box_num_Y_;
    coord actor_width_dZ = colli_box_dZ_*box_num_Z_;
    for (int nx = 0; nx < box_num_X_; nx++) {
        for (int ny = 0; ny < box_num_Y_; ny++) {
            for (int nz = 0; nz < box_num_Z_; nz++) {
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

void EnemyAdrastea::onActive() {
    _pStatus->reset();
    _pKurokoA->setMvVelo(0);
    _pKurokoB->setVxMvVelo(-3000);
    _pKurokoA->setFaceAngVelo(AXIS_Z, 1000);
    _pKurokoA->setFaceAngVelo(AXIS_Y, 300);
    _pKurokoA->setFaceAngVelo(AXIS_X, 700);
    static coord appearances_renge_Z = (MyShip::lim_Z_left_ - MyShip::lim_Z_right_) * 3;
    static coord appearances_renge_Y = (MyShip::lim_Y_top_ - MyShip::lim_Y_bottom_) * 3;
    _X = GgafDxUniverse::_X_gone_right - 1000;
    _Y = RND(-(appearances_renge_Y/2) , +(appearances_renge_Y/2));
    _Z = RND(-(appearances_renge_Z/2) , +(appearances_renge_Z/2));
    setHitAble(true);
}

void EnemyAdrastea::processBehavior() {
    //‰ÁŽZƒ‰ƒ“ƒNƒ|ƒCƒ“ƒg‚ðŒ¸­
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //À•W‚É”½‰f
    _pKurokoA->behave();
    _pKurokoB->behave();
    _pSeTx->behave();
}

void EnemyAdrastea::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAdrastea::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //”j‰óŽž
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //”ñ”j‰óŽž
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyAdrastea::onInactive() {
    sayonara();
}

EnemyAdrastea::~EnemyAdrastea() {
}

