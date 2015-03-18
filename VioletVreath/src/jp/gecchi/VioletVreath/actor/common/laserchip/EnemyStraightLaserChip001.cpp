#include "EnemyStraightLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraightLaserChip001::EnemyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "EnemyStraightLaserChip001", STATUS(EnemyStraightLaserChip001)) {
    _class_name = "EnemyStraightLaserChip001";
    setMvVelo(PX_C(100));
}

void EnemyStraightLaserChip001::initialize() {
    getKuroko()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(15000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
}

void EnemyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    getStatus()->reset();
}
void EnemyStraightLaserChip001::processBehavior() {
    StraightLaserChip::processBehavior();
}

void EnemyStraightLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
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

EnemyStraightLaserChip001::~EnemyStraightLaserChip001() {
}

