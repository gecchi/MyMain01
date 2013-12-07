#include "stdafx.h"
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


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

EnemyErmione::EnemyErmione(const char* prm_name) :
        DefaultMorphMeshActor(prm_name, "1/Ermione", STATUS(EnemyErmione)) {
    _class_name = "EnemyErmione";

    num_arm_ = 6; //腕の合計本数
    num_arm_part_ = 11;  //各腕の節数（3以上）
    angle pos_rz[] = {D_ANG(0),   D_ANG(90),   D_ANG(180),  D_ANG(270), D_ANG(0) , D_ANG(0)  }; //生やす場所
    angle pos_ry[] = {D_ANG(0),   D_ANG(0),    D_ANG(0)  ,  D_ANG(0)  , D_ANG(90), D_ANG(270) };
    static coord R = PX_C(100);     //本体Ermioneの半径
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
    //ArmPart(頭)          ArmPart(頭)          ArmPart(頭)

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
                paArm_[arm].papArmPart_[i]->config(D_ANG(10+(i*4)), 30+(i*20));
                //一つ前の腕の節を土台とするFK設定
                paArm_[arm].papArmPart_[i-1]->addSubGroupAsFk(
                                               paArm_[arm].papArmPart_[i],
                                               arm_R, 0, 0,
                                               D0ANG, D0ANG, D0ANG);
            }
        }
    }

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001");
    useProgress(PROG_BANPEI);
}

void EnemyErmione::onCreateModel() {
}

void EnemyErmione::initialize() {
    _pColliChecker->makeCollision(1);
    _pColliChecker->setColliSphere(0, 90000);
}

void EnemyErmione::onActive() {
    _pStatus->reset();
    _pMorpher->setWeight(0, 1.0);
    _pMorpher->setWeight(1, 0.0);

    _pProg->reset(PROG_INIT);
    setHitAble(false);
}

void EnemyErmione::processBehavior() {
    //加算ランクポイントを減少
    _pStatus->mul(STAT_AddRankPoint, _pStatus->getDouble(STAT_AddRankPoint_Reduction));
    switch (_pProg->get()) {
        case PROG_INIT: {
            setHitAble(false);
            _pAFader->setAlpha(0);
            _pKuroko->setMvVelo(0);
            UTIL::activateEntryEffectOf(this);
            _pProg->changeNext();
            break;
        }

        case PROG_ENTRY: {
            if (_pProg->getFrameInProgress() == 120) {
                _pAFader->fadeAcceStep(1.0, 0.000, 0.0001);
            }
            if (getAlpha() > 0.8) {
                setHitAble(true);
                throwEventLowerTree(EVENT_ERMIONE_ENTRY_DONE);
                _pKuroko->setMvVelo(10);
                _pKuroko->turnFaceAngTwd(P_MYSHIP,
                                          300, 0,
                                          TURN_ANTICLOSE_TO, false);
                _pKuroko->setMvAngTwd(P_MYSHIP);
                _pProg->changeNext();
            }
            break;
        }

        case PROG_MOVE: {
            if (_pProg->isJustChanged()) {
                _pKuroko->setFaceAngVelo(AXIS_X, 150);
                _pKuroko->setFaceAngVelo(AXIS_Y, 130);
                _pKuroko->setFaceAngVelo(AXIS_Z, 110);
            }
            break;
        }

        default:
            break;
    }
    _pAFader->behave();
    _pKuroko->behave();
    _pMorpher->behave();
    _pSeTx->behave();
}

void EnemyErmione::processJudgement() {
    if (isOutOfUniverse()) {
        sayonara();
    }
}

void EnemyErmione::onHit(GgafActor* prm_pOtherActor) {
    bool was_destroyed = UTIL::proceedEnemyHit(this, (GgafDxGeometricActor*)prm_pOtherActor);
    if (was_destroyed) {
        //破壊時
        _pSeTx->play3D(SE_EXPLOSION);
        throwEventLowerTree(EVENT_ERMIONE_SAYONARA);
    } else {
        //非破壊時
        _pSeTx->play3D(SE_DAMAGED);
    }
}

void EnemyErmione::onInactive() {
    //sayonara();
}

void EnemyErmione::addArm(angle prm_rz, angle prm_ry) {

}

EnemyErmione::~EnemyErmione() {
    GGAF_DELETEARR(paArm_);
}
