#include "EnemyDelheid.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/LocusVehicle.h"
#include "jp/ggaf/dx/util/CollisionChecker.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

using namespace GgafDx;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PHASE_INIT,
    PHASE_CURVE_MOVING,
    PHASE_AFTER_LEAD,
    PHASE_AFTER_LEAD_MOVING,
    PHASE_BANPEI,
};
enum {
    PHASE2_WAIT,
    PHASE2_OPEN,
    PHASE2_SHOT,
    PHASE2_CLOSE,
    PHASE2_BANPEI,
};
enum {
    MPH_CLOSE,
    MPH_OPEN,
};
enum {
    SE_UNDAMAGED,
};

EnemyDelheid::EnemyDelheid(const char* prm_name) :
        VvEnemyActor<DefaultMassMorphMeshActor>(prm_name, "Delheid", StatusReset(EnemyDelheid)) {
    _class_name = "EnemyDelheid";
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(SE_UNDAMAGED, "SE_ENEMY_UNDAMAGED_001");
    pPhase2_ = createAnotherPhase();
    shot_begin_frame_ = 0;
    pVehicleLeader_ = nullptr;
    pDepoShot_ = nullptr;
}

void EnemyDelheid::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}
//ここだめ_was_paused_flg？？？

//void EnemyDelheid::nextFrame() {
//    DefaultMassMorphMeshActor::nextFrame();
//    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
//        pProg2_->update();
//    }
//}
void EnemyDelheid::processNextFrame() {
    DefaultMassMorphMeshActor::processNextFrame();

//    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
    if (_is_active_in_the_tree_flg) {
        pPhase2_->update();
    }
}

void EnemyDelheid::config(GgafDx::CurveManufacture* prm_pCurveManufacture,
                          GgafCore::ActorDepository* prm_pDepoShot  ) {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    pVehicleLeader_ = createCurveVehicleLeader(prm_pCurveManufacture);
    pDepoShot_ = prm_pDepoShot;
}

void EnemyDelheid::initialize() {
    WorldCollisionChecker* pChecker = getWorldCollisionChecker();
    pChecker->addCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    setScaleR(0.3);
}

void EnemyDelheid::onActive() {
    if (pVehicleLeader_ == nullptr) {
        throwCriticalException("EnemyDelheidはスプライン必須ですconfigして下さい。this="<<NODE_INFO);
    }
    getStatus()->reset();
    setHitAble(true);
    getMorpher()->reset();
    getPhase()->reset(PHASE_INIT);
    pPhase2_->reset(PHASE2_WAIT);
}

void EnemyDelheid::processBehavior() {
    MyShip* pMyShip = pMYSHIP;

    //移動のフェーズ------------------------------
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pVehicleLeader_->start(RELATIVE_COORD_DIRECTION, 3); //最高で３回ループする予定
            getLocusVehicle()->setMvAcce(0);
            getLocusVehicle()->keepOnTurningFaceAngTwd(pMYSHIP,
                                                    D_ANG(1), 0, TURN_CLOSE_TO, false);
            pPhase->changeNext();
            break;
        }
        case PHASE_CURVE_MOVING: {
            if (pPhase->hasJustChanged()) {
            }
            //processJudgement() で pVehicleLeader_->isFinished() 成立待ち
            break;
        }

        //ゴールのアリサナがいない場合、その後の移動
        case PHASE_AFTER_LEAD: {
            //processJudgement() で pVehicleLeader_->isFinished() 成立待ち
            break;
        }
        case PHASE_AFTER_LEAD_MOVING: {
            //もう2回だけ同じカーブ移動が終わった後の動き
            //isOutOfSpacetime() 成立待ち
            break;
        }
    }

    //ショット発射のフェーズ-----------------------------------
    switch (pPhase2_->getCurrent()) {
        case PHASE2_WAIT: {
            //open_shot() 待ち・・・
            break;
        }
        case PHASE2_OPEN: {
            if (pPhase2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 1.1, 0, 0.001);
            }
            if (!getMorpher()->isTransitioning()) {
                setMorphWeight(MPH_OPEN, 1.0);
                pPhase2_->changeNext();
            }
            break;
        }

        case PHASE2_SHOT: {
            if (pPhase2_->hasJustChanged()) {
                shot_begin_frame_ = RND(120, 240);
            }
            if (pPhase2_->hasArrivedFrameAt(shot_begin_frame_)) {
                UTIL::shotWay002(
                       this,
                       pDepoShot_,
                       PX_C(20),     //r
                       5,            //way数
                       D_ANG(10),    //wayとwayの間隔
                       PX_C(5),      //初期速度
                       100,          //加速度
                       2,            //wayのセット数
                       0,            //セットとセットの間隔フレーム
                       0.8f,         //セット増加に伴う初期速度減衰率
                       nullptr
                     );
            }
            if (pPhase2_->hasArrivedFrameAt(240)) {
                pPhase2_->changeNext();
            }
            break;
        }
        case PHASE2_CLOSE: {
            if (pPhase2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 0.0, 0, -0.01);
            }
            if (!getMorpher()->isTransitioning()) {
                pPhase2_->changeNothing();
            }

            break;
        }
    }
    //-----------------------------------------------
    GgafDx::LocusVehicle* pLocusVehicle = getLocusVehicle();
    pLocusVehicle->_angvelo_face[AXIS_X] = pLocusVehicle->_velo_mv/2;
    pVehicleLeader_->behave(); //カーブ移動するようにDriverを操作
    pLocusVehicle->behave();
    getMorpher()->behave();
}

void EnemyDelheid::processSettlementBehavior() {
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_CURVE_MOVING: {
            if (pVehicleLeader_->_cnt_loop >= 2) {
                if (((FormationDelheid*)getFormation())->pAlisana_goal) {
                    //ゴールが存在する場合、１ループでさよなら。
                    pPhase->changeNothing();
                    sayonara();
                } else {
                    pPhase->change(PHASE_AFTER_LEAD);
                }
            }
            break;
        }

        //ゴールのアリサナがいない場合、その後の移動
        case PHASE_AFTER_LEAD: {
            if (pVehicleLeader_->isFinished()) {
                //カーブ移動も終わった場合
                pPhase->change(PHASE_AFTER_LEAD_MOVING);
            }
            break;
        }
    }
    DefaultMassMorphMeshActor::processSettlementBehavior();
}

void EnemyDelheid::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyDelheid::onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) {
    if (getMorphWeight(MPH_OPEN) > 0.1) {
        bool is_stamina_zero = performEnemyHit((const GgafDx::GeometricActor*)prm_pOtherActor);
        if (is_stamina_zero) {
            //破壊された時(スタミナ <= 0)
            sayonara();
        } else {
            //破壊されなかった時(スタミナ > 0)
        }
    } else {
        //開いてないので当たらない
        getSeXmtr()->play3D(SE_UNDAMAGED);
    }
}

void EnemyDelheid::onInactive() {
}

void EnemyDelheid::open_shot() {
    pPhase2_->change(PHASE2_OPEN);
}

EnemyDelheid::~EnemyDelheid() {
    GGAF_DELETE_NULLABLE(pVehicleLeader_);
    GGAF_DELETE(pPhase2_);
}

