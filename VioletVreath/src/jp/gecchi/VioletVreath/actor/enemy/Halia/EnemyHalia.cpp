#include "EnemyHalia.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoMvAssistant.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyHalia::EnemyHalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Halia", STATUS(EnemyHalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/HaliaCM", STATUS(EnemyHalia)) {

    _class_name = "EnemyHalia";
    veloTopMv_ = 20000;
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

    pAFader_ = NEW GgafDxAlphaFader(this);

    useProgress(PROG_BANPEI);
    //初期カメラZ位置
    const Camera* const pCam = P_GOD->getSpacetime()->getCamera();
    dZ_camera_init_ = -1 * DX_C(pCam->getZOrigin());
}

void EnemyHalia::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
    pModel->setSpecular(5.0, 1.0);
}

void EnemyHalia::initialize() {
    setHitAble(true);
    getKuroko()->linkFaceAngByMvAng(true);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyHalia::onActive() {
    getStatus()->reset();
    setMorphWeight(0.0);
    getProgress()->reset(PROG_INIT);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setRollFaceAngVelo(1000);
    pKuroko->setMvVelo(0);
    pKuroko->setMvAcce(0);
}

void EnemyHalia::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pProg->changeNext();
            break;
        }
        case PROG_ENTRY: {  //登場
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
                pProg->change(PROG_FIRST_MOVE);
            }
            break;
        }
        case PROG_FIRST_MOVE: { //初回移動
            if (pProg->hasJustChanged()) {
                pKuroko->setRzRyMvAng(0, 0);
                pKuroko->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pKuroko->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pKuroko->asstMv()->isSliding()) {
                pProg->change(PROG_TURN_OPEN);
            }
            break;
        }
        case PROG_MOVE: {  //２回以降の移動
            if (pProg->hasJustChanged()) {
                pKuroko->asstMv()->slideByVd(veloTopMv_, PX_C(1000),
                                              0.4, 0.6, 0, true);
                pKuroko->setRollFaceAngVelo(D_ANG(1));
            }
            if (!pKuroko->asstMv()->isSliding()) {
                pProg->change(PROG_TURN_OPEN);
            }
            break;
        }
        case PROG_TURN_OPEN: {
            if (pProg->hasJustChanged()) {
                pKuroko->turnMvAngTwd(P_MYSHIP,
                                      0, 100,
                                      TURN_CLOSE_TO, false);
            }
            if (!pKuroko->isTurningMvAng()) {
                pKuroko->turnMvAngTwd(P_MYSHIP,
                                      D_ANG(1), 0,
                                      TURN_CLOSE_TO, false);
                getMorpher()->transitionAcceStep(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
                pProg->changeNext();
            }
            break;
        }
        case PROG_FIRE_BEGIN: {
            if (!getMorpher()->isTransitioning()) {
                if ( _x - P_MYSHIP->_x > -dZ_camera_init_) {
                    pKuroko->setMvVelo(PX_C(1)); //ちょっとバック
                    pKuroko->setRollFaceAngVelo(D_ANG(5));//発射中は速い回転
                    pProg->change(PROG_IN_FIRE);
                } else {
                    //背後からは撃たない。
                    pProg->change(PROG_CLOSE);
                }
            }
            break;
        }
        case PROG_IN_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->getFrontChip() == nullptr) {
                    getSeTx()->play3D(SE_FIRE);
                }
            } else {
                pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            getMorpher()->transitionLinerUntil(1, 0.0, 60); //閉じる
            pProg->change(PROG_MOVE);
            break;
        }

        default: {
            break;
        }
    }
    pKuroko->behave();
    getMorpher()->behave();
    getSeTx()->behave();
    pAFader_->behave();
}

void EnemyHalia::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHalia::onHit(const GgafActor* prm_pOtherActor) {
    if (getMorphWeight(1) > 0.3) { //口が空いてたら
        bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊された時(スタミナ <= 0)
            getSeTx()->play3D(SE_EXPLOSION);
            sayonara();
        } else {
            //破壊されなかった時(スタミナ > 0)
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
    GGAF_DELETE(pAFader_);
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
