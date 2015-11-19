#include "EnemyOzartia.h"

#include "EnemyOzartiaShot01.h"
#include "EnemyOzartiaLaserChip01.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"

#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define D_MOVE (PX_C(500))
#define ASOBI (RND(-30,30))
EnemyOzartia::EnemyOzartia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ozartia", STATUS(EnemyOzartia)) {
    _class_name = "EnemyOzartia";
    pAFader_ = NEW GgafDxAlphaFader(this);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI1_-1);
    pProg2_ = createProgress(PROG2_BANPEI-1);
    is_hit_ = false;
    pConn_pSplManuf_ = connectToSplineManufactureManager("EnemyOzartia01_TTT");
    pKurokoLeader01_ = pConn_pSplManuf_->peek()->createKurokoLeader(getKuroko());
//    //バリアブロック
//    pDepo_shot01_ = NEW GgafActorDepository("Depo_OzartiaBlock");
//    for (int i = 0; i < 9; i++) {
//        std::string name = "EnemyOzartiaShot01["+XTOS(i)+"]";
//        pDepo_shot01_->put(NEW EnemyOzartiaShot01(name.c_str()));
//        Sleep(1);
//    }
//    addSubGroup(pDepo_shot01_);
//
//    pDepo_shot02_ = NEW LaserChipDepository("MyRotLaser");
//    pDepo_shot02_->config(60, 1, nullptr); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
//    EnemyOzartiaLaserChip01* pChip;
//    for (int i = 0; i < 65; i++) { //レーザーストック
//        std::string name = "EnemyOzartiaLaserChip01["+XTOS(i)+"]";
//        pChip = NEW EnemyOzartiaLaserChip01(name.c_str());
//        pChip->setSource(this); //位置向き同期
//        pDepo_shot02_->put(pChip);
//    }
//    addSubGroup(pDepo_shot02_);
    faceang_to_ship_ = false;
    effectBlendOne(); //加算合成
}

void EnemyOzartia::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
}

void EnemyOzartia::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAAB_Cube(0, 40000);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(PX_C(1), PX_C(30));
    pKuroko->linkFaceAngByMvAng(false); //独立
    setHitAble(false);
}

void EnemyOzartia::onActive() {
    getStatus()->reset();
    getProgress()->reset(PROG1_INIT);
    pProg2_->reset(PROG2_WAIT);
    faceang_to_ship_ = false;
}

void EnemyOzartia::processBehavior() {
    MyShip* pMyShip = P_MYSHIP;
    //本体移動系の処理 ここから --->
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG1_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->setMvAngTwd(pMyShip);
            pProg->changeNext();
            break;
        }
        case PROG1_ENTRY: {
            EffectBlink* pEffectEntry = nullptr;
            if (pProg->hasJustChanged()) {
                pEffectEntry = UTIL::activateEntryEffectOf(this);
            }
            static const frame frame_of_summons = pEffectEntry->getFrameOfSummonsBegin();
            static const frame summoning_frames = pEffectEntry->getSummoningFrames();
            if (pProg->hasArrivedAt(frame_of_summons)) {
                pAFader_->transitionLinerUntil(1.0, summoning_frames);
            }
            if (pProg->hasArrivedAt(frame_of_summons + summoning_frames)) {
                setHitAble(true);
                pProg->change(PROG1_STAY);
            }
            break;
        }
        case PROG1_STAY: {
            if (pProg->hasJustChanged()) {
                faceang_to_ship_ = true;
                pKuroko->setMvAcce(0);
                pKuroko->turnMvAngTwd(pMyShip, D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (is_hit_ || pProg->hasArrivedAt(4*60)) {
                //ヒットするか、しばらくボーっとしてると移動開始
                pProg->changeProbab(18, PROG1_MV_POS0,
                                    16, PROG1_MV_POS1,
                                    16, PROG1_MV_POS2,
                                    16, PROG1_MV_POS3,
                                    16, PROG1_MV_POS4,
                                    18, PROG1_MV_POS5 );
            }
            break;
        }
        //////////// 通常移動先決定 ////////////
        case PROG1_MV_POS0: {
            //自機の正面付近へ
            posMvTarget_.set(pMyShip->_x + D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS1: {
            //自機の上
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y + D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS2: {
            //自機の右
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z - D_MOVE + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS3: {
            //自機の下
            posMvTarget_.set(pMyShip->_x            + ASOBI,
                             pMyShip->_y - D_MOVE/2 + ASOBI,
                             pMyShip->_z            + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS4: {
            //自機の左
            posMvTarget_.set(pMyShip->_x          + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z + D_MOVE + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        case PROG1_MV_POS5: {
            //自機の後ろ
            posMvTarget_.set(pMyShip->_x - D_MOVE + ASOBI,
                             pMyShip->_y          + ASOBI,
                             pMyShip->_z          + ASOBI );
            pProg->change(PROG1_MOVE_START);
            break;
        }
        //////////// 通常移動開始 ////////////
        case PROG1_MOVE_START: {
            if (pProg->hasJustChanged()) {
                //ターン
                faceang_to_ship_ = false;
                pKuroko->setMvVeloBottom();
                pKuroko->setMvAcce(10); //微妙に加速
                pKuroko->turnMvAngTwd(&posMvTarget_, D_ANG(2), 0, TURN_CLOSE_TO, false);
            }
            if (!pKuroko->isTurningMvAng()) {
                //ターンしたら移動へ
                pProg->change(PROG1_MOVING);
            }
            break;
        }
        case PROG1_MOVING: {
            if (pProg->hasJustChanged()) {
                //自機の正面付近へスイーっと行きます
                pKuroko->asstMv()->slideByVd(pKuroko->getMvVeloTop(), UTIL::getDistance(this, &posMvTarget_),
                                       0.3, 0.7, pKuroko->getMvVeloBottom(), true);
            }
            if (!pKuroko->asstMv()->isSliding()) {
                //到着したら終了
                pProg->change(PROG1_STAY);
            }
            break;
        }
        //////////// 特殊移動開始 ////////////
        case PROG1_SP_MV01: {
            if (pProg->hasJustChanged()) {
                pKuroko->setMvAngTwd(pMyShip);
                pKurokoLeader01_->start(RELATIVE_COORD_DIRECTION, 10); //10回
            }
            if (pKurokoLeader01_->isFinished()) {
                pProg->change(PROG1_STAY);
            }
            break;
        }
        //////////// 時間切れ退出 ////////////
        case PROG1_LEAVE: {
            if (pProg->hasJustChanged()) {
                UTIL::activateLeaveEffectOf(this);
                pAFader_->transitionLinerUntil(0.0, 30);
            }
            if (pProg->hasArrivedAt(60)) {
                sayonara();
                pProg->changeNothing(); //おしまい！
            }
            break;
        }
        default :
            break;
    }
    //<-- 本体移動系の処理 ここまで

    //////////////////////////////////////////////////////////////////////

    //ショット発射系処理 ここから --->
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            if (pProg->hasJustChanged()) {
            }
            break;
        }
        case PROG2_SHOT01_01: {
            if (pProg->hasJustChanged()) {
                faceang_to_ship_ = true;
                getMorpher()->transitionLinerUntil(MPH_SHOT01, 1.0, 120);
            }
            if (pProg->hasArrivedAt(120)) {
                pProg->change(PROG2_SHOT01_02);
            }
            break;
        }
        default :
            break;
    }
    pProg2_->update();
    //<-- ショット発射系処理 ここまで

    if (faceang_to_ship_) {
        //自機向きモード
        if (!pKuroko->isTurningFaceAng()) {
            pKuroko->turnFaceAngTwd(pMyShip, D_ANG(5), 0, TURN_CLOSE_TO, false);
        }
    } else {
        //進行方向向きモード
        if (!pKuroko->isTurningFaceAng()) {
            pKuroko->turnRzRyFaceAngTo(pKuroko->_ang_rz_mv,pKuroko->_ang_ry_mv,
                                          D_ANG(2), 0, TURN_CLOSE_TO, false);
        }
    }

    pAFader_->behave();
    pKurokoLeader01_->behave();
    pKuroko->behave();
    is_hit_ = false;
}

void EnemyOzartia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyOzartia::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
    is_hit_ = true;
}

void EnemyOzartia::onInactive() {
    sayonara();
}

EnemyOzartia::~EnemyOzartia() {
    GGAF_DELETE(pKurokoLeader01_);
    pConn_pSplManuf_->close();
    GGAF_DELETE(pAFader_);
    GGAF_DELETE(pProg2_);
}

