#include "EnemyEres.h"

#include "jp/ggaf/core/actor/SceneChief.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveCoordVehicleLeader.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveLocusVehicleLeader.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eres/EnemyEresShot001.h"
#include "jp/ggaf/dx/util/curve/FixedFrameCurveManufacture.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/Config.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEres::EnemyEres(const char* prm_name, GgafCore::ActorDepository* prm_pDepo_EnemyEresShots001) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, "Eres", StatusReset(EnemyEres)) {
    _class_name = "EnemyEres";
    iMovePatternNo_ = 0;
    _x = PX_C(-100); //開始座標
    _y = 0;
    _z = 0;
    if (prm_pDepo_EnemyEresShots001 == nullptr) {
        //共有の弾が引数に未指定の場合
        //弾ストック作成
        pDepo_shot001_ = NEW GgafCore::ActorDepository("Depo_EnemyEresShots");
        for (int i = 0; i < 32; i++) {
            pDepo_shot001_->put(NEW EnemyEresShot001("EnemyEresShot"));
        }
        appendChild(pDepo_shot001_);
        createActorDepository_ = true;
    } else {
        //共有の弾が指定されてるの場合
        pDepo_shot001_ = prm_pDepo_EnemyEresShots001;
        createActorDepository_ = false;
    }

    pCurveManufConn_ = connectToCurveManufactureManager("EnemyEres_curve");
    pVehicleLeader_ = createCurveVehicleLeader(pCurveManufConn_->peek());
//    ((FixedFrameCurveCoordVehicleLeader*)pVehicleLeader_)->setGravitationParam(200, PX_C(100));

    getModel()->setSpecular(8.0, 2.0);
}

void EnemyEres::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, PX_C(60));
}

void EnemyEres::onActive() {
    setHitAble(true);
    getStatus()->reset();
    iMovePatternNo_ = 0;
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(2000);
//    pLocusVehicle->setMvVelo(3000);
    pVehicleLeader_->start(RELATIVE_COORD); //カーブ移動を開始
}

void EnemyEres::processBehavior() {
    //方向転換
    if (iMovePatternNo_ == 0 && getActiveFrame() == 60*30) {

        angle way[32];
        //UTIL::getWayAngleArr(180000, 8, 10000, way);
        UTIL::getRadialAngleArr(0, 32, way); //TODO:毎回求めるのは無駄
        GgafDx::FigureActor* pTama;
        for (int i = 0; i < 16; i++) {
            pTama = (GgafDx::FigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPositionAt(this);
                pTama->getLocusVehicle()->setRzRyMvAng(-D90ANG + way[i], D90ANG);
            }
        }
        for (int i = 16; i < 32; i++) {
            pTama = (GgafDx::FigureActor*)pDepo_shot001_->dispatch();
            if (pTama) {
                pTama->setPositionAt(this);
                pTama->getLocusVehicle()->setRzRyMvAng(-D90ANG - way[i], -D90ANG);
            }
        }

        iMovePatternNo_++;
    }
    pVehicleLeader_->behave(); //カーブ移動を進める
    getCoordVehicle()->behave();
    getLocusVehicle()->behave(); //次の座標へ移動
    //getSeXmtr()->behave();
}

void EnemyEres::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEres::onInactive() {
    if (createActorDepository_) {
        //弾は遅れて開放させるように、動きを継続させるため移動
        getSceneChief()->appendChild(pDepo_shot001_->extract());
        pDepo_shot001_->sayonara(SEC_F(5));//解放予約
    }
    sayonara();
}

bool EnemyEres::isOutOfSpacetime() const {
    if (_x < (PX_C(CONFIG::GAME_BUFFER_WIDTH) / -2) - 20000000) {
        return true;
    } else {
        return false;
    }
}

EnemyEres::~EnemyEres() {
    //staticなので最初の１回だけ解放したい
    pCurveManufConn_->close();
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}

