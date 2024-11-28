#include "EnemyRis.h"

#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRis::EnemyRis(const char* prm_name)
      : VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ris", StatusReset(EnemyRis)) {
    _class_name = "EnemyRis";
    iMovePatternNo_ = 0;
    pVehicleLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
}

void EnemyRis::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.9);
    pModel->getTexBlinker()->setRange(0.5, 2.0);
    pModel->getTexBlinker()->beat(60, 3, 0, 57, -1);
}

void EnemyRis::initialize() {
    setHitAble(true);
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->linkFaceAngByMvAng(true);
    pLocusVehicle->setRollFaceAngVelo(5000);
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyRis::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyRis::processBehavior() {
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    switch (iMovePatternNo_) {
        case 0:  //【パターン０：カーブ移動開始】
            if (pVehicleLeader_) {
                pVehicleLeader_->start(ABSOLUTE_COORD); //カーブ移動を開始
            }
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：カーブ移動終了待ち】
            if (pVehicleLeader_) {
                //カーブ移動有り
                if (pVehicleLeader_->isFinished()) {
                    iMovePatternNo_++; //カーブ移動が終了したら次の行動パターンへ
                }
            } else {
                //カーブ移動無し
                iMovePatternNo_++; //すぐに次の行動パターンへ
            }
            break;

        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
            if (pDepo_shot_) {
                //放射状ショット
                int way = RF_EnemyRis_ShotWay(G_RANK); //ショットWAY数
                UTIL::shotWay004(_x, _y, _z,
                                 D180ANG, D0ANG,
                                 pDepo_shot_,
                                 PX_C(20), way, D_ANG(120),
                                 0, 0,  //ショット側で速度を設定
                                 1, 0, 1.0,
                                 nullptr );
                //ショット発射エフェクト
                if (pDepo_effect_) {
                    GgafDx::FigureActor* pTestActor_Shot = (GgafDx::FigureActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->setPositionAt(this);
                    }
                }
            }
            //自機へ方向転換
            pLocusVehicle->turnMvAngTwd(pMYSHIP,
                                  3000, 0,
                                  TURN_CLOSE_TO, true);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３：自機へグルッと逆回転で方向転換開始】
            if (_z-10000 < pMYSHIP->_z && pMYSHIP->_z < _z+10000) {
                //自機とZ軸が接近したらグルッと逆回転で方向転換
                pLocusVehicle->turnMvAngTwd(MyShip::lim_x_behaind_ - 500000 , _y, _z,
                                      10000, 0,
                                      TURN_CLOSE_TO, true);
                pLocusVehicle->setMvAcce(100);
                iMovePatternNo_++;
            } else {
                //自機とZ軸が接近するまで待つ
            }
            break;
        default:
            break;
    }


    if (pVehicleLeader_) {
        pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作
    }
    pLocusVehicle->behave();
    //getSeXmtr()->behave();
}

void EnemyRis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyRis::onInactive() {
    sayonara();
}

EnemyRis::~EnemyRis() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
}
