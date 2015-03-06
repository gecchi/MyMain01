#include "EnemyRatislaviaEye.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EffectRatislaviaEye001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislavia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ratislavia/EnemyRatislaviaEyeStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRatislaviaEye::EnemyRatislaviaEye(const char* prm_name, EnemyRatislavia* prm_pRatislavia) :
        DefaultMorphMeshActor(prm_name, "1/RatislaviaEye", STATUS(EnemyRatislaviaEye)) {
        //CubeMapMorphMeshActor(prm_name, "1/HaliaCM", STATUS(EnemyRatislaviaEye)) {

    _class_name = "EnemyRatislaviaEye";
    setScaleR(0.3*10);
    pRatislavia_ = prm_pRatislavia;
    positionAs(pRatislavia_);

    pLaserChipDepo_ = NEW LaserChipDepository("DepoLaserChip");
    pLaserChipDepo_->config(60, 1, nullptr); //Haliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyRatislaviaEyeStraightLaserChip001* pChip;
    for (int i = 0; i < 60; i++) { //レーザーストック
        std::string name = "LaserChip("+ XTOS(i) + ")";
        pChip = NEW EnemyRatislaviaEyeStraightLaserChip001(name.c_str());
        pChip->setSource(this); //位置向き同期
        pLaserChipDepo_->put(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    pEffect_ = NEW EffectRatislaviaEye001("EffectRatislaviaEye001");
    pEffect_->inactivate();
    addSubGroup(pEffect_);
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_MIDDLE_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");
    useProgress(PROG_BANPEI);

    is_wake_ = false;
}

void EnemyRatislaviaEye::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->forceRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyRatislaviaEye::initialize() {
    setHitAble(true);
    getKuroko()->relateFaceByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, 200000);
}

void EnemyRatislaviaEye::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);
    getProgress()->reset(PROG_MOVE);
    positionAs(pRatislavia_);
    setFaceAngAs(pRatislavia_);
    getKuroko()->setRzRyMvAngVelo(pRatislavia_->getKuroko()->_angvelo_face[AXIS_Z],
                                  pRatislavia_->getKuroko()->_angvelo_face[AXIS_Y]);
}

void EnemyRatislaviaEye::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    positionAs(pRatislavia_);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_MOVE: {
            break;
        }
        case PROG_OPEN: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(1, 1.0, 180); //開く
            }
            if (pProg->getFrame() > 240) {
                pProg->changeNext();
            }
            pKuroko->takeoverMvFrom(pRatislavia_->getKuroko());
            pKuroko->setRzRyMvAngVelo(pRatislavia_->getKuroko()->_angvelo_face[AXIS_Z],
                                      pRatislavia_->getKuroko()->_angvelo_face[AXIS_Y]);
            break;
        }

        case PROG_TURN: {
            if (pProg->isJustChanged()) {
                pKuroko->turnMvAngTwd(P_MYSHIP,
                                        D_ANG(1), 0, TURN_CLOSE_TO, false);
            }
            if (pProg->getFrame() > 240) {
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if (pProg->isJustChanged()) {
                //_pKuroko->turnMvAngTwd(P_MYSHIP, D_ANG(1), 0, TURN_ANTICLOSE_TO, false);
                pEffect_->activate();
            }
            pEffect_->positionAs(this);
            if (pEffect_->onChangeToInactive()) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (pProg->isJustChanged()) {
                pKuroko->turnMvAngTwd(P_MYSHIP,
                                        10, 0, TURN_CLOSE_TO, false);
            }
            LaserChip* pChip = pLaserChipDepo_->dispatch();
            if (pChip) {
                if (pChip->getFrontChip() == nullptr) {
                    getSeTx()->play3D(SE_FIRE);
                }
            } else {
                pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_END: {
            if (pProg->isJustChanged()) {
                getMorpher()->transitionLinerUntil(1, 0.0, 180); //閉じる
                pKuroko->setRzRyMvAngVelo(pRatislavia_->getKuroko()->_angvelo_face[AXIS_Z],
                                          pRatislavia_->getKuroko()->_angvelo_face[AXIS_Y]);
            }
            //硬直
            if (pProg->getFrame() >= 300) {
                pProg->change(PROG_OPEN);
            }
            break;
        }

        default: {
            break;
        }
    }

    pKuroko->behave();
    getMorpher()->behave();
    getSeTx()->behave();
}

void EnemyRatislaviaEye::processJudgement() {
//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyRatislaviaEye::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
        _TRACE_("EnemyRatislaviaEye::onHit() 上位になげるthrowEventUpperTree(RATISLAVIA_EXPLOSION)");
        throwEventUpperTree(RATISLAVIA_EXPLOSION); //親のEnemyRatislaviaを破壊するイベントを投げる
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyRatislaviaEye::onInactive() {
    //sayonara();
}

void EnemyRatislaviaEye::wake() {
    is_wake_ = true;
    getProgress()->change(PROG_OPEN);
}

EnemyRatislaviaEye::~EnemyRatislaviaEye() {
}
