#include "EnemyEres.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/core/actor/GgafGroupHead.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/FixedVelocitySplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEresShot001.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"

#include "jp/gecchi/VioletVreath/Properties.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEres::EnemyEres(const char* prm_name, GgafActorDepository* prm_pDepo_EnemyEresShots001) :
        DefaultMeshSetActor(prm_name, "Eres", STATUS(EnemyEres)) {
    _class_name = "EnemyEres";
    iMovePatternNo_ = 0;
    _x = -356000; //開始座標
    _y = 0;
    _z = -680000;
    X_turn_ = (PX_C(PROPERTY::GAME_BUFFER_WIDTH) / 2) - 30000;
    Y_turn_ = -10000;
    Z_turn_ = 0;

    if (prm_pDepo_EnemyEresShots001 == nullptr) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        pDepo_shot001_ = NEW GgafActorDepository("Depo_EnemyEresShots");
        for (int i = 0; i < 32; i++) {
            pDepo_shot001_->put(NEW EnemyEresShot001("EnemyEresShot"));
        }
        addSubGroup(pDepo_shot001_);
        createGgafActorDepository_ = true;
    } else {
        //共有の弾が指定されてるの場合
        pDepo_shot001_ = prm_pDepo_EnemyEresShots001;
        createGgafActorDepository_ = false;
    }

    pSplLineConnection_ = connectToSplineLineManager("Spl_001");
    pKurokoLeader_ = NEW FixedVelocitySplineKurokoLeader(getKuroko(), pSplLineConnection_->peek(), 5000); //移動速度固定

//    pKurokoLeader_ = NEW FixedFrameSplineKurokoLeader(getKuroko(), pSplLineConnection_->peek(), 600, 5000); //移動フレーム数固定
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
}

void EnemyEres::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -30000, -30000, 30000, 30000);
}

void EnemyEres::onActive() {
    setHitAble(true);
    getStatus()->reset();
    iMovePatternNo_ = 0;
    frame_Active_ = 0;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(6000);
    pKuroko->setMvVelo(8000);
    pKurokoLeader_->start(ABSOLUTE_COORD); //スプライン移動を開始
    frame_Active_ = 0;
}

void EnemyEres::processBehavior() {
    //方向転換
    if (iMovePatternNo_ == 0 && _x > 400000) {

        angle way[32];
        //UTIL::getWayAngle2D(180000, 8, 10000, way);
        UTIL::getRadialAngle2D(0, 32, way); //TODO:毎回求めるのは無駄
        GgafDxFigureActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDxFigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPosition(_x, _y, _z);
                pTama->getKuroko()->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDxFigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPosition(_x, _y, _z);
                pTama->getKuroko()->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pKurokoLeader_->behave(); //スプライン移動を進める
    getKuroko()->behave(); //次の座標へ移動
    //getSeTransmitter()->behave();
    frame_Active_++;
}

void EnemyEres::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEres::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyEres::onInactive() {
    if (createGgafActorDepository_) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getMySceneDirector()->addSubLast(pDepo_shot001_->getMyGroupHead()->extract());
        pDepo_shot001_->sayonara(60 * 5);//解放予約
    }
    sayonara();
}

bool EnemyEres::isOutOfSpacetime() const {
    if (_x < (PX_C(PROPERTY::GAME_BUFFER_WIDTH) / -2) - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyEres::~EnemyEres() {
    //staticなので最初の１回だけ解放したい
    pSplLineConnection_->close();
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

