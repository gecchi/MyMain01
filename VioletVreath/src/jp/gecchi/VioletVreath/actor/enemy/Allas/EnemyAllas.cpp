#include "stdafx.h"
#include "EnemyAllas.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyAllas::EnemyAllas(const char* prm_name) :
        DefaultMeshSetActor(prm_name, "Allas", STATUS(EnemyAllas)) {
    _class_name = "EnemyAllas";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_Shot_ = nullptr;
    pDepo_ShotEffect_ = nullptr;
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
    useProgress(10);
}

void EnemyAllas::onCreateModel() {
    _pModel->setSpecular(5.0, 1.0);
}

void EnemyAllas::initialize() {
    setHitAble(true);
    _pKurokoA->setFaceAngVelo(AXIS_Z, -7000);
    _pKurokoA->relateFaceWithMvAng(true);
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliAAB_Cube(0, 40000);
}

void EnemyAllas::onActive() {
    if (pKurokoLeader_ == nullptr) {
        throwGgafCriticalException("EnemyAllasはスプライン必須ですconfigして下さい");
    }

    _pStatus->reset();
   iMovePatternNo_ = 0; //行動パターンリセット
    _pProg->change(1);
}

void EnemyAllas::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));

    //【パターン1：スプライン移動】
    if (_pProg->isJustChangedTo(1)) {
        pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
    }
    if (_pProg->get() == 1) {
        //スプライン移動終了待ち
        if (pKurokoLeader_->isFinished()) {
            _pProg->changeNext(); //次のパターンへ
        }
    }

    switch (iMovePatternNo_) {
        case 0:  //【パターン０：スプライン移動開始】
            if (pKurokoLeader_) {
                pKurokoLeader_->start(SplineKurokoLeader::ABSOLUTE_COORD); //スプライン移動を開始(1:座標相対)
            }
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 1:  //【パターン１：スプライン移動終了待ち】
            if (pKurokoLeader_) {
                //スプライン移動有り
                if (pKurokoLeader_->isFinished()) {
                    iMovePatternNo_++; //スプライン移動が終了したら次の行動パターンへ
                }
            } else {
                //スプライン移動無し
                iMovePatternNo_++; //すぐに次の行動パターンへ
            }
            break;

        case 2:  //【パターン２：放射状ショット発射と自機へ方向転換】
            if (pDepo_Shot_) {
                //放射状ショット
                int way = RF_EnemyAllas_ShotWay(G_RANK); //ショットWAY数
                angle* paAng_way = NEW angle[way];
                UTIL::getRadialAngle2D(0, way, paAng_way);
                GgafDxDrawableActor* pActor_Shot;
                for (int i = 0; i < way; i++) {
                    pActor_Shot = (GgafDxDrawableActor*)pDepo_Shot_->dispatch();
                    if (pActor_Shot) {
                        pActor_Shot->positionAs(this);
                        pActor_Shot->_pKurokoA->setRzRyMvAng(paAng_way[i], D90ANG);
                        pActor_Shot->activate();
                    }
                }
                GGAF_DELETEARR(paAng_way);
                //ショット発射エフェクト
                if (pDepo_ShotEffect_) {
                    GgafDxDrawableActor* pTestActor_Shot = (GgafDxDrawableActor*)pDepo_ShotEffect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->positionAs(this);
                    }
                }
            }
//            //自機へ方向転換
            _pKurokoA->turnMvAngTwd(P_MYSHIP->_x, _y, P_MYSHIP->_z,
                                    2000, 0,
                                    TURN_CLOSE_TO, true);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３】

            break;
        default:
            break;
    }

    if (pKurokoLeader_) {
        pKurokoLeader_->behave(); //スプライン移動を振る舞い
    }
    _pKurokoA->behave();
    //_pSeTx->behave();
}

void EnemyAllas::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyAllas::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
    } else {
        //非破壊時
    }
}

void EnemyAllas::onInactive() {
    sayonara();
}

EnemyAllas::~EnemyAllas() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
