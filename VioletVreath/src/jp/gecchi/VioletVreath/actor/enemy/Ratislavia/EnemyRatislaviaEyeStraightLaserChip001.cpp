#include "EnemyRatislaviaEyeStraightLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;


EnemyRatislaviaEyeStraightLaserChip001::EnemyRatislaviaEyeStraightLaserChip001(const char* prm_name) :
        VvEnemyActor<StraightLaserChip>(prm_name, "RatislaviaEyeStraightLaserChip001", StatusReset(EnemyRatislaviaEyeStraightLaserChip001)) {
    _class_name = "EnemyRatislaviaEyeStraightLaserChip001";
    setMvVelo(500000);
}

void EnemyRatislaviaEyeStraightLaserChip001::initialize() {
    callVecDriver()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(300000);
    setHitAble(true, false); //��ʊO�����蔻��͖���
    //setScaleR(5.0);
    setScaleR(500.0);
    setCullingDraw(false);
}

void EnemyRatislaviaEyeStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    callVecDriver()->setMvVelo(100000);
    callVecDriver()->setMvAcce(300);
    getStatus()->reset();
}

void EnemyRatislaviaEyeStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyRatislaviaEyeStraightLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}


EnemyRatislaviaEyeStraightLaserChip001::~EnemyRatislaviaEyeStraightLaserChip001() {
}

