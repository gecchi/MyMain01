#include "EnemyDrastea.h"

#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Trucker.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_MOVE01_1   ,
    PROG_SPLINE_MOVE,
    PROG_MOVE02_1   ,
    PROG_MOVE02_2   ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED   ,
    SE_EXPLOSION ,
};

EnemyDrastea::EnemyDrastea(const char* prm_name) :
        VvEnemyActor<CubeMapMeshSetActor>(prm_name, "Drastea", StatusReset(EnemyDrastea)) {
    _class_name = "EnemyDrastea";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyDrastea::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDrastea::initialize() {
    setAlpha(0.7);
//    effectBlendOne();
    setCubeMap("BkSky_cubemap.dds",0.3);

    //�����蔻��BOX�P�̊e�ӂ̒���
    coord colli_box_x_len  = PX_C(35);
    coord colli_box_y_len  = PX_C(35);
    coord colli_box_z_len  = PX_C(35);
    //x,y,z�������̓����蔻��BOX�̐�
    int box_num_x     = 6;
    int box_num_y     = 1;
    int box_num_z     = 6;
    //�e�����蔻��BOX���m�̊Ԋu�ix,y,z�������j
    coord colli_box_spc_dx = PX_C(29);
    coord colli_box_spc_dy = PX_C(29);
    coord colli_box_spc_dz = PX_C(29);

    //�����蔻��BOX����
    int colli_areas = box_num_x * box_num_y * box_num_z;
    CollisionChecker* pChecker = getCollisionChecker();
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
    GgafDx::Kuroko* const pKuroko = getKuroko();
    GgafDx::Trucker* const pTrucker = getTrucker();
    pKuroko->setMvVelo(0);
    pKuroko->setRollPitchYawFaceAngVelo(700, 1100, 300);
    pTrucker->setVxMvVelo(-3000);
    const coord appearances_renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 4;
    const coord appearances_renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 4;
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    _x = pSpacetime->_x_bound_right;
    _y = RND(-(appearances_renge_y/2) , +(appearances_renge_y/2));
    _z = RND(-(appearances_renge_z/2) , +(appearances_renge_z/2));
    setHitAble(true);
}

void EnemyDrastea::processBehavior() {
    //���W�ɔ��f
    getKuroko()->behave();
    getTrucker()->behave();
    getSeTransmitter()->behave();
}

void EnemyDrastea::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDrastea::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyDrastea::onInactive() {
    sayonara();
}

EnemyDrastea::~EnemyDrastea() {
}

