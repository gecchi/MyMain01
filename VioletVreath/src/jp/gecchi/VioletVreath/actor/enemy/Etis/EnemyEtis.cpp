#include "EnemyEtis.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEtis::EnemyEtis(const char* prm_name) :
        DefaultMassMeshActor(prm_name, "Etis", STATUS(EnemyEtis)) {
    _class_name = "EnemyEtis";
    width_x_ = 220*2*LEN_UNIT;
    height_z_ = 220*2*LEN_UNIT;
    depth_y_ = 36*2*LEN_UNIT;
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyEtis::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyEtis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (width_x_ - depth_y_) ; i+= depth_y_) {
        nArea++;
    }
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(nArea);
    for (int i = 0, n = 0; i < width_x_-depth_y_; i += depth_y_, n++) {
        pChecker->setColliAABox(n,
                             i - ((depth_y_/2.0)/1.5)-(width_x_/2.0 - depth_y_/2.0), -((depth_y_/2.0)/1.5), -(height_z_/2.0),
                             i + ((depth_y_/2.0)/1.5)-(width_x_/2.0 - depth_y_/2.0),  ((depth_y_/2.0)/1.5),  (height_z_/2.0),
                             false, false, true );
    }
}

void EnemyEtis::onActive() {
    getStatus()->reset();
    setAlpha(1.0);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Z, D_ANG(1));
    pKuroko->setRzRyMvAng(D0ANG, D180ANG);
    pKuroko->setMvVelo(PX_C(3));
    const coord renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 4;
    const coord renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 4;
    Spacetime* pSpacetime =  pGOD->getSpacetime();
    _x = pSpacetime->_x_bound_right - 1000;
    _y = RND(-(renge_y/2) , +(renge_y/2));
    _z = RND(-(renge_z/2) , +(renge_z/2));
    setHitAble(true);
}

void EnemyEtis::processBehavior() {
    //���W�ɔ��f
    getKuroko()->behave();
}

void EnemyEtis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEtis::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        getSeTransmitter()->play3D(SE_DAMAGED);
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyEtis::onInactive() {
    sayonara();
}

EnemyEtis::~EnemyEtis() {
}

