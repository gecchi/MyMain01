#include "stdafx.h"
#include "EnemyEmus.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepositoryStore.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxScaler.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChipDepository.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyEmus::EnemyEmus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Emus", STATUS(EnemyEmus)) {
    _class_name = "EnemyEmus";
    pScaler_ = NEW GgafDxScaler(this);
    _pActor_Base = nullptr;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 5*60;
    frame_of_morph_interval_ = 120;

//    pConn_LaserChipDepoStore_ = connect_DepositoryManager(
//             "EnemyEmusLaserChip001DepoStore"
//         );
//    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pConn_LaserChipDepoStore_->peek());
    pLaserChipDepo_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    is_firing_ = false;
    useProgress(PROG_BANPEI);
}

void EnemyEmus::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyEmus::initialize() {
    setHitAble(true);
    _pKuroko->relateFaceWithMvAng(true);
    _pMorpher->forceRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    setScale(1000);
    pScaler_->forceRange(1000, 1200);
    pScaler_->beat(30, 5, 0, 20, -1);
}

void EnemyEmus::onActive() {
    _pStatus->reset();
    setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
    _pProg->reset(PROG_HATCH_CLOSE);
}

void EnemyEmus::processBehavior() {
    changeGeoLocal(); //計算はローカル座標系
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->transitionLinerUntil(MORPHTARGET_HATCH_OPEN,
                                           0.0f, frame_of_morph_interval_);
                _pKuroko->setFaceAngVelo(AXIS_X, 0);
            }

            //次へ
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->transitionLinerUntil(MORPHTARGET_HATCH_OPEN,
                                           1.0f, frame_of_morph_interval_);
                _pKuroko->setFaceAngVelo(AXIS_X, 3000);
            }
            if (_pProg->getFrameInProgress() == (frame_of_morph_interval_/2)) {
                //開くモーションが半分以上まで到達したなら
                _pProg->change(PROG_FIRE);
            }
            break;
        }
        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {

                if (!pLaserChipDepo_) {
                    pLaserChipDepo_ = (LaserChipDepository*)UTIL::getDepositoryOf(this);
                }
                if(pLaserChipDepo_) {
                    is_firing_ = true; //レーザーセットの借り入れ出来た
                } else {
                    is_firing_ = false; //レーザーセットが借りれなかった
                }
            }


            if (_pProg->getFrameInProgress() >= (frame_of_morph_interval_/2) + frame_of_open_interval_) {
                is_firing_ = false;
                pLaserChipDepo_ = nullptr;
                _pProg->change(PROG_HATCH_CLOSE);
            }
            break;
        }
        default :
            break;
    }
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    _pMorpher->behave();
    _pKuroko->behave();
    changeGeoFinal();
}

void EnemyEmus::processSettlementBehavior() {
    DefaultMorphMeshActor::processSettlementBehavior();
    //絶対座標が更新されてから～オープン時レーザー
    if (is_firing_) {
        LaserChip* pChip = pLaserChipDepo_->dispatch();
        if (pChip) {
            pChip->position(_x, _y, _z);
            pChip->_pKuroko->setRzRyMvAng(_rz, _ry); //絶対座標系での向き
        } else {
            is_firing_ = false;
        }
    }
}

void EnemyEmus::processJudgement() {
    if (_pActor_Base != nullptr && _pActor_Base->isActiveInTheTree()) {
//        (*(_pActor_Base->_pFunc_calcRotMvWorldMatrix))(_pActor_Base, _matWorld);
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }


//    if (isOutOfUniverse()) {
//        sayonara();
//    }
}

void EnemyEmus::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyEmus::onInactive() {
    sayonara();
}

EnemyEmus::~EnemyEmus() {
    GGAF_DELETE(pScaler_);
//    pConn_LaserChipDepoStore_->close();
}
