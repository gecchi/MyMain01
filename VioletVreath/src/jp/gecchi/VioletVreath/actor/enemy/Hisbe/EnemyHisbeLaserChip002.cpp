#include "EnemyHisbeLaserChip002.h"

#include "jp/ggaf/core/actor/SceneMediator.h"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip002::EnemyHisbeLaserChip002(const char* prm_name) :
        VvEnemyActor<RefractionLaserChip>(prm_name, "HisbeLaserChip002", StatusReset(EnemyHisbeLaserChip002)) {
    _class_name = "EnemyHisbeLaserChip002";
    pConn_pCurveManuf_ = connectToCurveManufactureManager("EnemyHisbeLaserChip002"); //�q���x���g�Ȑ�
    pDriverLeader_ = pConn_pCurveManuf_->peek()->createVecDriverLeader(getVecDriver());
    pDriverLeader_->adjustCoordOffset(PX_C(100), 0, 0);
    pFeatureScene_ = nullptr;
    getVecDriver()->setMvAngByFaceAng();
    getVecDriver()->linkFaceAngByMvAng(true);
}

void EnemyHisbeLaserChip002::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setCullingDraw(false);
}

void EnemyHisbeLaserChip002::onActive() {
    RefractionLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pFeatureScene_ = ((DefaultScene*)(getSceneMediator()->getPlatformScene()))->getNearestFeatureScene();
}

void EnemyHisbeLaserChip002::onRefractionInto(int prm_num_refraction)  {

}

void EnemyHisbeLaserChip002::onRefractionOutOf(int prm_num_refraction)  {
    if (prm_num_refraction == 0) {
        pDriverLeader_->start(RELATIVE_COORD_DIRECTION); //���Ă�����ɃX�v���C�����W�����[���h�ϊ�
    }
    pDriverLeader_->behave();
    if (pDriverLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::processBehavior() {
    if (_is_leader) {
        if (pFeatureScene_) {
            pDriverLeader_->_x_start_in_loop -= pFeatureScene_->getFeatureParam1();
        }
    }
    RefractionLaserChip::processBehavior();
}

void EnemyHisbeLaserChip002::processJudgement() {
    if (getActiveFrame() >= getRefractionFinishFrames()) {
        sayonara();
    }
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip002::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

EnemyHisbeLaserChip002::~EnemyHisbeLaserChip002() {
    GGAF_DELETE(pDriverLeader_);
    pConn_pCurveManuf_->close();
}


