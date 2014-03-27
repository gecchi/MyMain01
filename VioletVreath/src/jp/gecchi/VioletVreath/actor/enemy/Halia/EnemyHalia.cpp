#include "stdafx.h"
#include "EnemyHalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHalia::EnemyHalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Halia", STATUS(EnemyHalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/HaliaCM", STATUS(EnemyHalia)) {

    _class_name = "EnemyHalia";
    veloTopMv_ = 20000;
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1, nullptr); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //レーザーストック
        std::string name = "EnemyStraightLaserChip001["+XTOS(i)+"]";
        pChip = NEW EnemyStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    addSubGroup(pLaserChipDepo_);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
    //初期カメラZ位置
    dZ_camera_init_ = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyHalia::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->_pTexBlinker->forceRange(0.1, 1.0);
    pModel->_pTexBlinker->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyHalia::initialize() {
    setHitAble(true);
    getKuroko()->relateFaceByMvAng(true);
    CollisionChecker3D* pColliChecker = getCollisionChecker();
    pColliChecker->makeCollision(1);
    pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHalia::onActive() {
    getStatus()->reset();
    setMorphWeight(0.0);
    GgafDxKuroko* pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_X, 1000);
    pKuroko->hlprA()->slideMvByVd(veloTopMv_, MyShip::lim_x_front_-_x,
                           0.4, 0.6, 1000, true);
    getProgress()->reset(PROG_MOVE);
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyHalia::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE: {
            if (!pKuroko->hlprA()->isSlidingMv()) {
                getMorpher()->transitionAcceStep(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
                pKuroko->turnMvAngTwd(P_MYSHIP,
                                        0, 100,
                                        TURN_CLOSE_TO, false);
                pProg->changeNext();
            }
            break;
        }
        case PROG_TURN_OPEN: {
            if (pProg->getFrameInProgress() > 120) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_BEGIN: {
            if ( _x - P_MYSHIP->_x > -dZ_camera_init_) {
                pProg->change(PROG_IN_FIRE);
            } else {
                //背後からは撃たない。
                pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (getActiveFrame() % 16U == 0) {
                pKuroko->turnMvAngTwd(P_MYSHIP,
                                        10, 0,
                                        TURN_CLOSE_TO, false);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == nullptr) {
                    getSeTx()->play3D(SE_FIRE);
                    pKuroko->setFaceAngVelo(AXIS_X, 5000);//発射中は速い回転
                }
            } else {
                pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            getMorpher()->transitionLinerUntil(1, 0.0, 60); //閉じる
            pKuroko->hlprA()->slideMvByVd(veloTopMv_, 1500000, 0.4, 0.6, 1000, true);
            pKuroko->setFaceAngVelo(AXIS_X, 1000);
            pProg->change(PROG_MOVE);
            break;
        }

        default:
            break;
    }
    pKuroko->behave();
    getMorpher()->behave();
    getSeTx()->behave();
}

void EnemyHalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyHalia::onHit(GgafActor* prm_pOtherActor) {
    if (getMorphWeight(1) > 0.1) { //口が空いてたら
        bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊時
            getSeTx()->play3D(SE_EXPLOSION);
        } else {
            //非破壊時
            getSeTx()->play3D(SE_DAMAGED);
        }
    } else {
        getSeTx()->play3D(SE_UNDAMAGED);
    }
}

void EnemyHalia::onInactive() {
    //sayonara();
}

EnemyHalia::~EnemyHalia() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
