#include "EnemyEmus.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

enum {
    PROG_INIT       ,
    PROG_INI_WAIT   ,
    PROG_HATCH_CLOSE,
    PROG_HATCH_OPEN ,
    PROG_FIRE       ,
    PROG_NOTHING    ,
    PROG_BANPEI,
};
enum {
    SE_DAMAGED  ,
    SE_EXPLOSION,
};

EnemyEmus::EnemyEmus(const char* prm_name) :
        DefaultMassMorphMeshActor(prm_name, "Emus_1", STATUS(EnemyEmus)) {
    _class_name = "EnemyEmus";
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 5*60;
    frame_of_morph_interval_ = 120;

//    pConn_pDepoStore_laser_set = connectToDepositoryManager(
//             "EnemyEmusLaserChip001DepoStore"
//         );
//    pDepoStore_laser_set = (GgafActorDepositoryStore*)(pConn_pDepoStore_laser_set->peek());
    pDepo_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
    ini_wait_ = 0;
}

void EnemyEmus::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setSpecular(5.0, 1.0);
    pModel->setBlinkPower(0.1, 0.9);
    pModel->getTexBlinker()->setRange(0.1, 1.0);
    pModel->getTexBlinker()->beat(120, 60, 0, 60, -1);
}

void EnemyEmus::initialize() {
    setHitAble(true);
    getKuroko()->linkFaceAngByMvAng(true);
    getMorpher()->setRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    CollisionChecker* pChecker = getCollisionChecker();
    pChecker->createCollisionArea(1);
    pChecker->setColliAABox_Cube(0, 200000);
    setScale(1000);
    GgafDxScaler* const pScaler = getScaler();
    pScaler->setRange(1000, 1200);
    pScaler->beat(30, 5, 0, 20, -1);
}

void EnemyEmus::onActive() {
    getStatus()->reset();
    setMorphWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
    getProgress()->reset(PROG_INIT);
}

void EnemyEmus::processBehavior() {
    changeGeoLocal(); //計算はローカル座標系
    GgafDxKuroko* const pKuroko = getKuroko();
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_INI_WAIT);
            break;
        }
        case PROG_INI_WAIT: {
            if (pProg->hasArrivedAt(ini_wait_+1)) {
                pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           0.0f, frame_of_morph_interval_);
                pKuroko->setRollFaceAngVelo(0);
            }

            //次へ
            if (pProg->getFrame() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (pProg->hasJustChanged()) {
                getMorpher()->transitionLinearUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                pKuroko->setRollFaceAngVelo(3000);
            }
            if (pProg->hasArrivedAt(frame_of_morph_interval_/2)) {
                //開くモーションが半分以上まで到達したなら
                pProg->change(PROG_FIRE);
            }
            break;
        }
        case PROG_FIRE: {
            if (pProg->hasJustChanged()) {
                if (!pDepo_) {
                    pDepo_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
                }
            }
            if (pProg->getFrame() >= (frame_of_morph_interval_/2) + frame_of_open_interval_) {
                pDepo_ = nullptr;
                pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    getMorpher()->behave();
    pKuroko->behave();
    changeGeoFinal(); //絶対座標系に戻す
}

void EnemyEmus::processChangeGeoFinal() {
    //絶対座標系での操作
    GgafProgress* const pProg = getProgress();
    switch (pProg->get()) {
        case PROG_FIRE: {
            if(pDepo_) {
                GgafDxFigureActor* pChip = (GgafDxFigureActor*)pDepo_->dispatch();
                if (pChip) {
                    pChip->setPositionAt(this);
                    pChip->getKuroko()->setRzRyMvAng(_rz, _ry); //絶対座標系での向き
                } else {
                    pDepo_ = nullptr;
                }
            }
            break;
        }
        default:
            break;
    }
}

void EnemyEmus::processJudgement() {

    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
//        (*(_pActor_base->_pFunc_calc_rot_mv_world_matrix))(_pActor_base, _matWorld);
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }


//    if (isOutOfSpacetime()) {
//        sayonara();
//    }
}

void EnemyEmus::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::performEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTransmitter()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //非破壊時
        getSeTransmitter()->play3D(SE_DAMAGED);
    }
}

void EnemyEmus::onInactive() {
    sayonara();
}

EnemyEmus::~EnemyEmus() {
//    pConn_pDepoStore_laser_set->close();
}
