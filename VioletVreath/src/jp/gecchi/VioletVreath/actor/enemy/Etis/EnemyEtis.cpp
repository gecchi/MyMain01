#include "stdafx.h"
#include "EnemyEtis.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEtis::EnemyEtis(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Etis", STATUS(EnemyEtis)) {
    _class_name = "EnemyEtis";
    pAxMver_ = NEW GgafDxAxesMover(this);
    width_x_ = 220*2*LEN_UNIT;
    height_z_ = 220*2*LEN_UNIT;
    depth_y_ = 36*2*LEN_UNIT;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
}

void EnemyEtis::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEtis::initialize() {
    int nArea = 0;
    for (int i = 0; i < (width_x_ - depth_y_) ; i+= depth_y_) {
        nArea++;
    }
    _pColliChecker->makeCollision(nArea);
    for (int i = 0, n = 0; i < width_x_-depth_y_; i += depth_y_, n++) {
        _pColliChecker->setColliAAB(n,
                                    i - ((depth_y_/2.0)/1.5)-(width_x_/2.0 - depth_y_/2.0), -((depth_y_/2.0)/1.5), -(height_z_/2.0),
                                    i + ((depth_y_/2.0)/1.5)-(width_x_/2.0 - depth_y_/2.0),  ((depth_y_/2.0)/1.5),  (height_z_/2.0),
                                    false, false, true );
    }
}

void EnemyEtis::onActive() {
    _pStatus->reset();
    setAlpha(1.0);
    _pKuroko->setMvVelo(0);
    pAxMver_->setVxMvVelo(-3000);
    _pKuroko->setFaceAngVelo(AXIS_Z, 1000);
    static coord renge_y = (MyShip::lim_y_top_ - MyShip::lim_y_bottom_) * 3;
    static coord renge_z = (MyShip::lim_z_left_ - MyShip::lim_z_right_) * 3;
    _x = GgafDxUniverse::_x_gone_right - 1000;
    _y = RND(-(renge_y/2) , +(renge_y/2));
    _z = RND(-(renge_z/2) , +(renge_z/2));
    setHitAble(true);
}

void EnemyEtis::processBehavior() {
    //���Z�����N�|�C���g������
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //���W�ɔ��f
    _pKuroko->behave();
    pAxMver_->behave();
    _pSeTx->behave();
}

void EnemyEtis::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyEtis::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j��
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //��j��
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyEtis::onInactive() {
    sayonara();
}

EnemyEtis::~EnemyEtis() {
    GGAF_DELETE(pAxMver_);
}

