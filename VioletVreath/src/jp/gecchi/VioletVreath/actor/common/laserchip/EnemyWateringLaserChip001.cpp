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
    getKuroko()->relateFaceByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(50000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void EnemyWateringLaserChip001::onCreateModel() {

}

void EnemyWateringLaserChip001::onActive() {
    WateringLaserChip::onActive();
    getKuroko()->setMvVelo(PX_C(100));
    getKuroko()->setMvAcce(PX_C(2));
    getStatus()->reset();
}

void EnemyWateringLaserChip001::processBehavior() {
    if (onChangeToActive()) {
        //�A�N�e�B�u�ɂȂ����u�Ԃ́A
        //���p���A�N�^�[���w�肵���ŏ��̍��W�ŕ\���������B
        //���߂̊������s���ƁA�����̂ŁA�ŏ������͂��̂܂܂̍��W�ŕ\���B
    } else {
        GgafDxKuroko* const pKuroko = getKuroko();
        pKuroko->behave();
    }
    WateringLaserChip::processBehavior();//���W���ړ������Ă���Ăяo������
}


void EnemyWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() <= 2 && (pOther->getKind() & KIND_CHIKEI)) {
        //�o��2�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
        return;
    }

    const bool was_destroyed = UTIL::transactEnemyHit(this, pOther);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyWateringLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}


EnemyWateringLaserChip001::~EnemyWateringLaserChip001() {
}

