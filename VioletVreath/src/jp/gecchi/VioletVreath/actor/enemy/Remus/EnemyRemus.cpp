#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyRemus::EnemyRemus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Remus", STATUS(EnemyRemus)) {
    _class_name = "EnemyRemus";
    _pActor_Base = nullptr;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 5*60;
    frame_of_morph_interval_   = 120;

    pConn_LaserChipDepoStore_ = connectToDepositoryManager(
             "Conn_EnemyRemusLaserChip001DepoStore", nullptr
         );
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pConn_LaserChipDepoStore_->fetch());
    pLaserChipDepo_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    is_firing_ = false;
    useProgress(PROG_NOTHING);
}

void EnemyRemus::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyRemus::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pMorpher->forceWeightRange(MORPHTARGET_HATCH_OPEN, 0.0f, 1.0f);
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 200000);
    _pScaler->setScale(1000);
    _pScaler->forceScaleRange(1000, 1200);
    _pScaler->beat(30, 5, 5, -1);
}

void EnemyRemus::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(MORPHTARGET_HATCH_OPEN, 0.0f);
    is_open_hatch_ = false;
    _pProg->reset(PROG_HATCH_CLOSE);
}

void EnemyRemus::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->isJustChanged()) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
            }

            //次へ
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 3000);
            }
            if (_pProg->getFrameInProgress() == (frame_of_morph_interval_/2)) {
                //開くモーションが半分以上まで到達したなら
                _pProg->change(PROG_FIRE);
            }
            break;
        }
        case PROG_FIRE: {
            if (_pProg->isJustChanged()) {
                pLaserChipDepo_ = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch()); //レーザーセット一本借り入れを試みる
                if(pLaserChipDepo_) {
                    is_firing_ = true; //レーザーセットの借り入れ出来た
                } else {
                    is_firing_ = false; //レーザーセットが借りれなかった
                }
            }
            //オープン時レーザー
            if (is_firing_) {
                LaserChip* pChip = pLaserChipDepo_->dispatch();
                if (pChip) {
                    pChip->locateWith(this);
                    angle Rz, Ry;  //現在の最終的な向きを、RzRyで取得する
                    UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                     Rz, Ry); //現在の最終的な向きを、RzRyで取得！
                    pChip->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                } else {
                    is_firing_ = false;
                }
            }

            if (_pProg->getFrameInProgress() >= (frame_of_morph_interval_/2) + frame_of_open_interval_) {
                is_firing_ = false;
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
    //_pKurokoAの計算はローカルで行う
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();

}

void EnemyRemus::processJudgement() {
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

void EnemyRemus::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
        _pSeTx->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyRemus::onInactive() {
    sayonara();
}

EnemyRemus::~EnemyRemus() {
    pConn_LaserChipDepoStore_->close();
}
