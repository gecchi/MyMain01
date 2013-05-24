#include "stdafx.h"
#include "EnemyCeres.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/EnemyCeresShot001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyCeres::EnemyCeres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyCeresShots001) :
        DefaultMeshSetActor(prm_name, "Ceres", STATUS(EnemyCeres)) {
    _class_name = "EnemyCeres";
    iMovePatternNo_ = 0;
    _X = -356000; //開始座標
    _Y = 0;
    _Z = -680000;
    X_turn_ = P_CAM->_X_buffer_right - 30000;
    Y_turn_ = -10000;
    Z_turn_ = 0;

    if (prm_pDepo_EnemyCeresShots001 == nullptr) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        pDepo_EnemyCeresShots001_ = NEW GgafActorDepository("RotEnemyMeshS001");
        EnemyCeresShot001* pCeresShot001;
        for (int i = 0; i < 32; i++) {
            pCeresShot001 = NEW EnemyCeresShot001("EnemyMeshShot");
            pCeresShot001->inactivateTreeImmed(); //最初非表示
            pDepo_EnemyCeresShots001_->addSubLast(pCeresShot001);
        }
        addSubGroup(pDepo_EnemyCeresShots001_);
        createGgafActorDepository_ = true;
    } else {
        //共有の弾が指定されてるの場合
        pDepo_EnemyCeresShots001_ = prm_pDepo_EnemyCeresShots001;
        createGgafActorDepository_ = false;
    }

    pSplLineConnection_ = connectToSplineLineManager("Spl_001");
    pProgram_CeresMove_ = NEW FixedVelocitySplineKurokoLeader(_pKurokoA, pSplLineConnection_->peek(), 5000); //移動速度固定

//    pProgram_CeresMove_ = NEW FixedFrameSplineKurokoLeader(_pKurokoA, pSplLineConnection_->peek(), 600, 5000); //移動フレーム数固定
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyCeres::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB(0, -30000, -30000, 30000, 30000);
}

void EnemyCeres::onActive() {
    setHitAble(true);
    _pStatus->reset();
    iMovePatternNo_ = 0;
    frame_Active_ = 0;
    _pKurokoA->relateMvFaceAng(true);
    _pKurokoA->setFaceAngVelo(AXIS_X, 6000);
    _pKurokoA->setMvVelo(8000);
    pProgram_CeresMove_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動を開始
    frame_Active_ = 0;
}

void EnemyCeres::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //方向転換
    if (iMovePatternNo_ == 0 && _X > 400000) {

        angle way[32];
        //UTIL::getWayAngle2D(180000, 8, 10000, way);
        UTIL::getRadialAngle2D(0, 32, way); //TODO:毎回求めるのは無駄
        GgafDxDrawableActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyCeresShots001_->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxDrawableActor*)pDepo_EnemyCeresShots001_->dispatch();
            if (pTama) {
                pTama->locate(_X, _Y, _Z);
                pTama->_pKurokoA->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pProgram_CeresMove_->behave(); //スプライン移動を進める
    _pKurokoA->behave(); //次の座標へ移動
    //_pSeTx->behave();
    frame_Active_++;
}

void EnemyCeres::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}


void EnemyCeres::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyCeres::onInactive() {
    if (createGgafActorDepository_) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getSceneDirector()->addSubLast(pDepo_EnemyCeresShots001_->getMyGroupHead()->extract());
        pDepo_EnemyCeresShots001_->sayonara(60 * 5);//解放予約
    }
    sayonara();
}

bool EnemyCeres::isOutOfUniverse() {
    if (_X < P_CAM->_X_buffer_left - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyCeres::~EnemyCeres() {
    //staticなので最初の１回だけ解放したい
    pSplLineConnection_->close();
    GGAF_DELETE_NULLABLE(pProgram_CeresMove_);
}
