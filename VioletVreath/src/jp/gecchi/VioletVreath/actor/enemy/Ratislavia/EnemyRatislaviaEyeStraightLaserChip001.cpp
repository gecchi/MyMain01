#include "stdafx.h"
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
    _veloMv = 500000;
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

void EnemyRatislaviaEyeStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    //playSe3D1();
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        //sayonara();
    }

}


EnemyRatislaviaEyeStraightLaserChip001::~EnemyRatislaviaEyeStraightLaserChip001() {
}
