#include "EnemyEmusLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyEmusLaserChip001::EnemyEmusLaserChip001(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "EmusLaserChip001", StatusReset(EnemyEmusLaserChip001)) {
    _class_name = "EnemyEmusLaserChip001";
}

void EnemyEmusLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->setMvVelo(300000);
    pLocusVehicle->linkFaceAngByMvAng(true);
}

void EnemyEmusLaserChip001::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
}

void EnemyEmusLaserChip001::processBehavior() {
    getLocusVehicle()->behave();
}

void EnemyEmusLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEmusLaserChip001::onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) {
    if (getActiveFrame() < 30 && (prm_pOppHitChecker->_kind & KIND_CHIKEI)) {
        //�o��30�t���[���ȓ��Ńq�b�g���肪�n�`�Ȃ�Ζ����i�o�����n�`�ɂ��j�󂳂������j
        return;
    } else {
        bool is_stamina_zero = performEnemyHit(prm_pOppHitChecker);
        if (is_stamina_zero) {
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

