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
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("GURUGURU");
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
}

void EnemyStraeaLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setMvVelo(30000);
    pKuroko->linkFaceAngByMvAng(true);
}

void EnemyStraeaLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pKurokoLeader_->start(RELATIVE_COORD_DIRECTION); //�����������Ƀ��[���h�ϊ�
}

void EnemyStraeaLaserChip003::processBehavior() {
    pKurokoLeader_->behave();
    getKuroko()->behave();
    WateringLaserChip::processBehavior();
}

void EnemyStraeaLaserChip003::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}
void EnemyStraeaLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyStraeaLaserChip003::~EnemyStraeaLaserChip003() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}

