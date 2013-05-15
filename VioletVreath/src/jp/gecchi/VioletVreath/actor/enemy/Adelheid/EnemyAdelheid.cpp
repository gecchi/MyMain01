#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdelheid::EnemyAdelheid(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Adelheid", STATUS(EnemyAdelheid)) {
    _class_name = "EnemyAdelheid";
    pKurokoLeader_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(PROG_MOVING_AFTER_LEAD);
    pProg2_ = createProgress(PROG2_CLOSE);
    shot_begin_frame_ = 0;
}

void EnemyAdelheid::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAdelheid::nextFrame() {
    DefaultMorphMeshActor::nextFrame();
    if (!_was_paused_flg && _is_active_in_the_tree_flg) {
        pProg2_->update();
    }
}
void EnemyAdelheid::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    setScaleR(0.3);
}

void EnemyAdelheid::onActive() {
    if (getFormation()) {
        GGAF_DELETE_NULLABLE(pKurokoLeader_);
        pKurokoLeader_ = ((FormationAdelheid*)getFormation())->getSplManuf()->createKurokoLeader(_pKurokoA);
    }
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAdelheidはスプライン必須ですconfigして下さい。 this="<<this<<" name="<<getName());
    }
    _pStatus->reset();
    setHitAble(true);
    _pMorpher->reset();
    _pKurokoA->setFaceAng(AXIS_X, 0);
    _pKurokoA->setMvAcce(0);
    _pKurokoA->keepOnTurningFaceAngTwd(P_MYSHIP,
                                       D_ANG(1), 0, TURN_CLOSE_TO, false);
    _pProg->reset(PROG_INIT);
    pProg2_->reset(PROG2_WAIT);
}

void EnemyAdelheid::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    MyShip* pMyShip = P_MYSHIP;

    //移動の状態遷移------------------------------
    switch (_pProg->get()) {
        case PROG_INIT: {
            pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
            _pProg->changeNext();
            break;
        }
        case PROG_MOVING: {
            if (_pProg->isJustChanged()) {
            }

            //pKurokoLeader_->isFinished() 待ち
            break;
        }

        //ゴールのパリサナがいない場合、その後の移動
        case PROG_MOVING_AFTER_LEAD: {
            if (_pProg->isJustChanged()) {
                _pKurokoA->setMvAcce(100);
            }

            //isOutOfUniverse() まで・・・
            break;
        }
    }

    //ショット発射の状態遷移-----------------------------------
    switch (pProg2_->get()) {
        case PROG2_WAIT: {
            //open_shot() 待ち・・・
            break;
        }
        case PROG2_OPEN: {
            if (pProg2_->isJustChanged()) {
                _pMorpher->morphAcceStep(MPH_OPEN, 1.1, 0, 0.001);
            }
            if (!_pMorpher->isMorphing()) {
                _pMorpher->setWeight(MPH_OPEN, 1.0);
                pProg2_->changeNext();
            }
            break;
        }

        case PROG2_SHOT: {
            if (pProg2_->isJustChanged()) {
                shot_begin_frame_ = RND(120, 240);
            }
            if (pProg2_->getFrameInProgress() == shot_begin_frame_) {
                UTIL::shotWay002(
                       this,
                       ((FormationAdelheid*)getFormation())->pConnection_ShotDepo_->peek(),
                       PX_C(20),     //r
                       5,            //way数
                       D_ANG(10),    //wayとwayの間隔
                       PX_C(5),      //初期速度
                       100,          //加速度
                       2,            //wayのセット数
                       0,            //セットとセットの間隔フレーム
                       0.8f,         //セット増加に伴う初期速度減衰率
                       nullptr
                     );
            }
            if (pProg2_->getFrameInProgress() == 240) {
                pProg2_->changeNext();
            }
            break;
        }
        case PROG2_CLOSE: {
            if (pProg2_->isJustChanged()) {
                _pMorpher->morphAcceStep(MPH_OPEN, 0.0, 0, -0.01);
            }
            if (!_pMorpher->isMorphing()) {
                pProg2_->changeNothing();
            }

            break;
        }
    }
    //-----------------------------------------------

    if (getFormation()) {
        _pKurokoA->_veloMv = ((FormationAdelheid*)getFormation())->mv_velo_member_;
        _pKurokoA->_angveloFace[AXIS_X] = ((FormationAdelheid*)getFormation())->mv_velo_member_ / 2;
    }

    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();
    _pMorpher->behave();
}

void EnemyAdelheid::processJudgement() {
    if (_pProg->get() == PROG_MOVING) {
        if (pKurokoLeader_->isFinished()) {
            if (getFormation()) {
                if (((FormationAdelheid*)getFormation())->pPalisana_goal) {
                    _pProg->changeNothing();
                    sayonara();
                } else {
                    _pProg->change(PROG_MOVING_AFTER_LEAD);
                }
            } else {
                //ダミーの時か、来ないハズ
            }
        }
    }

    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAdelheid::onHit(GgafActor* prm_pOtherActor) {
    if (pProg2_->isNothing() || pProg2_->get() == PROG2_WAIT) {
        //開いてないので当たらない
    } else {
        bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊時
            _pSeTx->play3D(SE_EXPLOSION);
        } else {
            //非破壊時
            _pSeTx->play3D(SE_DAMAGED);
        }
    }
}

void EnemyAdelheid::onInactive() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}

void EnemyAdelheid::open_shot() {
    pProg2_->change(PROG2_OPEN);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    GGAF_DELETE(pProg2_);
}


