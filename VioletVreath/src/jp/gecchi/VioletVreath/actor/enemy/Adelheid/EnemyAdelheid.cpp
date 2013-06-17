#include "stdafx.h"
#include "EnemyAdelheid.h"

#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxChecker.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adelheid/FormationAdelheid.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAdelheid::EnemyAdelheid(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Adelheid", STATUS(EnemyAdelheid)) {
    _class_name = "EnemyAdelheid";
    pKurokoLeader_ = nullptr;
    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_UNDAMAGED, "WAVE_ENEMY_UNDAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_AFTER_LEAD_MOVING);
    pProg2_ = createProgress(PROG2_CLOSE);
    shot_begin_frame_ = 0;
    pKurokoLeader_ = nullptr;
    pDepoShot_ = nullptr;
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

void EnemyAdelheid::config(GgafLib::SplineKurokoLeader* prm_pKurokoLeader,
                           GgafCore::GgafActorDepository* prm_pDepoShot  ) {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    pKurokoLeader_ = prm_pKurokoLeader;
    pDepoShot_ = prm_pDepoShot;
}

void EnemyAdelheid::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
    setScaleR(0.3);
}

void EnemyAdelheid::onActive() {
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
        case PROG_SPLINE_MOVING: {
            if (_pProg->isJustChanged()) {
            }
            //processJudgement() で pKurokoLeader_->isFinished() 成立待ち
            break;
        }

        //ゴールのパリサナがいない場合、その後の移動
        case PROG_AFTER_LEAD: {
            if (_pProg->isJustChanged()) {
                //もう一回だけ同じスプライン移動する
                pKurokoLeader_->start(SplineKurokoLeader::RELATIVE_DIRECTION);
            }
            //processJudgement() で pKurokoLeader_->isFinished() 成立待ち
            break;
        }
        case PROG_AFTER_LEAD_MOVING: {
            //isOutOfUniverse() 成立待ち
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
                       pDepoShot_,
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

    _pKurokoA->_angveloFace[AXIS_X] = _pKurokoA->_veloMv/2;
    pKurokoLeader_->behave(); //スプライン移動を振る舞い
    _pKurokoA->behave();
    _pMorpher->behave();
}

void EnemyAdelheid::processJudgement() {

    switch (_pProg->get()) {
        case PROG_SPLINE_MOVING: {
            if (pKurokoLeader_->isFinished()) {
                if (((FormationAdelheid*)getFormation())->pPalisana_goal) {
                    //ゴールが存在する場合、そこでさよなら。
                    _pProg->changeNothing();
                    sayonara();
                } else {
                    _pProg->change(PROG_AFTER_LEAD);
                }
            }
            break;
        }

        //ゴールのパリサナがいない場合、その後の移動
        case PROG_AFTER_LEAD: {
            if (pKurokoLeader_->isFinished()) {
                //もう一回のスプライン移動も終わった場合
                _pProg->change(PROG_AFTER_LEAD_MOVING);
            }
            break;
        }
    }

    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAdelheid::onHit(GgafActor* prm_pOtherActor) {
    if (_pMorpher->_weight[MPH_OPEN] > 0.1) {
        bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
        if (was_destroyed) {
            //破壊時
            _pSeTx->play3D(SE_EXPLOSION);
        } else {
            //非破壊時
            _pSeTx->play3D(SE_DAMAGED);
        }
    } else {
        //開いてないので当たらない
        _pSeTx->play3D(SE_UNDAMAGED);
    }
}

void EnemyAdelheid::onInactive() {
}

void EnemyAdelheid::open_shot() {
    pProg2_->change(PROG2_OPEN);
}

EnemyAdelheid::~EnemyAdelheid() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
    GGAF_DELETE(pProg2_);
}


