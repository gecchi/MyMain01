#include "EnemyRis.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/model/supporter/GgafDxTextureBlinker.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyRis::EnemyRis(const char* prm_name)
      : DefaultMeshSetActor(prm_name, "Ris", STATUS(EnemyRis)) {
    _class_name = "EnemyRis";
    iMovePatternNo_ = 0;
    pKurokoLeader_ = nullptr;
    pDepo_shot_ = nullptr;
    pDepo_effect_ = nullptr;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");     //爆発
}

void EnemyRis::onCreateModel() {
    GgafDxModel* pModel = getModel();
    pModel->setBlinkPower(0.5, 0.9);
    pModel->getTexBlinker()->setRange(0.5, 2.0);
    pModel->getTexBlinker()->beat(60, 3, 0, 57, -1);
}

void EnemyRis::initialize() {
    setHitAble(true);
    GgafDxKuroko* const pKuroko = getKuroko();
    pKuroko->linkFaceAngByMvAng(true);
    pKuroko->setRollFaceAngVelo(5000);
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliAAB(0, -30000, -30000, -30000, 30000, 30000, 30000);
}

void EnemyRis::onActive() {
    getStatus()->reset();
    iMovePatternNo_ = 0; //行動パターンリセット
}

void EnemyRis::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* const pKuroko = getKuroko();
    switch (iMovePatternNo_) {
        case 0:  //【パターン０：スプライン移動開始】
            if (pKurokoLeader_) {
                pKurokoLeader_->start(ABSOLUTE_COORD); //スプライン移動を開始
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
            if (pDepo_shot_) {
                //放射状ショット
                int way = RF_EnemyRis_ShotWay(G_RANK); //ショットWAY数
                UTIL::shotWay004(_x, _y, _z,
                                 D180ANG, D0ANG,
                                 pDepo_shot_,
                                 PX_C(20), way, D_ANG(120),
                                 0, 0,  //ショット側で速度を設定
                                 1, 0, 1.0,
                                 nullptr );
                //ショット発射エフェクト
                if (pDepo_effect_) {
                    GgafDxFigureActor* pTestActor_Shot = (GgafDxFigureActor*)pDepo_effect_->dispatch();
                    if (pTestActor_Shot) {
                        pTestActor_Shot->positionAs(this);
                    }
                }
            }
            //自機へ方向転換
            pKuroko->turnMvAngTwd(P_MYSHIP,
                                  3000, 0,
                                  TURN_CLOSE_TO, true);
            iMovePatternNo_++; //次の行動パターンへ
            break;

        case 3:  //【行動パターン３：自機へグルッと逆回転で方向転換開始】
            if (_z-10000 < P_MYSHIP->_z && P_MYSHIP->_z < _z+10000) {
                //自機とZ軸が接近したらグルッと逆回転で方向転換
                pKuroko->turnMvAngTwd(MyShip::lim_x_behaind_ - 500000 , _y, _z,
                                      10000, 0,
                                      TURN_CLOSE_TO, true);
                pKuroko->setMvAcce(100);
                iMovePatternNo_++;
            } else {
                //自機とZ軸が接近するまで待つ
            }
            break;
        default:
            break;
    }


    if (pKurokoLeader_) {
        pKurokoLeader_->behave(); //スプライン移動を振る舞い
    }
    pKuroko->behave();
    //getSeTx()->behave();
}

void EnemyRis::processJudgement() {
    if (isOutOfSpacetime()) {
        sayonara();
    }
}

void EnemyRis::onHit(const GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (const GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊された時(スタミナ <= 0)
        getSeTx()->play3D(SE_EXPLOSION);
        sayonara();
    } else {
        //破壊されなかった時(スタミナ > 0)
    }
}

void EnemyRis::onInactive() {
    sayonara();
}

EnemyRis::~EnemyRis() {
    GGAF_DELETE_NULLABLE(pKurokoLeader_);
}
