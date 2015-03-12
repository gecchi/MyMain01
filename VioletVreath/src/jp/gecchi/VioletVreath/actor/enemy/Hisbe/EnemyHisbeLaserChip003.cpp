#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/scene/WalledScene.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        WateringLaserChip(prm_name, "HisbeLaserChip003", STATUS(EnemyHisbeLaserChip003)) {
    _class_name = "EnemyHisbeLaserChip003";
    pConn_pSplManuf_ = getConnection_SplineManufactureManager("EnemyHisbeLaserChip003"); //�S�X�p�[�Ȑ�
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    pKurokoLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    sp_index_ = 0;
    pNearestScrollingScene_ = nullptr;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);

    getKuroko()->relateFaceByMvAng(true);
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
    sp_index_ = 0;
    pNearestScrollingScene_ = ((DefaultScene*)getPlatformScene())->getNearestScrollingScene();
}

void EnemyHisbeLaserChip003::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    if (pNearestScrollingScene_ && pNearestScrollingScene_->_pFuncScrolling == WalledScene::scrollX) {
        pKurokoLeader_->_x_start -= pNearestScrollingScene_->getScrollSpeed();
    }
    if (sp_index_ > (pKurokoLeader_->_pManufacture->_sp->_rnum -1)) {

    } else {
        pKuroko->setMvVelo(pKurokoLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pKurokoLeader_->behave(); ������ pKuroko->_velo_mv ���Q�Ƃ����t���[�������肵�Ă�̂ŁA
    //�P�t���[���Ŏ��̓_�ɓ��B����ׂ��ApKurokoLeader_->behave(); �̑O�� pKuroko->setMvVelo() �Őݒ肵�Ȃ���΂����Ȃ��B
    pKurokoLeader_->behave();
    pKuroko->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //�p���ۂ߂����Ȃ��̂ŃI�[�o�[���C�h
    if (_was_paused_flg) {
        GgafDxGeometricActor::processSettlementBehavior();
    } else {
        LaserChip::processSettlementBehavior();
    }
}
void EnemyHisbeLaserChip003::processJudgement() {
    if (pKurokoLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onHit(GgafActor* prm_pOtherActor) {
    const bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

void EnemyHisbeLaserChip003::onInactive() {
    WateringLaserChip::onInactive();
}

EnemyHisbeLaserChip003::~EnemyHisbeLaserChip003() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}

