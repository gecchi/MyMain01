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
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;

    pLaserChipDepo_ = NEW LaserChipDepository("MyRotLaser");
    pLaserChipDepo_->config(60, 1, nullptr); //Thaliaは弾切れフレームを1にしないとパクパクしちゃいます。
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

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    _pSeTx->set(SE_FIRE     , "WAVE_ENEMY_FIRE_LASER_001");

    useProgress(PROG_CLOSE);
    //初期カメラZ位置
    dZ_camera_init_ = -1 * P_CAM->_cameraZ_org * LEN_UNIT * PX_UNIT;
}

void EnemyThalia::onCreateModel() {
    _pModel->_pTexBlinker->setBlinkableRange(0.9, 0.1, 1.0);
    _pModel->_pTexBlinker->setPower(0.1);
    _pModel->_pTexBlinker->beat(120, 60, 1, -1);
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyThalia::initialize() {
    setHitAble(true);
    _pKurokoA->relateMvFaceAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
    setScaleR(0.3);
}

void EnemyThalia::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);
    _pKurokoA->setFaceAngVelo(AXIS_X, 1000);
    _pKurokoA->slideMvByVD(veloTopMv_, 1000,
                                         MyShip::lim_front_-_X, 0.4, 0.6);
    _pProg->reset(PROG_MOVE);
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyThalia::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_MOVE: {
            if (!_pKurokoA->isSlidingMv()) {
                _pMorpher->morphAcceStep(1, 1.0, 0.0, 0.0004); //開く 0.0004 開く速さ
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                        0, 100,
                                        TURN_CLOSE_TO, false);
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
            if (getActiveFrame() % 16 == 0) {
                _pKurokoA->turnMvAngTwd(P_MYSHIP,
                                        10, 0,
                                        TURN_CLOSE_TO, false);
            }
            EnemyStraightLaserChip001* pLaser = (EnemyStraightLaserChip001*)pLaserChipDepo_->dispatch();
            if (pLaser) {
                if (pLaser->_pChip_front == nullptr) {
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
            _pMorpher->morphLinerUntil(1, 0.0, 60); //閉じる
            _pKurokoA->slideMvByVD(veloTopMv_, 1000, 1500000, 0.4, 0.6);
//            _pKurokoA->slideMvByDT(200, 1000000, 180);
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
        //爆発効果
        UTIL::activateExplosionEffectOf(this);
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
            UTIL::activateItemOf(this);
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
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
