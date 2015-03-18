#include "EnemyRatislaviaEyeStraightLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyRatislaviaEyeStraightLaserChip001::EnemyRatislaviaEyeStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "RatislaviaEyeStraightLaserChip001", STATUS(EnemyRatislaviaEyeStraightLaserChip001)) {
    _class_name = "EnemyRatislaviaEyeStraightLaserChip001";
    _velo_mv = 500000;
}

void EnemyRatislaviaEyeStraightLaserChip001::initialize() {
    getKuroko()->setRzRyMvAng(0,0);
    registerHitAreaCube_AutoGenMidColli(300000);
    setHitAble(true, false); //��ʊO�����蔻��͖���
    //setScaleR(5.0);
    setScaleR(500.0);
    setAlpha(0.9);
}

void EnemyRatislaviaEyeStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    getKuroko()->setMvVelo(100000);
    getKuroko()->setMvAcce(300);
    getStatus()->reset();
}

void EnemyRatislaviaEyeStraightLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}


EnemyRatislaviaEyeStraightLaserChip001::~EnemyRatislaviaEyeStraightLaserChip001() {
}

