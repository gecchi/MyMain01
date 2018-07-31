#include "EnemyHisbe002.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hisbe/EnemyHisbeLaserChip003.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

enum {
    PROG_WAIT,
    PROG_OPEN,
    PROG_FIRE,
    PROG_CLOSE,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
    SE_FIRE,
};

EnemyHisbe002::EnemyHisbe002(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Hisbe002", STATUS(EnemyHisbe002)) {
        //CubeMapMorphMeshActor(prm_name, "1/HisbeCM", STATUS(EnemyHisbe002)) {

    _class_name = "EnemyHisbe002";
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;

    pLaserChipDepo_ = NEW LaserChipDepository("HisbeLaser");
    EnemyHisbeLaserChip003* pChip;
    for (int i = 0; i < 240; i++) { //レーザーストック
        std::stringstream name;
        name <<  "EnemyHisbeLaserChip003[" << i << "]";
        pChip = NEW EnemyHisbeLaserChip003(name.str().c_str());
        pLaserChipDepo_->put(pChip);
    }
    pLaserChipDepo_->config(240, 1, nullptr); //Hisbeは弾切れフレームを1にしないとパクパクしちゃいます。
    addSubGroup(pLaserChipDepo_);

    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_BANPEI);
}

void EnemyHisbe002::onCreateModel() {
}

void EnemyHisbe002::initialize() {
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->setFaceAngVelo(AXIS_Y, 500);
    pKuroko->linkFaceAngByMvAng(true);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliSphere(0, 40000);
}

void EnemyHisbe002::onActive() {
    getStatus()->reset();
    getMorpher()->reset();
    getProgress()->reset(PROG_WAIT);
}

void EnemyHisbe002::processBehavior() {
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_WAIT: {
            if (pLaserChipDepo_->_num_chip_active == 0) {
                pProg->changeNext();
            }
            break;
        }
        case PROG_OPEN: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 1.0, 120);
            }
            if (!getMorpher()->isTransitioning()) {
                //完全に開いたら
                pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                pLaser->setPositionAt(this);
                pLaser->getKuroko()->setRzRyMvAng(_rz, _ry);
                                   //レーザーのスプラインがRELATIVE_COORD_DIRECTIONのためMvAngの設定が必要。
                if (pLaser->getInfrontChip() == nullptr) {
                    getSeTransmitter()->play3D(SE_FIRE);
                }
            } else {
                pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: { //１サイクルレーザー打ち切った
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(1, 0.0, 120); //閉じる
            }
            if (!getMorpher()->isTransitioning()) {
                //完全に閉じたら
                pProg->change(PROG_WAIT);
            }
            break;
        }

        default: {
            break;
        }
    }

    pKuroko->behave();
    getMorpher()->behave();
    getSeTransmitter()->behave();
}

void EnemyHisbe002::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyHisbe002::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyHisbe002::onInactive() {
    //sayonara();
}

EnemyHisbe002::~EnemyHisbe002() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
