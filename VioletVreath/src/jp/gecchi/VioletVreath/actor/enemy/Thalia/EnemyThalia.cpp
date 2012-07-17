#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyThalia::EnemyThalia(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Thalia", STATUS(EnemyThalia)) {
        //CubeMapMorphMeshActor(prm_name, "1/ThaliaCM", STATUS(EnemyThalia)) {

    _class_name = "EnemyThalia";
    veloTopMv_ = 20000;
    iMovePatternNo_ = 0;
    pSplSeq_ = NULL;
    pDepo_Shot_ = NULL;
    pDepo_ShotEffect_ = NULL;

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1, NULL); //Thaliaは弾切れフレームを1にしないとパクパクしちゃいます。
    EnemyStraightLaserChip001* pChip;
    for (int i = 0; i < 65; i++) { //レーザーストック
        std::stringstream name;
        name <<  "EnemyStraightLaserChip001[" << i << "]";
        pChip = NEW EnemyStraightLaserChip001(name.str().c_str());
        pChip->setSource(this); //位置向き同期
        pChip->inactivateImmed();
        pLaserChipDepo_->addSubLast(pChip);
    }
    addSubGroup(pLaserChipDepo_);

    _pSeTx->set(SE_DAMAGED  , "yume_shototsu", GgafRepeatSeq::nextVal("CH_yume_shototsu"));
    _pSeTx->set(SE_EXPLOSION, "bomb1"   , GgafRepeatSeq::nextVal("CH_bomb1"));
    _pSeTx->set(SE_FIRE     , "laser001", GgafRepeatSeq::nextVal("CH_laser001"));
    useProgress(PROG_CLOSE);
    //初期カメラZ位置
    dZ_camera_init_ = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyThalia::onCreateModel() {

    _pModel->_pTextureBlinker->forceBlinkRange(0.9, 0.1, 1.0);
    _pModel->_pTextureBlinker->setBlink(0.1);
    _pModel->_pTextureBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pKurokoA->relateFaceAngWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyThalia::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->execSmoothMvSequenceD(veloTopMv_, 1000,
                                     MyShip::lim_front_-_X, 0.4, 0.6);
    _pProg->set(PROG_MOVE);
    iMovePatternNo_ = 0; //行動パターンリセット

}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));



    switch (_pProg->get()) {
        case PROG_MOVE: {
            if (!_pKurokoA->isRunnigSmoothMvSequence()) {
                _pMorpher->intoTargetAcceStep(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                 0, 100,
                                                 TURN_CLOSE_TO);

                _pProg->changeNext();
            }
            break;
        }
        case PROG_TURN_OPEN: {
            if (_pProg->getFrameInProgress() > 120) {
                _pProg->changeNext();
            }
            break;
        }

        case PROG_FIRE_BEGIN: {
            if ( _X - P_MYSHIP->_X > -dZ_camera_init_) {
                _pProg->change(PROG_IN_FIRE);
            } else {
                //背後からは撃たない。
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_IN_FIRE: {
            if (getActivePartFrame() % 10 == 0) {
                _pKurokoA->execTurnMvAngSequence(P_MYSHIP->_X, P_MYSHIP->_Y, P_MYSHIP->_Z,
                                                 10, 0,
                                                 TURN_CLOSE_TO);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == NULL) {
                    _pSeTx->play3D(SE_FIRE);
                    _pKurokoA->setFaceAngVelo(AXIS_X, 5000);//発射中は速い回転
                }
            } else {
                _pProg->change(PROG_CLOSE);
            }
            break;
        }
        case PROG_CLOSE: {
            //１サイクルレーザー打ち切った
            _pMorpher->intoTargetLinerUntil(1, 0.0, 60); //閉じる
            _pKurokoA->execSmoothMvSequenceD(veloTopMv_, 1000, 1500000, 0.4, 0.6);
//            _pKurokoA->execSmoothMvSequence(200, 1000000, 180);
            _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
            _pProg->change(PROG_MOVE);
            break;
        }

        default:
            break;
    }


    _pKurokoA->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyThalia::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyThalia::onHit(GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*)prm_pOtherActor;

    if (UTIL::calcEnemyStamina(this, pOther) <= 0) {
        setHitAble(false);
        //爆発エフェクト
        GgafDxDrawableActor* pExplo = UTIL::activateExplosionEffectOf(this);
        if (pExplo) {
            pExplo->locateWith(this);
            pExplo->_pKurokoA->followMvFrom(_pKurokoA);
        }
        _pSeTx->play3D(SE_EXPLOSION);

        //打ち返し弾
        if (pDepo_Shot_) {
//                UTIL::shotWay001(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       2000, 200);
//                UTIL::shotWay001v2(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       10+_RANK_*10, 10000,
//                                       3000, 200,
//                                       5, 0.8);
//                UTIL::shotWay002(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       20+_RANK_*10, 0,
//                                       2000, 200);
//                  UTIL::shotWay002v2(this,
//                                       pDepo_Shot_,
//                                       P_MYSHIP,
//                                       RR_EnemyThalia_ShotWay(_RANK_), 0,
//                                       2000, 200,
//                                       5, 0.8);
//                  UTIL::shotWay002(this, pDepo_Shot_,
//                                      PX_C(20),
//                                      5, 5, D_ANG(10), D_ANG(10),
//                                      2000, 200);

//                  UTIL::shotWay002(this, pDepo_Shot_,
//                                      PX_C(20),
//                                      6, 6, D_ANG(8), D_ANG(8),
//                                      2000, 200,
//                                      20, 60, 0.9);

            UTIL::shotWay004(this, pDepo_Shot_,
                             PX_C(20),
                             8, D_ANG(10),
                             2000, 200,
                             12, 3, 0.9);

        }

        //自機側に撃たれて消滅の場合、
        if (pOther->getKind() & KIND_MY) {
            //アイテム出現
            Item* pItem = UTIL::activateItemOf(this);
            if (pItem) {
                pItem->locateWith(this);
            }
        }
        sayonara();
    } else {
        //非破壊時
        effectFlush(2); //フラッシュ
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyThalia::onInactive() {
    //sayonara();
}

EnemyThalia::~EnemyThalia() {
    DELETE_POSSIBLE_NULL(pSplSeq_);
}
