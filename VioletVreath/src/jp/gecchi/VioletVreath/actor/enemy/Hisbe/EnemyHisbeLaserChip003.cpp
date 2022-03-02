#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "HisbeLaserChip003", StatusReset(EnemyHisbeLaserChip003)) {
    _class_name = "EnemyHisbeLaserChip003";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip003"); //�S�X�p�[�Ȑ�
    pDriverLeader_ = createCurveDriverLeader(pConn_pCurveManuf_->peek());
    pDriverLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);

    getVecDriver()->linkFaceAngByMvAng(true);
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pDriverLeader_->start(RELATIVE_COORD_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
    sp_index_ = 0;
    setDriverLeader(pDriverLeader_);
}

void EnemyHisbeLaserChip003::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();

    if (pFeatureScene_) {
        pDriverLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
    }
    if (sp_index_ > (pDriverLeader_->_pManufacture->_pCurve->_rnum -1)) {

    } else {
        pVecDriver->setMvVelo(pDriverLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pDriverLeader_->behave(); ������ pVecDriver->_velo_mv ���Q�Ƃ����t���[�������肵�Ă�̂ŁA
    //�P�t���[���Ŏ��̓_�ɓ��B����ׂ��ApDriverLeader_->behave(); �̑O�� pVecDriver->setMvVelo() �Őݒ肵�Ȃ���΂����Ȃ��B
    pDriverLeader_->behave();
    pVecDriver->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //�p���ۂ߂����Ȃ��̂ŃI�[�o�[���C�h
//    if (_was_paused_flg) {
//        GgafDx::GeometricActor::processSettlementBehavior();
//    } else {
        LaserChip::processSettlementBehavior();
//    }
}
void EnemyHisbeLaserChip003::processJudgement() {
    if (pDriverLeader_->isFinished()) {
        sayonara();
    }

    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
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
    GGAF_DELETE(pDriverLeader_);
    pConn_pCurveManuf_->close();
}

