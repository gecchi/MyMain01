#include "stdafx.h"
#include "EnemyAstraeaLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAstraeaLaserChip001::EnemyAstraeaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "AstraeaLaserChip001", STATUS(EnemyAstraeaLaserChip001)) {
    _class_name = "EnemyAstraeaLaserChip001";
}

void EnemyAstraeaLaserChip001::initialize() {
    registHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyAstraeaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    _pStatus->reset();

    _pKurokoA->setMvVelo(10000);
    _pKurokoA->setMvAcce(400);
    _pKurokoA->relateMvFaceAng(true);
}

void EnemyAstraeaLaserChip001::executeHitChk_MeAnd(GgafActor* prm_pOtherActor) {
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

void EnemyAstraeaLaserChip001::processBehaviorHeadChip() {
    if (getActiveFrame() == 40) {
        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                7000, 0,
                                TURN_ANTICLOSE_TO, false);
    }


    if (!_pKurokoA->isTurningMvAng()) {
        _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                100, 0,
                                TURN_CLOSE_TO, false);
    }
//
//    if (frame_of_behaving_from_onActive_ == 35) {
//        _pKurokoA->turnMvAngTwd(
//                    P_MYSHIP,
//                    20000, TURN_ANTICLOSE_TO);
//    }

    _pKurokoA->behave();
}

void EnemyAstraeaLaserChip001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    //�q�b�g��
    //�̗͌v�Z
    int sta = UTIL::calcEnemyStamina(this, pOther);
    if (sta <= 0) {
        //�q�b�g���ď��Ŏ�
        sayonara();
    } else {
        //�q�b�g���Đ�����
    }
}

EnemyAstraeaLaserChip001::~EnemyAstraeaLaserChip001() {

}

