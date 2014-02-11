#include "stdafx.h"
#include "EnemyWateringLaserChip001.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;



EnemyWateringLaserChip001::EnemyWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "EnemyWateringLaserChip001", STATUS(EnemyWateringLaserChip001)) {
    _class_name = "EnemyWateringLaserChip001";
}

void EnemyWateringLaserChip001::initialize() {
    _pKuroko->relateFaceWithMvAng(true);
    registerHitAreaCube_AutoGenMidColli(50000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void EnemyWateringLaserChip001::onCreateModel() {

}

void EnemyWateringLaserChip001::onActive() {
    WateringLaserChip::onActive();
    _pKuroko->setMvVelo(PX_C(80));
    _pKuroko->setMvAcce(300);
    _pStatus->reset();
}

void EnemyWateringLaserChip001::processBehavior() {
    if (getActiveFrame() == 1) {
        //�����ݒ�̍��W���炢���Ȃ�Y����̂�h�~
        coord tmp_x = _x;
        coord tmp_y = _y;
        coord tmp_z = _z;
        _pKuroko->behave();
        position(tmp_x, tmp_y, tmp_z);
    } else {
        _pKuroko->behave();
    }
    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
}


void EnemyWateringLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false); //�ȍ~����t���[�����Ńq�b�g�����Ȃ��B
        UTIL::activateExplosionEffectOf(this); //�����G�t�F�N�g�o��
        sayonara();
    }
}

void EnemyWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}


EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
}

