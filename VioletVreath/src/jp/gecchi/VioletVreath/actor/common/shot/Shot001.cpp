#include "Shot001.h"

#include "jp/ggaf/dx/actor/supporter/Rikisha.h"
#include "jp/ggaf/dx/actor/supporter/Scaler.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineRikishaLeader.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineManufacture.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/SplineSourceManagerEx.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"


using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        VvEnemyActor<DefaultMassMeshActor>(prm_name, "Flora", StatusReset(Shot001)) {
    _class_name = "Shot001";
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(0, "WAVE_EXPLOSION_002");
    pSplManufConn_ = connectToSplineManufactureManager("Shot001_spline");
    pRikishaLeader_ = NEW FixedVelocitySplineRikishaLeader(pSplManufConn_->peek(), callRikisha()); //�ړ����x�Œ�
}

void Shot001::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(16));
    setScale(2000);
    getScaler()->setRange(2000, 3000);
}

void Shot001::onActive() {
    getStatus()->reset();
    setHitAble(true, false);
    GgafDx::Rikisha* const pRikisha = callRikisha();
    pRikisha->linkFaceAngByMvAng(true);
    pRikisha->setMvVelo(RF_Shot001_MvVelo(G_RANK));    //�ړ����x
    pRikisha->setRollFaceAngVelo(RF_Shot001_AngVelo(G_RANK)); //������݋
    pRikishaLeader_->start(RELATIVE_COORD_DIRECTION);
    getScaler()->beat(30,5,0,2,-1);
//    _TRACE_(FUNC_NAME<<" id=["<<getId()<<"]("<<getActiveFrame()<<") �� = \t"<<callRikisha()->_rz_mv<<"\t"<<callRikisha()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processBehavior() {
//    _TRACE_(FUNC_NAME<<" before id=["<<getId()<<"]("<<getActiveFrame()<<") �� = \t"<<callRikisha()->_rz_mv<<"\t"<<callRikisha()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
    GgafDx::Rikisha* const pRikisha = callRikisha();
    //���W�ɔ��f
    pRikishaLeader_->behave(); //�X�v���C���ړ���U�镑��
    pRikisha->behave();
    getScaler()->behave();
//    _TRACE_(FUNC_NAME<<" after id=["<<getId()<<"]("<<getActiveFrame()<<") �� = \t"<<callRikisha()->_rz_mv<<"\t"<<callRikisha()->_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //�j�󂳂ꂽ��(�X�^�~�i <= 0)
        getSeTransmitter()->play3D(0);
        sayonara();
    } else {
        //�j�󂳂�Ȃ�������(�X�^�~�i > 0)
    }
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    pSplManufConn_->close();
    GGAF_DELETE(pRikishaLeader_);

}
