#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyStraightLaserChip001::EnemyStraightLaserChip001(const char* prm_name) :
        StraightLaserChip(prm_name, "EnemyStraightLaserChip001", STATUS(EnemyStraightLaserChip001)) {
    _class_name = "EnemyStraightLaserChip001";
    _veloMv = 100000;
}

void EnemyStraightLaserChip001::initialize() {
    _pKurokoA->setRzRyMvAng(0,0);
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false); //��ʊO�����蔻��͖���
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyStraightLaserChip001::onActive() {
    StraightLaserChip::onActive();
    _pKurokoA->setMvVelo(100000);
    _pKurokoA->setMvAcce(300);
    _pStatus->reset();
}

void EnemyStraightLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyStraightLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�E�E�E�R�R�Ƀq�b�g���ꂽ�G�t�F�N�g
    //playSe3D1();
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        //�j�󂳂ꂽ�ꍇ
        //�E�E�E�R�R�ɔj�󂳂ꂽ�G�t�F�N�g
        sayonara();
    }

}


EnemyStraightLaserChip001::~EnemyStraightLaserChip001() {
}

