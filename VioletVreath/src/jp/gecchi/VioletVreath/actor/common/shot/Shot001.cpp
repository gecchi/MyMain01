#include "Shot001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

Shot001::Shot001(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Flora", STATUS(Shot001)) {
    _class_name = "Shot001";
    pScaler_ = NEW GgafDxScaler(this);

    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(0, "WAVE_EXPLOSION_002");

    pSplLineConnection_ = getConnection_SplineLineManager("Spl_HAN"); //スプライン定義
    pKurokoLeader_ = NEW FixedVelocitySplineKurokoLeader(getKuroko(), pSplLineConnection_->peek(), 10000); //移動速度固定
}

void Shot001::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB_Cube(0, PX_C(16));
    setScale(2000);
    pScaler_->setRange(2000, 3000);
}

void Shot001::onActive() {
    getStatus()->reset();
    setHitAble(true);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setMvVelo(RF_Shot001_MvVelo(G_RANK));    //移動速度
    pKuroko->setRollFaceAngVelo(RF_Shot001_AngVelo(G_RANK)); //きりもみ具合
    pKurokoLeader_->start(RELATIVE_COORD_DIRECTION);
    pScaler_->beat(30,5,0,2,-1);
//    _TRACE_("Shot001::onActive() id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getKuroko()->_ang_rz_mv<<"\t"<<getKuroko()->_ang_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processBehavior() {
//    _TRACE_("Shot001::processBehavior() before id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getKuroko()->_ang_rz_mv<<"\t"<<getKuroko()->_ang_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
    GgafDxKuroko* const pKuroko = getKuroko();
    //座標に反映
    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    pKuroko->behave();
    pScaler_->behave();
//    _TRACE_("Shot001::processBehavior() after id=["<<getId()<<"]("<<getActiveFrame()<<") → = \t"<<getKuroko()->_ang_rz_mv<<"\t"<<getKuroko()->_ang_ry_mv<<"\t\t\t"<<_x<<"\t"<<_y<<"\t"<<_z<<"");
}

void Shot001::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void Shot001::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(0);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    GGAF_DELETE(pKurokoLeader_);
    GGAF_DELETE(pScaler_);
    pSplLineConnection_->close();
}
