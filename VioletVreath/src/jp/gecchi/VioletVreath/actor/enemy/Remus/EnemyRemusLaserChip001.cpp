#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyRemusLaserChip001::EnemyRemusLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "RemusLaserChip001", STATUS(EnemyRemusLaserChip001)) {
    _class_name = "EnemyRemusLaserChip001";
}

void EnemyRemusLaserChip001::initialize() {
    registHitAreaCube(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    _pKurokoA->setMvVelo(300000);
    _pKurokoA->relateFaceAngWithMvAng(true);
}

void EnemyRemusLaserChip001::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();
}

void EnemyRemusLaserChip001::processBehavior() {
    _pKurokoA->behave();
    WateringLaserChip::processBehavior();
}

void EnemyRemusLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActivePartFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
        //�o��30�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
        return;
    }
    //�q�b�g��
    //�̗͌v�Z
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //�q�b�g���ď��Ŏ�
        sayonara();
    } else {
        //�q�b�g���Đ�����
    }
}
void EnemyRemusLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyRemusLaserChip001::~EnemyRemusLaserChip001() {
}

