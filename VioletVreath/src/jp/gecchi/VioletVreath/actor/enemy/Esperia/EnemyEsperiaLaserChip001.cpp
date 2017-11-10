#include "EnemyEsperiaLaserChip001.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyEsperiaLaserChip001::EnemyEsperiaLaserChip001(const char* prm_name) :
        HomingLaserChip(prm_name, "EsperiaLaserChip001", STATUS(EnemyEsperiaLaserChip001)) {
    _class_name = "EnemyEsperiaLaserChip001";
    tx1_ = ty1_ = tz1_ = 0;
    tx2_ = ty2_ = tz2_ = 0;
    begin_y_ = 0;
    turn_dy_ = 0;
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_FIRE , "WAVE_ENEMY_FIRE_LASER_001");
}

void EnemyEsperiaLaserChip001::initialize() {
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 20000);
    setHitAble(true, false);
    setScaleR(5.0);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->forceMvVeloRange(PX_C(100));
    pKuroko->linkFaceAngByMvAng(true);
    useProgress(PROG_BANPEI);
}

void EnemyEsperiaLaserChip001::onActive() {
    HomingLaserChip::onActive();
    //ステータスリセット
    getStatus()->reset();
    begin_y_ = _y;
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->stopTurningMvAng();
    if (getInfrontChip() == nullptr) {
        pKuroko->setMvAngTwd(tx1_, ty1_, tz1_);
        getProgress()->reset(PROG_MOVE_UP);
    } else {
        getProgress()->reset(PROG_NOTHING);
    }
    setAlpha(0.99);
    //次のメンバーは EnemyEsperia 本体側から設定済みが前提
    //turn_dy_;
    //tx1_, ty1_, tz1_;
    //tx2_, ty2_, tz2_;
}

void EnemyEsperiaLaserChip001::processBehaviorHeadChip() {
    MyShip* pMyShip = pMYSHIP;
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE_UP: {
            //レーザー上昇
            if (!pKuroko->isTurningMvAng()) {

                //補正
                pKuroko->turnMvAngTwd(tx1_, ty1_, tz1_,
                                      D_ANG(5), 0,
                                      TURN_CLOSE_TO, false);
            }
            if (_y > begin_y_+turn_dy_ || pProg->getFrame() > 300) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_TURN1: {
            //自機より少し上の座標で屈折
            if (pProg->hasJustChanged()) {
                pKuroko->setMvVelo(pKuroko->_velo_mv/3); //屈折時少しスローダウン
                pKuroko->turnMvAngTwd(tx2_, ty2_, tz2_,
                                      D_ANG(10), 0,
                                      TURN_CLOSE_TO, false);
            }
            if (!pKuroko->isTurningMvAng() || pProg->getFrame() > 300) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_TURN2: {
            //屈折補正
            if (pProg->getFrame() % 8U == 0) {
                pKuroko->turnMvAngTwd(tx2_, ty2_, tz2_,
                                      D_ANG(5), 0,
                                      TURN_CLOSE_TO, false);
                pKuroko->setMvVelo(pKuroko->_velo_mv*2);
            }
            if (pProg->getFrame() > 60) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_INTO_MYSHIP: {
            if (pProg->hasJustChanged()) {
                getSeTransmitter()->play3D(SE_FIRE);
            }
            if (pProg->getFrame() % 16U == 0) {
                pKuroko->turnMvAngTwd(tx2_, ty2_, tz2_,
                                      100, 0,
                                      TURN_CLOSE_TO, false);
            }
            if (pProg->getFrame() > 90) {
                pKuroko->stopTurningMvAng();
                pKuroko->setRzRyMvAngVelo(0,0);
                pProg->changeNext();
            }
            break;
        }
        case PROG_NOTHING: {
            break;
        }
    }
    pKuroko->behave();
    getSeTransmitter()->behave();
}

void EnemyEsperiaLaserChip001::processJudgement() {
    HomingLaserChip::processJudgement();
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyEsperiaLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

EnemyEsperiaLaserChip001::~EnemyEsperiaLaserChip001() {
}

