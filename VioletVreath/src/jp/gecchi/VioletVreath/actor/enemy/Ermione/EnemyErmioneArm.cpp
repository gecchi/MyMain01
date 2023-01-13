#include "EnemyErmioneArm.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleFaceAngAssistant.h"
#include "jp/gecchi/VioletVreath/actor/effect/Blink/EffectBlink.h"

using namespace GgafLib;
using namespace VioletVreath;

EnemyErmioneArm::EnemyErmioneArm(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset) :
        VvEnemyActor<DefaultMeshSetActor>(prm_name, prm_model, prm_pFuncStatusReset) {
    _class_name = "EnemyErmioneArm";

    aiming_ang_velo_ = 0;
    aiming_movable_limit_ang_ = 0;
    GgafDx::SeTransmitterForActor* pSeTx = getSeTransmitter();
    pSeTx->set(SE_DAMAGED  , "SE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "SE_EXPLOSION_001"); //腕破壊
    behave_frames_ = 0;
    arm_no_ = 0;
    arm_part_no_ = 0;
}


void EnemyErmioneArm::initialize() {
}

void EnemyErmioneArm::onActive() {
    getStatus()->reset();
    getPhase()->reset(PHASE_INIT);
}

void EnemyErmioneArm::processBehavior() {

    changeGeoLocal(); //ローカル座標の操作とする。
    GgafDx::VecVehicle* pVecVehicle = getVecVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_WAITING);
            break;
        }
        case PHASE_WAITING: {
            if (pPhase->hasJustChanged()) {
                //本体からFKとして追加された直後は、一度processSettlementBehavior()が実行されないと
                //座標反映されない、したがって。１フレーム後のPHASE_WAITINGでエントリエフェ実行行う事
                UTIL::activateEntryEffectOf(this);
            }
            break;
        }

        case PHASE_NOTHING: {
            if (pPhase->hasJustChanged() ) {
                behave_frames_ = RND(1, 10);
            }
            if (pPhase->hasArrivedFrameAt(behave_frames_)) {
                pPhase->change(PHASE_AIMING);
            }
            break;
        }

        case PHASE_AIMING: {
            if (pPhase->hasJustChanged() ) {
                if (aiming_movable_limit_ang_ > 0) {
                    //自機へ方向を向ける
                    //考え方：ローカル座標系で予めどの方向に向いておけば、最終的に自機に向くことになるかを求める
                    //
                    //自機への向くための変換前状態で、
                    //ローカル座標で「向いておけばいいのではないか」の方向のベクトルを(tvx, tvy, tvz) とおき、
                    //「土台まで」の行列の積（_pActor_base->_matWorldRotMv) を b_mat_xx とする。
                    //現在の最終座標から自機への向きのベクトルを、(mvx, mvy, mvz) とすると、
                    //
                    // | b_mat_11 b_mat_12 b_mat_13 | |tvx|   |mvx|
                    // | b_mat_21 b_mat_22 b_mat_23 | |tvy| = |mvy|
                    // | b_mat_31 b_mat_32 b_mat_33 | |tvz|   |mvz|
                    //
                    //となるはずだ。(tvx, tvy, tvz)について解く。逆行列を掛けて求めれば良い。
                    //
                    // |tvx|   | b_mat_11 b_mat_12 b_mat_13 | -1  |mvx|
                    // |tvy| = | b_mat_21 b_mat_22 b_mat_23 |     |mvy|
                    // |tvz|   | b_mat_31 b_mat_32 b_mat_33 |     |mvz|
                    //
                    //mvx mvy mvz は、自機への方向ベクトルである
                    int mvx,mvy,mvz;
                    if (RND(1, 1000) < 960 || arm_part_no_ >= 9) {
                        //絶対座標系で通常の自機を狙う方向ベクトル
                        GgafDx::GeometricActor* pTargetActor = pMYSHIP;
                        mvx = pTargetActor->_x - _x_final; //ここで自身の _x, _y, _z は絶対座標(_x_final)であることがポイント
                        mvy = (pTargetActor->_y + PX_C(50)) - _y_final; //自機のやや上を狙う
                        mvz = pTargetActor->_z - _z_final;
                    } else {
                        //たま～に逆方向を目標にして、触手に動きを強要する
                        GgafDx::GeometricActor* pTargetActor = pMYSHIP;
                        mvx = _x_final - pTargetActor->_x;
                        mvy = _y_final - pTargetActor->_y;
                        mvz = _z_final - pTargetActor->_z;
                    }
                    //逆行列取得
                    D3DXMATRIX* pBaseInvMatRM = getBaseActor()->getInvMatWorldRotMv();
                    //ローカル座標でのターゲットとなる方向ベクトル計算
                    int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz*pBaseInvMatRM->_31;
                    int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz*pBaseInvMatRM->_32;
                    int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz*pBaseInvMatRM->_33;
                    //自動方向向きシークエンス開始
                    angle rz_target, ry_target;
                    UTIL::convVectorToRzRy(tvx, tvy, tvz, rz_target, ry_target);
                    //計算の結果、rz_target ry_target に向けば、自機に向ける

                    //rz_target、ry_target 可動範囲内に制限する
                    if (aiming_movable_limit_ang_ <= rz_target && rz_target <= D180ANG) {
                        rz_target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= rz_target && rz_target <= D360ANG - aiming_movable_limit_ang_) {
                        rz_target = D360ANG - aiming_movable_limit_ang_;
                    }
                    if (aiming_movable_limit_ang_ <= ry_target && ry_target <= D180ANG) {
                        ry_target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= ry_target && ry_target <= D360ANG - aiming_movable_limit_ang_) {
                        ry_target = D360ANG - aiming_movable_limit_ang_;
                    }

                    pVecVehicle->turnRzRyFaceAngTo(
                                    rz_target, ry_target,
                                    aiming_ang_velo_, aiming_ang_velo_*0.01,
                                    TURN_CLOSE_TO, false);
                }
            }
            if (pVecVehicle->isTurningFaceAng()) {
                // 待機
            } else {
                pPhase->change(PHASE_NOTHING);
            }

            break;
        }

        default :
            break;
    }

    pVecVehicle->behave();
    changeGeoFinal();
    //pScaler_->behave();
    if (_pActor_base) {
        setAlpha(((GgafDx::FigureActor*)_pActor_base)->getAlpha());
    }
}

void EnemyErmioneArm::processJudgement() {
    if (getBaseActor() && getBaseActor()->isActiveInTheTree()) {
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }
}


void EnemyErmioneArm::onInactive() {
    sayonara();
}

void EnemyErmioneArm::onCatchEvent(eventval prm_event_val, void* prm_pSource) {
    if ( prm_event_val == EVENT_ERMIONE_SAYONARA) {
        //本体破壊時
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);//爆発エフェ
        sayonara();
    }
    if ( prm_event_val == EVENT_ERMIONE_ENTRY_DONE) {
        setHitAble(true);
        getPhase()->change(PHASE_NOTHING);
    }
}

EnemyErmioneArm::~EnemyErmioneArm() {
}
