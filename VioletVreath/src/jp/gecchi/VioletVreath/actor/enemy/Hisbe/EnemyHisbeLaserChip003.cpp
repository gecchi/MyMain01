#include "EnemyHisbeLaserChip003.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip003::EnemyHisbeLaserChip003(const char* prm_name) :
        VvEnemyActor<WateringLaserChip>(prm_name, "HisbeLaserChip003", StatusReset(EnemyHisbeLaserChip003)) {
    _class_name = "EnemyHisbeLaserChip003";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip003"); //�S�X�p�[�Ȑ�
    pVehicleLeader_ = createCurveVehicleLeader(pConn_pCurveManuf_->peek());
    pVehicleLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);

    getLocusVehicle()->linkFaceAngByMvAng(true);
    sp_index_ = 0;
}

void EnemyHisbeLaserChip003::onActive() {
    WateringLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pVehicleLeader_->start(RELATIVE_COORD_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
    sp_index_ = 0;
    setVehicleLeader(pVehicleLeader_);
}

void EnemyHisbeLaserChip003::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();

    if (pFeatureScene_) {
        pVehicleLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
    }
    if (sp_index_ > (pVehicleLeader_->_pManufacture->_pCurve->_rnum -1)) {

    } else {
        pLocusVehicle->setMvVelo(pVehicleLeader_->getSegmentDistance(sp_index_));
        sp_index_++;
    }
    //pVehicleLeader_->behave(); ������ pLocusVehicle->_velo_mv ���Q�Ƃ����t���[�������肵�Ă�̂ŁA
    //�P�t���[���Ŏ��̓_�ɓ��B����ׂ��ApVehicleLeader_->behave(); �̑O�� pLocusVehicle->setMvVelo() �Őݒ肵�Ȃ���΂����Ȃ��B
    pVehicleLeader_->behave();
    pLocusVehicle->behave();
    WateringLaserChip::processBehavior();
}
void EnemyHisbeLaserChip003::processSettlementBehavior() {
    //��������_was_paused_flg
//    if (getSceneChief()->getPlatformScene()->_was_paused_flg) {
//        GgafDx::GeometricActor::processSettlementBehavior();
//    } else {
//        LaserChip::processSettlementBehavior();
//    }
    //�p���ۂ߂����Ȃ��̂ŃI�[�o�[���C�h
    LaserChip::processSettlementBehavior();
}

void EnemyHisbeLaserChip003::processJudgement() {
    if (pVehicleLeader_->isFinished()) {
        sayonara();
    }

    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip003::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
    if (is_stamina_zero) {
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
    GGAF_DELETE(pVehicleLeader_);
    pConn_pCurveManuf_->close();
}

