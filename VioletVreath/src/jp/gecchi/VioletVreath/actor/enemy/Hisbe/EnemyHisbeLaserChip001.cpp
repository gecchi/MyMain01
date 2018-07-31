#include "EnemyHisbeLaserChip001.h"

#include "jp/ggaf/core/actor/GgafSceneMediator.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/scene/WalledScene.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHisbeLaserChip001::EnemyHisbeLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "HisbeLaserChip001", STATUS(EnemyHisbeLaserChip001)) {
    _class_name = "EnemyHisbeLaserChip001";
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyHisbeLaserChip002"); //�q���x���g�Ȑ�
    pKurokoLeader_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
    pScrollingScene_ = nullptr;
    getKuroko()->setMvAngByFaceAng();
    getKuroko()->linkFaceAngByMvAng(true);
}

void EnemyHisbeLaserChip001::initialize() {
    registerHitAreaCube_AutoGenMidColli(20000);
    setHitAble(true, false);
    setScaleR(5.0);
    setAlpha(0.9);
}

void EnemyHisbeLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //�X�e�[�^�X���Z�b�g
    getStatus()->reset();
    pScrollingScene_ = ((DefaultScene*)(getMySceneMediator()->getPlatformScene()))->getNearestScrollingScene();
}

void EnemyHisbeLaserChip001::onInactive() {
    HomingLaserChip::onInactive();
    pKurokoLeader_->stop();
}

void EnemyHisbeLaserChip001::processBehaviorHeadChip() {
    if (getActiveFrame() == 1) {
        return;
    }

    if (getActiveFrame() == 2) {
        pKurokoLeader_->start(RELATIVE_COORD_DIRECTION); //�����������Ƀ��[���h�ϊ�
    }
    if (pScrollingScene_) {
        pKurokoLeader_->_x_start_in_loop -= pScrollingScene_->getScrollSpeed();
    }
    pKurokoLeader_->behave();
    getKuroko()->behave();
    if (pKurokoLeader_->isFinished()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbeLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}

EnemyHisbeLaserChip001::~EnemyHisbeLaserChip001() {
    GGAF_DELETE(pKurokoLeader_);
    pConn_pSplManuf_->close();
}

