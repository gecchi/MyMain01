#include "stdafx.h"
#include "EnemyErmioneArm.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperB.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyErmioneArm::EnemyErmioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyErmioneArm";

    aiming_ang_velo_ = 0;
    aiming_movable_limit_ang_ = 0;
    GgafDxSeTransmitterForActor* pSeTx = getSeTx();
    pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001"); //腕破壊
    useProgress(PROG_BANPEI);
    behave_frames_ = 0;
}


void EnemyErmioneArm::initialize() {
}

void EnemyErmioneArm::onActive() {
    _pStatus->reset();
    getProgress()->reset(PROG_INIT);
}

void EnemyErmioneArm::processBehavior() {

    changeGeoLocal(); //ローカル座標の操作とする。
    GgafDxKuroko* pKuroko = getKuroko();
    GgafProgress* pProg = getProgress();
    switch (pProg->get()) {
        case PROG_INIT: {
            pProg->change(PROG_WAITING);
            break;
        }
        case PROG_WAITING: {
            if (pProg->isJustChanged()) {
                //本体からFKとして追加された直後は、一度processSettlementBehavior()が実行されないと
                //座標反映されない、したがって。１フレーム後のPROG_WAITINGでエントリエフェ実行行う事
                UTIL::activateEntryEffectOf(this);
            }
            break;
        }

        case PROG_NOTHING: {
            if (pProg->isJustChanged() ) {
                behave_frames_ = RND(30, 60);
            }
            if (pProg->getFrameInProgress() == behave_frames_) {
                pProg->change(PROG_AIMING);
            }
            break;
        }

        case PROG_AIMING: {
            if (pProg->isJustChanged() ) {
                if (aiming_movable_limit_ang_ > 0) {
                    //自機へ方向を向ける
                    //考え方：ローカル座標系で予めどの方向に向いておけば、最終的に自機に向くことになるかを求める
                    //
                    //自機への向くための変換前状態で、
                    //ローカル座標で「向いておけばいいのではないか」の方向のベクトルを(tvx, tvy, tvz) とおき、
                    //「土台まで」の行列の積（_pActor_Base->_matWorldRotMv) を b_mat_xx とする。
                    //現在の最終座標から自機への向きのベクトルを、(mvx, mvy, mvz) とすると、
                    //
                    //                | b_mat_11 b_mat_12 b_mat_13 |
                    //| tvx tvy tvz | | b_mat_21 b_mat_22 b_mat_23 | = | mvx mvy mvz |
                    //                | b_mat_31 b_mat_32 b_mat_33 |
                    //
                    //となるはずだ。(tvx, tvy, tvz)について解く。逆行列を掛けて求めれば良い。
                    //
                    //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
                    // | tvx tvy tvz | = | mvx mvy mvz | | b_mat_21 b_mat_22 b_mat_23 |
                    //                                   | b_mat_31 b_mat_32 b_mat_33 |
                    //
                    //mvx mvy mvz を求める
                    int mvx,mvy,mvz;
                    if (RND(1, 100) < 96) {
                        //絶対座標系で通常の自機を狙う方向ベクトル
                        GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                        mvx = pTargetActor->_x - _x_final; //ここで自身の _x, _y, _z は絶対座標(_x_final)であることがポイント
                        mvy = (pTargetActor->_y + PX_C(50)) - _y_final; //自機のやや上を狙う
                        mvz = pTargetActor->_z - _z_final;
                    } else {
                        //たま～に逆方向を目標にして、触手に動きを強要する
                        GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                        mvx = _x_final - pTargetActor->_x;
                        mvy = _y_final - pTargetActor->_y;
                        mvz = _z_final - pTargetActor->_z;
                    }
                    //逆行列取得
                    D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
                    //ローカル座標でのターゲットとなる方向ベクトル計算
                    int tvx = mvx*pBaseInvMatRM->_11 + mvy*pBaseInvMatRM->_21 + mvz * pBaseInvMatRM->_31;
                    int tvy = mvx*pBaseInvMatRM->_12 + mvy*pBaseInvMatRM->_22 + mvz * pBaseInvMatRM->_32;
                    int tvz = mvx*pBaseInvMatRM->_13 + mvy*pBaseInvMatRM->_23 + mvz * pBaseInvMatRM->_33;
                    //自動方向向きシークエンス開始
                    angle angRz_Target, angRy_Target;
                    UTIL::convVectorToRzRy(tvx, tvy, tvz, angRz_Target, angRy_Target);
                    //計算の結果、angRz_Target angRy_Target に向けば、自機に向ける

                    //angRz_Target、angRy_Target 可動範囲内に制限する
                    if (aiming_movable_limit_ang_ <= angRz_Target && angRz_Target <= D180ANG) {
                        angRz_Target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= angRz_Target && angRz_Target <= D360ANG - aiming_movable_limit_ang_) {
                        angRz_Target = D360ANG - aiming_movable_limit_ang_;
                    }
                    if (aiming_movable_limit_ang_ <= angRy_Target && angRy_Target <= D180ANG) {
                        angRy_Target = aiming_movable_limit_ang_;
                    } else if (D180ANG <= angRy_Target && angRy_Target <= D360ANG - aiming_movable_limit_ang_) {
                        angRy_Target = D360ANG - aiming_movable_limit_ang_;
                    }

                    pKuroko->turnRzRyFaceAngTo(
                                    angRz_Target, angRy_Target,
                                    aiming_ang_velo_, aiming_ang_velo_*0.04,
                                    TURN_CLOSE_TO, false);
                }
            }
            if (pKuroko->isTurningFaceAng()) {
                // 待機
            } else {
                pProg->change(PROG_NOTHING);
            }

            break;
        }

        default :
            break;
    }

    pKuroko->behave();
    changeGeoFinal();
    //pScaler_->behave();
    if (_pActor_Base) {
        setAlpha(((GgafDxDrawableActor*)_pActor_Base)->getAlpha());
    }
}

void EnemyErmioneArm::processJudgement() {
    if (_pActor_Base != nullptr && _pActor_Base->isActiveInTheTree()) {
    } else {
        //土台がなければ自分も死ぬ
        sayonara();
    }
}


void EnemyErmioneArm::onInactive() {
    sayonara();
}

void EnemyErmioneArm::onCatchEvent(hashval prm_no, void* prm_pSource) {
    if ( prm_no == EVENT_ERMIONE_SAYONARA) {
        //本体破壊時
        setHitAble(false);
        UTIL::activateExplosionEffectOf(this);//爆発エフェ
        sayonara();
    }
    if ( prm_no == EVENT_ERMIONE_ENTRY_DONE) {
        setHitAble(true);
        getProgress()->change(PROG_NOTHING);
    }
}

EnemyErmioneArm::~EnemyErmioneArm() {
}
