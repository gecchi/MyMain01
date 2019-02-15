#include "EnemyDelheid.h"

#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/Kuroko.h"
#include "jp/ggaf/dx/actor/supporter/Checker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"



using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_INIT,
    PROG_SPLINE_MOVING,
    PROG_AFTER_LEAD,
    PROG_AFTER_LEAD_MOVING,
    PROG_BANPEI,
};
enum {
    PROG2_WAIT,
    PROG2_OPEN,
    PROG2_SHOT,
    PROG2_CLOSE,
    PROG2_BANPEI,
};
enum {
    MPH_CLOSE,
    MPH_OPEN,
};
enum {
    SE_DAMAGED  ,
    SE_UNDAMAGED,
    SE_EXPLOSION,
};

EnemyDelheid::EnemyDelheid(const char* prm_name) :
        DefaultMassMorphMeshActor(prm_name, "Delheid_1") {
    _class_name = "EnemyDelheid";
    getStatus()->reset(statusResetFunction(EnemyDelheid));
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    pProg2_ = createProgress(PROG2_BANPEI-1);
    shot_begin_frame_ = 0;
    pKurokoLeader_ = nullptr;
    pDepoShot_ = nullptr;
}

void EnemyDelheid::onCreateModel() {
    GgafDx::Model* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyDelheid::nextFrame() {
    DefaultMassMorphMeshActor::nextFrame();
    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
        pProg2_->update();
    }
}

void EnemyDelheid::config(GgafLib::SplineLeader* prm_pKurokoLeader,
                          GgafCore::ActorDepository* prm_pDepoShot  ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepoShot_ = prm_pDepoShot;
}

void EnemyDelheid::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAACube(0, 40000);
    setScaleR(0.3);
}

void EnemyDelheid::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwCriticalException("EnemyDelheidはスプライン必須ですconfigして下さい。this="<<NODE_INFO);
    }
    getStatus()->reset();
    setHitAble(true);
    getMorpher()->reset();
    getProgress()->reset(PROG_INIT);
    pProg2_->reset(PROG2_WAIT);
}

void EnemyDelheid::processBehavior() {
    MyShip* pMyShip = pMYSHIP;

    //移動の状態遷移------------------------------
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(RELATIVE_COORD_DIRECTION, 3); //最高で３回ループする予定
            getKuroko()->setMvAcce(0);
            getKuroko()->keepOnTurningFaceAngTwd(pMYSHIP,
                                                 D_ANG(1), 0, TURN_CLOSE_TO, false);
            pProg->changeNext();
            break;
        }
        case PROG_SPLINE_MOVING: {
            if (pProg->hasJustChanged()) {
            }
            //processJudgement() で pKurokoLeader_->isFinished() 成立待ち
            break;
        }

        //ゴールのアリサナがいない場合、その後の移動
        case PROG_AFTER_LEAD: {
            //processJudgement() で pKurokoLeader_->isFinished() 成立待ち
            break;
        }
        case PROG_AFTER_LEAD_MOVING: {
            //もう2回だけ同じスプライン移動が終わった後の動き
            //isOutOfSpacetime() 成立待ち
            break;
        }
    }

    //ショット発射の状態遷移-----------------------------------
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            //open_shot() 待ち・・・
            break;
        }
        case PROG2_OPEN: {
            if (pProg2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 1.1, 0, 0.001);
            }
            if (!getMorpher()->isTransitioning()) {
                setMorphWeight(MPH_OPEN, 1.0);
                pProg2_->changeNext();
            }
            break;
        }

        case PROG2_SHOT: {
            if (pProg2_->hasJustChanged()) {
                shot_begin_frame_ = RND(120, 240);
            }
            if (pProg2_->hasArrivedAt(shot_begin_frame_)) {
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
            if (pProg2_->hasArrivedAt(240)) {
                pProg2_->changeNext();
            }
            break;
        }
        case PROG2_CLOSE: {
            if (pProg2_->hasJustChanged()) {
                getMorpher()->transitionAcceUntil(MPH_OPEN, 0.0, 0, -0.01);
            }
            if (!getMorpher()->isTransitioning()) {
                pProg2_->changeNothing();
            }

            break;
        }
    }
    //-----------------------------------------------
    GgafDx::Kuroko* const pKuroko = getKuroko();
    pKuroko->_angvelo_face[AXIS_X] = pKuroko->_velo_mv/2;
    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    pKuroko->behave();
    getMorpher()->behave();
}

void EnemyDelheid::processSettlementBehavior() {
    GgafCore::Progress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_SPLINE_MOVING: {
            if (pKurokoLeader_->_cnt_loop >= 2) {
                if (((FormationDelheid*)getFormation())->pAlisana_goal) {
                    //ゴールが存在する場合、１ループでさよなら。
                    pProg->changeNothing();
                    sayonara();
                } else {
                    pProg->change(PROG_AFTER_LEAD);
                }
            }
            break;
        }

        //ゴールのアリサナがいない場合、その後の移動
        case PROG_AFTER_LEAD: {
            if (pKurokoLeader_->isFinished()) {
                //スプライン移動も終わった場合
                pProg->change(PROG_AFTER_LEAD_MOVING);
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

void EnemyDelheid::onHit(const GgafCore::Actor* prm_pOtherActor) {
    if (getMorphWeight(MPH_OPEN) > 0.1) {
        bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDx::GeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊された時(スタミナ <= 0)
            getSeTransmitter()->play3D(SE_EXPLOSION);
            sayonara();
        } else {
            //破壊されなかった時(スタミナ > 0)
            getSeTransmitter()->play3D(SE_DAMAGED);
        }
    } else {
        //開いてないので当たらない
        getSeTransmitter()->play3D(SE_UNDAMAGED);
    }
}

void EnemyDelheid::onInactive() {
}

void EnemyDelheid::open_shot() {
    pProg2_->change(PROG2_OPEN);
}

EnemyDelheid::~EnemyDelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    GGAF_DELETE(pProg2_);
}


