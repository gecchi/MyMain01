#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyTorusEyeStraightLaserChip001::EnemyTorusEyeStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "TorusEyeStraightLaserChip001", STATUS(EnemyTorusEyeStraightLaserChip001)) {
    _class_name = "EnemyTorusEyeStraightLaserChip001";
    _veloMv = 200000;
}

void EnemyTorusEyeStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube(100000);
    setHitAble(true, false); //��ʊO�����蔻��͖���
    //setScaleR(5.0);
setScaleR(500.0);
    setAlpha(0.9);
}

void EnemyTorusEyeStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pKurokoA->setMvVelo(100000);
    _pKurokoA->setMvAcce(300);
    _pStatus->reset();
}

void EnemyTorusEyeStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
    if (((GgafMainActor*)prm_pOtherActor)->getKind() & KIND_CHIKEI) {
        if (_chip_kind != 2 || _can_chikei_hit) {
            GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
        } else {
            return;
        }
    } else {
        GgafDxDrawableActor::executeHitChk_MeAnd(prm_pOtherActor);
    }
}

void EnemyTorusEyeStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    //playSe3D1();
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        //sayonara();
    }

}


EnemyTorusEyeStraightLaserChip001::~EnemyTorusEyeStraightLaserChip001() {
}

