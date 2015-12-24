#include "EnemyEmusLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyEmusLaserChip001::EnemyEmusLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "EmusLaserChip001", STATUS(EnemyEmusLaserChip001)) {
    _class_name = "EnemyEmusLaserChip001";
}

void EnemyEmusLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(300000);
    pKuroko->linkFaceAngByMvAng(true);
}

void EnemyEmusLaserChip001::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
}

void EnemyEmusLaserChip001::processBehavior() {
    getKuroko()->behave();
}

void EnemyEmusLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEmusLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (getActiveFrame() < 30 && (pOther->getKind() & KIND_CHIKEI)) {
        //�o��30�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
        return;
    } else {
        bool was_destroyed = UTIL::transactEnemyHit(this, pOther);
        if (was_destroyed) {
            //�j�󂳂ꂽ��(�X�^�~�i <= 0)
            sayonara();
        } else {
            //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
        }
    }
}
void EnemyEmusLaserChip001::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyEmusLaserChip001::~EnemyEmusLaserChip001() {
}

