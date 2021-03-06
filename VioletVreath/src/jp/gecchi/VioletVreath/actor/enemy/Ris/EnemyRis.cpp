#include "EnemyRis.h"

#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/model/supporter/TextureBlinker.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    SE_EXPLOSION,
};

EnemyRis::EnemyRis(const char* prm_name)
      : VvEnemyActor<DefaultMeshSetActor>(prm_name, "Ris", StatusReset(EnemyRis)) {
    _class_name = "EnemyRis";
    iMovePatternNo_ = 0;
    pDriverLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
}

void EnemyRis::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.9);
    pModel->getTexBlinker()->setRange(0.5, 2.0);
    pModel->getTexBlinker()->beat(60, 3, 0, 57, -1);
}

void EnemyRis::initialize() {
    setHitAble(true);
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    pVecDriver->linkFaceAngByMvAng(true);
    pVecDriver->setRollFaceAngVelo(5000);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyRis::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyRis::processBehavior() {
    GgafDx::VecDriver* const pVecDriver = getVecDriver();
    switch (iMovePatternNo_) {
        case 0:  //【パターン０：カーブ移動開始】
            if (pDriverLeader_) {
                pDriverLeader_->start(ABSOLUTE_COORD); //カーブ移動を開始
            }
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：カーブ移動終了待ち】
            if (pDriverLeader_) {
                //カーブ移動有り
                if (pDriverLeader_->isFinished()) {
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
            pVecDriver->turnMvAngTwd(pMYSHIP,
                                  3000, 0,
                                  TURN_CLOSE_TO, true);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３：自機へグルッと逆回転で方向転換開始】
            if (_z-10000 < pMYSHIP->_z && pMYSHIP->_z < _z+10000) {
                //自機とZ軸が接近したらグルッと逆回転で方向転換
                pVecDriver->turnMvAngTwd(MyShip::lim_x_behaind_ - 500000 , _y, _z,
                                      10000, 0,
                                      TURN_CLOSE_TO, true);
                pVecDriver->setMvAcce(100);
                iMovePatternNo_++;
            } else {
                //自機とZ軸が接近するまで待つ
            }
            break;
        default:
            break;
    }


    if (pDriverLeader_) {
        pDriverLeader_->behave(); //カーブ移動するようにDriverを操作
    }
    pVecDriver->behave();
    //getSeTransmitter()->behave();
}

void EnemyRis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyRis::onHit(const GgafCore::Actor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyRis::onInactive() {
    sayonara();
}

EnemyRis::~EnemyRis() {
    GGAF_DELETE_NULLABLE(pDriverLeader_);
}
