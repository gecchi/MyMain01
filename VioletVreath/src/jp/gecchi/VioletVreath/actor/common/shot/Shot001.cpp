#include "stdafx.h"
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
    _pSeTx->set(0, "WAVE_EXPLOSION_002");
    pSplLineConnection_ = (SplineLineConnection*)(P_GOD->pSpl3DManager_->connect("Spl_HAN", this)); //スプライン定義
    pKurokoLeader_ = NEW FixedVelocitySplineKurokoLeader(_pKuroko, pSplLineConnection_->peek(), 10000); //移動速度固定
}

void Shot001::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, PX_C(16));
    pScaler_->setScale(2000);
    pScaler_->forceRange(2000, 3000);
}

void Shot001::onActive() {
    _pStatus->reset();
    setHitAble(true);
    _pKuroko->relateFaceWithMvAng(true);
    _pKuroko->setMvVelo(RF_Shot001_MvVelo(G_RANK));    //移動速度
    _pKuroko->setFaceAngVelo(AXIS_X, RF_Shot001_AngVelo(G_RANK)); //きりもみ具合
    pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
    pScaler_->beat(30,5,2,-1);
}

void Shot001::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    //座標に反映
    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pKuroko->behave();
    pScaler_->behave();
}

void Shot001::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void Shot001::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;
    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false); //以降同一フレーム内でヒットさせない。
        UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
        _pSeTx->play3D(0);
        if (pOther->getKind() & KIND_MY) { //自機側に撃たれて消滅の場合は
            UTIL::activateItemOf(this); //アイテム出現
        }
        sayonara();
    }

    //_pSeTx->behave();
}


void Shot001::onInactive() {
}


Shot001::~Shot001() {
    GGAF_DELETE(pKurokoLeader_);
    GGAF_DELETE(pScaler_);
    pSplLineConnection_->close();
}
