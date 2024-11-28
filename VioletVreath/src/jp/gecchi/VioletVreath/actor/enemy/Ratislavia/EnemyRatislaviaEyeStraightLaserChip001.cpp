#include "EnemyRatislaviaEyeStraightLaserChip001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyRatislaviaEyeStraightLaserChip001::EnemyRatislaviaEyeStraightLaserChip001(const char* prm_name) :
        VvEnemyActor<StraightLaserChip>(prm_name, "RatislaviaEyeStraightLaserChip001", StatusReset(EnemyRatislaviaEyeStraightLaserChip001)) {
    _class_name = "EnemyRatislaviaEyeStraightLaserChip001";
    setMvVelo(500000);
}

void EnemyRatislaviaEyeStraightLaserChip001::initialize() {
    getLocusVehicle()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(300000);
    setHitAble(true, false); //‰æ–ÊŠO“–‚½‚è”»’è‚Í–³‚µ
    //setScaleR(5.0);
    setScaleR(500.0);
    setCullingDraw(false);
}

void EnemyRatislaviaEyeStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    getLocusVehicle()->setMvVelo(100000);
    getLocusVehicle()->setMvAcce(300);
    getStatus()->reset();
}

void EnemyRatislaviaEyeStraightLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

EnemyRatislaviaEyeStraightLaserChip001::~EnemyRatislaviaEyeStraightLaserChip001() {
}

