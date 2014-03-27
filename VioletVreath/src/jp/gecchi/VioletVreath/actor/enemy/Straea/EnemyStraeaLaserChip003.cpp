#include "stdafx.h"
#include "EnemyStraeaLaserChip003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyStraeaLaserChip003::EnemyStraeaLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "StraeaLaserChip001", STATUS(EnemyStraeaLaserChip003)) {
    _class_name = "EnemyStraeaLaserChip003";
    pSplManufConnection_ = connect_SplineManufactureManager("GURUGURU");
    pKurokoLeader_ = pSplManufConnection_->peek()->createKurokoLeader(getKuroko());
}

void EnemyStraeaLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setMvVelo(30000);
    pKuroko->relateFaceByMvAng(true);
}

void EnemyStraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //�����������Ƀ��[���h�ϊ�
}

void EnemyStraeaLaserChip003::processBehavior() {
    pKurokoLeader_->behave();
    getKuroko()->behave();
    WateringLaserChip::processBehavior();
}

void EnemyStraeaLaserChip003::onHit(GgafActor* prm_pOtherActor) {
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
void EnemyStraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyStraeaLaserChip003::~EnemyStraeaLaserChip003() {
    GGAF_DELETE(pKurokoLeader_);
    pSplManufConnection_->close();
}

