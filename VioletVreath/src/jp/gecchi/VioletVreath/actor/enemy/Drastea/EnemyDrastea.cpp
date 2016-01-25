#include "EnemyDrastea.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyDrastea::EnemyDrastea(const char* prm_name) :
        CubeMapMeshSetActor(prm_name, "Drastea", STATUS(EnemyDrastea)) {
    _class_name = "EnemyDrastea";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyDrastea::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDrastea::initialize() {
    setAlpha(0.7);
//    effectBlendOne();
    setCubeMap("BkSky_cubemap.dds",0.3);

    //当たり判定BOX１つの各辺の長さ
    coord colli_box_x_len  = PX_C(35);
    coord colli_box_y_len  = PX_C(35);
    coord colli_box_z_len  = PX_C(35);
    //x,y,z軸方向の当たり判定BOXの数
    int box_num_x     = 6;
    int box_num_y     = 1;
    int box_num_z     = 6;
    //各当たり判定BOX同士の間隔（x,y,z軸方向）
    coord colli_box_spc_dx = PX_C(29);
    coord colli_box_spc_dy = PX_C(29);
    coord colli_box_spc_dz = PX_C(29);

    //当たり判定BOX生成
    int colli_areas = box_num_x * box_num_y * box_num_z;
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(colli_areas);
    int n = 0;
    coord bx = -((colli_box_x_len*box_num_x + colli_box_spc_dx*(box_num_x-1)) / 2);
    coord by = -((colli_box_y_len*box_num_y + colli_box_spc_dy*(box_num_y-1)) / 2);
    coord bz = -((colli_box_z_len*box_num_z + colli_box_spc_dz*(box_num_z-1)) / 2);
    for (int nx = 0; nx < box_num_x; nx++) {
        coord colli_bx = (colli_box_x_len*nx) + (colli_box_spc_dx*nx);
        for (int ny = 0; ny < box_num_y; ny++) {
            coord colli_by = (colli_box_y_len*ny) + (colli_box_spc_dy*ny);
            for (int nz = 0; nz < box_num_z; nz++) {
                coord colli_bz = (colli_box_z_len*nz) + (colli_box_spc_dz*nz);

                pChecker->setColliAABox(n, bx + colli_bx,
                                         by + colli_by,
                                         bz + colli_bz,
                                         bx + colli_bx + colli_box_x_len,
                                         by + colli_by + colli_box_y_len,
                                         bz + colli_bz + colli_box_z_len,
                                         true, true, true );
                n++;
            }
        }
    }
}

void EnemyDrastea::onActive() {
    getStatus()->reset();
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(0);
    pKuroko->setRollPitchYawFaceAngVelo(700, 1100, 300);
    pAxsMver_->setVxMvVelo(-3000);
    const coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 4;
    const coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 4;
    Spacetime* pSpacetime =  P_GOD->getSpacetime();
    _x = pSpacetime->_x_bound_right;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));
    setHitAble(true);
}

void EnemyDrastea::processBehavior() {
    //座標に反映
    getKuroko()->behave();
    pAxsMver_->behave();
    getSeTx()->behave();
}

void EnemyDrastea::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDrastea::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyDrastea::onInactive() {
    sayonara();
}

EnemyDrastea::~EnemyDrastea() {
    GGAF_DELETE(pAxsMver_);
}

