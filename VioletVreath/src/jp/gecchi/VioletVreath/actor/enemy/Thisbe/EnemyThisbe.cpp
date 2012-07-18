#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyThisbe::EnemyThisbe(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thisbe", STATUS(EnemyThisbe)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThisbeCM", STATUS(EnemyThisbe)) {

    _class_name = "EnemyThisbe";
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;

    pLaserChipDepo_ = NEW LaserChipDepository("ThisbeLaser");
    pLaserChipDepo_->config(100, 1, NULL); //Thisbeは弾切れフレームを1にしないとパクパクしちゃいます。

//    EnemyThisbeLaserChip001* pChip;
//    for (int i = 0; i < 65; i++) { //レーザーストック
//        std::stringstream name;
//        name <<  "EnemyThisbeLaserChip001[" << i << "]";
//        pChip = NEW EnemyThisbeLaserChip001(name.str().c_str());
//        pLaserChipDepo_->addSubLast(pChip);
//    }


    pCon_RefractionEffectDepository_ = connectToDepositoryManager("DpCon_EffRefraction001", NULL);

    EnemyThisbeLaserChip002* pChip;
    for (int i = 0; i < 100; i++) { //レーザーストック
        std::stringstream name;
        name <<  "EnemyThisbeLaserChip002[" << i << "]";
        pChip = NEW EnemyThisbeLaserChip002(name.str().c_str());
        int num_refraction = pChip->pSplManufCon_->fetch()->_pSplSrc->_pSp->_rnum;
        pChip->config(num_refraction, 1, 1, pCon_RefractionEffectDepository_->fetch());
        pLaserChipDepo_->addSubLast(pChip);
    }

    addSubGroup(pLaserChipDepo_);

    _pSeTx->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTx->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTx->set(SE_FIRE     , "laser001", GgafRepeatSeq::nextVal("CH_laser001"));

    useProgress(PROG_CLOSE);
}

void EnemyThisbe::onCreateModel() {
}

void EnemyThisbe::initialize() {
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 40000);
}

void EnemyThisbe::onActive() {
    _pStatus->reset();
    _pMorpher->reset();
    _pProg->set(PROG_WAIT);
}

void EnemyThisbe::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    switch (_pProg->get()) {
        case PROG_WAIT: {
            if (pLaserChipDepo_->_num_chip_active == 0) {
                _pProg->changeNext();
            }
            break;
        }
        case PROG_OPEN: {
            if (_pProg->isJustChanged()) {
                _pMorpher->intoTargetLinerUntil(1, 1.0, 120);
            }
            if (!_pMorpher->isMorph()) {
                //完全に開いたら
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE: {
            LaserChip* pLaser = pLaserChipDepo_->dispatch();
            if (pLaser) {
                pLaser->locateWith(this);
                pLaser->_pKurokoA->setRzRyMvAng(_pKurokoA->_angFace[AXIS_Z], _pKurokoA->_angFace[AXIS_Y]);
                                   //レーザーのスプラインがRELATIVE_DIRECTIONのためMvAngの設定が必要。
                if (pLaser->_pChip_front == NULL) {
                    _pSeTx->play3D(SE_FIRE);
                }
            } else {
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->intoTargetLinerUntil(1, 0.0, 120); //閉じる
            if (!_pMorpher->isMorph()) {
                //完全に閉じたら
                _pProg->change(PROG_WAIT);
            }
            break;
        }

        default:
            break;
    }

    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyThisbe::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThisbe::onHit(GgafActor* prm_pOtherActor) {
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

void EnemyThisbe::onInactive() {
    //sayonara();
}

EnemyThisbe::~EnemyThisbe() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
    pCon_RefractionEffectDepository_->close();
}
