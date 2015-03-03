#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAlphaFader.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmWeak.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmHead.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArmBody.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantB.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmione::EnemyErmione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ermione", STATUS(EnemyErmione)) {
    _class_name = "EnemyErmione";
    pAFader_ = NEW GgafDxAlphaFader(this);
    num_arm_ = 6; //腕の合計本数
    num_arm_part_ = 11;  //各腕の節数（3以上）
    angle pos_rz[] = {D_ANG(0),   D_ANG(90),   D_ANG(180),  D_ANG(270), D_ANG(0) , D_ANG(0)  }; //生やす場所
    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)  ,  D_ANG(0)  , D_ANG(90), D_ANG(270) };
    static coord R = PX_C(130);     //本体Ermioneの半径
    static coord arm_R = PX_C(45);  //可動部の腕の関節１個の半径

    //次のようなツリー構造を作る(腕が３本の場合)
    //Ermione
    // ↓
    //GroupHead()
    // ↓
    //ArmPart(根本)  ⇔   ArmPart(根本)   ⇔  ArmPart(根本)
    // ↓                   ↓                  ↓
    //ArmPart              ArmPart             ArmPart
    // ↓                   ↓                  ↓
    //ArmPart(弱点)        ArmPart(弱点)       ArmPart(弱点)
    // ↓                   ↓                  ↓
    //ArmPart              ArmPart             ArmPart
    // ↓                   ↓                  ↓
    //ArmPart              ArmPart             ArmPart
    // ↓                   ↓                  ↓
    //ArmPart(頭)          ArmPart(頭)         ArmPart(頭)

    paArm_ = NEW EnemyErmione::Arm[num_arm_];
    float vx, vy, vz;
    for (int arm = 0; arm < num_arm_; arm++) { //腕の本数でループ
        paArm_[arm].pos_Rz_ = pos_rz[arm];
        paArm_[arm].pos_Ry_ = pos_ry[arm];
        UTIL::convRzRyToVector(paArm_[arm].pos_Rz_, paArm_[arm].pos_Ry_,
                               vx, vy, vz); //腕をつける方向のベクトル
        paArm_[arm].papArmPart_ = NEW EnemyErmioneArm*[num_arm_part_];

        for (int i = 0; i < num_arm_part_; i++) { //腕の胴体(関節)
            if (i == (num_arm_part_-1)/2) {
                //腕の節の弱点部分(腕の節数の半分あたりに弱点節を作成する)
                paArm_[arm].papArmPart_[i] = NEW EnemyErmioneArmWeak("ArmWeak");
            } else if (i == num_arm_part_-1) {
                //腕の節の先頭部分
                paArm_[arm].papArmPart_[i] = NEW EnemyErmioneArmHead("ArmHead");
            } else {
                //普通の腕の節
                paArm_[arm].papArmPart_[i] = NEW EnemyErmioneArmBody("ArmBody");
            }
            if (i == 0) {
                //節が根本の場合
                //関節固定させる
                paArm_[arm].papArmPart_[i]->config(0, 0);
                //自身を土台とするFK設定
                this->addSubGroupAsFk(
                        paArm_[arm].papArmPart_[i],
                        vx*R, vy*R, vz*R,
                        D0ANG, paArm_[arm].pos_Ry_, paArm_[arm].pos_Rz_);
            } else {
                //節が根本以外場合
                //先に行くほど可動範囲と回転スピードが大きくする（これで、FKなのにIKっぽくも見える！）
                paArm_[arm].papArmPart_[i]->config(D_ANG(10+(i*2.5)), 20+(i*60));
                //一つ前の腕の節を土台とするFK設定
                paArm_[arm].papArmPart_[i-1]->addSubGroupAsFk(
                                               paArm_[arm].papArmPart_[i],
                                               arm_R, 0, 0,
                                               D0ANG, D0ANG, D0ANG); //土台移行は真っ直ぐつけるので Face rz,ry=0,0 で良い
            }
        }
    }
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyErmione::onCreateModel() {
}

void EnemyErmione::initialize() {
    CollisionChecker3D* pChecker = getCollisionChecker();
    pChecker->makeCollision(1);
    pChecker->setColliSphere(0, 90000);
}

void EnemyErmione::onActive() {
    getStatus()->reset();
    setMorphWeight(1, 0.0);

    getProgress()->reset(PROG_INIT);
    setHitAble(false);
}

void EnemyErmione::processBehavior() {
    //加算ランクポイントを減少
    UTIL::updateEnemyRankPoint(this);
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            setAlpha(0);
            pKuroko->setMvVelo(10);
            UTIL::activateEntryEffectOf(this);
            pProg->changeNext();
            break;
        }

        case PROG_ENTRY: {
            if (pProg->hasArrivedAt(120)) {
                pAFader_->transitionAcceStep(1.0, 0.000, 0.0001);
            }
            if (getAlpha() > 0.8) {
                setHitAble(true);
                throwEventLowerTree(EVENT_ERMIONE_ENTRY_DONE);
                pKuroko->setMvAngTwd(P_MYSHIP);
                pKuroko->setMvVelo(10);
                pKuroko->asstB()->turnFaceAngByDtTwd(
                        P_MYSHIP, TURN_CLOSE_TO, true, 60*30,
                        0.4, 0.6, 0, true);

                pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE: {
            if (pProg->isJustChanged()) {
                pKuroko->setFaceAngVelo(AXIS_X, 15);
                pKuroko->setFaceAngVelo(AXIS_Y, 13);
                pKuroko->setFaceAngVelo(AXIS_Z, 11);
            }
            break;
        }

        default: {
            break;
        }
    }
    pAFader_->behave();
    pKuroko->behave();
    getMorpher()->behave();
    getSeTx()->behave();
}

void EnemyErmione::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyErmione::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::transactEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        getSeTx()->play3D(SE_EXPLOSION);
        throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
    } else {
        //非破壊時
        getSeTx()->play3D(SE_DAMAGED);
    }
}

void EnemyErmione::onInactive() {
    //sayonara();
}

void EnemyErmione::addArm(angle prm_rz, angle prm_ry) {

}

EnemyErmione::~EnemyErmione() {
    GGAF_DELETE(pAFader_);
    GGAF_DELETEARR(paArm_);
}
