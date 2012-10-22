#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

#define MORPHTARGET_HATCH_OPEN 1

EnemyRemus::EnemyRemus(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Remus", STATUS(EnemyRemus)) {
    _class_name = "EnemyRemus";
    _pActor_Base = NULL;
    is_open_hatch_ = false;
    frame_of_open_interval_  = 3*60;
    frame_of_close_interval_ = 20*60;
    frame_of_morph_interval_   = 120;

    pCon_LaserChipDepoStore_ = connectToDepositoryManager(
             "DpCon_EnemyRemusLaserChip001DepoStore", NULL
         );
    pLaserChipDepoStore_ = (GgafActorDepositoryStore*)(pCon_LaserChipDepoStore_->fetch());
    pLaserChipDepo_ = NULL;
    _pSeTxer->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTxer->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    wait_until_close_ = false;
    useProgress(PROG_HATCH_OPEN);
}

void EnemyRemus::onCreateModel() {
    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyRemus::initialize() {
    setHitAble(true);
    //_pKurokoA->setRzMvAngVelo(1000);
    //_pKurokoA->setRyMvAngVelo(500);
    _pKurokoA->relateFaceAngWithMvAng(true);
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
//    frame_of_moment_nextopen_ = frame_of_close_interval_;
    _pProg->set(PROG_HATCH_CLOSE);
}

void EnemyRemus::processBehavior() {

    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_HATCH_CLOSE);
            break;
        }
        case PROG_HATCH_CLOSE: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                0.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, -3000);
            }

            //次へ
            if (_pProg->getFrameInProgress() >= frame_of_close_interval_ + frame_of_morph_interval_) {
                _pProg->change(PROG_HATCH_OPEN);
            }
            break;
        }
        case PROG_HATCH_OPEN: {
            if (_pProg->hasJustChanged()) {
                _pMorpher->intoTargetLinerUntil(MORPHTARGET_HATCH_OPEN,
                                                1.0f, frame_of_morph_interval_);
                _pKurokoA->setFaceAngVelo(AXIS_X, 0);
                pLaserChipDepo_ = (LaserChipDepository*)(pLaserChipDepoStore_->dispatch()); //レーザーセット一本借り入れを試みる
                if(pLaserChipDepo_) {
                    wait_until_close_ = false;
                } else {
                    wait_until_close_ = true;
                }
            }

            //オープン時敵出現処理
            if (wait_until_close_ == false &&  _pMorpher->_weight[MORPHTARGET_HATCH_OPEN] > 0.5) { //モーションが半分以上まで到達したなら
                if (pLaserChipDepo_) { //レーザーセットが借り入れできてる場合
                    LaserChip* pChip = (LaserChip*)pLaserChipDepo_->dispatch();
                    if (pChip) {
                        //現在の最終的な向きを、RzRyで取得する
                        angle Rz, Ry;
                        UTIL::getRzRyAng(_matWorldRotMv._11, _matWorldRotMv._12, _matWorldRotMv._13,
                                         Rz, Ry); //現在の最終的な向きを、RzRyで取得！
                        pChip->_pKurokoA->setRzRyMvAng(Rz, Ry); //RzRyでMoverに設定
                        pChip->locateWith(this);
                    } else {
                        wait_until_close_ = true;
                    }
                }
            }

            if (_pProg->getFrameInProgress() >= frame_of_open_interval_+ frame_of_morph_interval_) {
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
    if (_pActor_Base != NULL && _pActor_Base->isActiveInTheTree()) {
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
        _pSeTxer->play3D(SE_EXPLOSION);

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            UTIL::activateItemOf(this);
        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTxer->play3D(SE_DAMAGED);
    }
}

void EnemyRemus::onInactive() {
    sayonara();
}

EnemyRemus::~EnemyRemus() {
    pCon_LaserChipDepoStore_->close();
}
