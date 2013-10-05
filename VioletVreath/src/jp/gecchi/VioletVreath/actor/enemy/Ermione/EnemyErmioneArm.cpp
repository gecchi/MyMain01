#include "stdafx.h"
#include "EnemyErmioneArm.h"
#include "EnemyErmione.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoA.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


EnemyErmioneArm::EnemyErmioneArm(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat) :
        DefaultMeshSetActor(prm_name, prm_model, prm_pStat) {
    _class_name = "EnemyErmioneArm";
    aiming_ang_velo_ = 0;
    aiming_movable_limit_ang_ = 0;

    _pSeTx->set(SE_DAMAGED  , "WAVE_ENEMY_DAMAGED_001");
    _pSeTx->set(SE_EXPLOSION, "WAVE_EXPLOSION_001"); //腕破壊
    useProgress(_BANPEI_-1);
}


void EnemyErmioneArm::initialize() {
}

void EnemyErmioneArm::onActive() {
    _pStatus->reset();
    _pProg->reset(PROG_INIT);
}

void EnemyErmioneArm::processBehavior() {
    switch (_pProg->get()) {
        case PROG_INIT: {
            _pProg->change(PROG_WAITING);
            break;
        }
        case PROG_WAITING: {
            if (_pProg->isJustChanged()) {
                //本体からFKとして追加された直後は、一度processSettlementBehavior()が実行されないと
                //座標反映されない、したがって。１フレーム後のPROG_WAITINGでエントリエフェ実行行う事
                UTIL::activateEntryEffectOf(this);
            }
            break;
        }

        case PROG_NOTHING: {
            if (_pProg->getFrameInProgress() == 10) {
                _pProg->change(PROG_AIMING);
            }
            break;
        }

        case PROG_AIMING: {
            if (_pProg->isJustChanged() ) {
                //自機へ方向を向ける
                //考え方：ローカル座標系で予めどの方向に向いておけば、最終的に自機に向くことになるかを求める
                //
                //自機への向くための変換前状態で、
                //ローカル座標で「向いておけばいいのではないか」の方向のベクトルを(TvX, TvY, TvZ) とおき、
                //「土台まで」の行列の積（_pActor_Base->_matWorldRotMv) を b_mat_xx とする。
                //現在の最終座標から自機への向きのベクトルを、(MvX, MvY, MvZ) とすると、
                //
                //                | b_mat_11 b_mat_12 b_mat_13 |
                //| TvX TvY TvZ | | b_mat_21 b_mat_22 b_mat_23 | = | MvX MvY MvZ |
                //                | b_mat_31 b_mat_32 b_mat_33 |
                //
                //となるはずだ。(TvX, TvY, TvZ)について解く。逆行列を掛けて求めれば良い。
                //
                //                                   | b_mat_11 b_mat_12 b_mat_13 | -1
                // | TvX TvY TvZ | = | MvX MvY MvZ | | b_mat_21 b_mat_22 b_mat_23 |
                //                                   | b_mat_31 b_mat_32 b_mat_33 |
                //

                //MvX MvY MvZ を求める
                int MvX,MvY,MvZ;
                if (RND(1, 60) != 1) {
                    //通常の自機を狙う方向ベクトル
                    GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                    MvX = pTargetActor->_X - _X; //ここでの _X, _Y, _Z は絶対座標であることがポイント
                    MvY = (pTargetActor->_Y + PX_C(50)) - _Y; //自機のやや上を狙う
                    MvZ = pTargetActor->_Z - _Z;
                } else {
                    //たま～に逆方向を目標にして、触手に動きを強要する
                    GgafDxGeometricActor* pTargetActor = P_MYSHIP;
                    MvX = _X - pTargetActor->_X;
                    MvY = _Y - pTargetActor->_Y;
                    MvZ = _Z - pTargetActor->_Z;
                }
                //逆行列取得
                D3DXMATRIX* pBaseInvMatRM = _pActor_Base->getInvMatWorldRotMv();
                //ローカル座標でのターゲットとなる方向ベクトル計算
                int TvX = MvX*pBaseInvMatRM->_11 + MvY*pBaseInvMatRM->_21 + MvZ * pBaseInvMatRM->_31;
                int TvY = MvX*pBaseInvMatRM->_12 + MvY*pBaseInvMatRM->_22 + MvZ * pBaseInvMatRM->_32;
                int TvZ = MvX*pBaseInvMatRM->_13 + MvY*pBaseInvMatRM->_23 + MvZ * pBaseInvMatRM->_33;
                //自動方向向きシークエンス開始
                angle angRz_Target, angRy_Target;
                UTIL::convVectorToRzRy(TvX, TvY, TvZ, angRz_Target, angRy_Target);
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
                _pKurokoA->turnRzRyFaceAngTo(
                                angRz_Target, angRy_Target,
                                aiming_ang_velo_, aiming_ang_velo_*0.05,
                                TURN_CLOSE_TO, false);
            }
            if (_pKurokoA->isTurningMvAng()) {
                // 待機
            } else {
                _pProg->change(PROG_NOTHING);
            }
            break;
        }

        default :
            break;
    }

    //＜注意＞
    //・GgafDxKurokoA(_pKurokoA)の behave() 以外メソッドは、常にローカル座標の操作とする。
    //  behave()以外メソッドは実際に座標計算しているわけではないので、
    //  changeGeoFinal()時、changeGeoLocal()時に関係なく、呼び出し可能。
    //・GgafDxKurokoA(_pKurokoA)の behave() メソッドは座標を１フレーム後の状態にする計算を行う。
    //  したがって、次のように ローカル座標時(changeGeoLocal()時)で呼び出す事とする。
    //    changeGeoLocal();
    //    _pKurokoA->behave();
    //    changeGeoFinal();
    changeGeoLocal();
    _pKurokoA->behave();
    changeGeoFinal();
    //_pScaler->behave();
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
        _pProg->change(PROG_NOTHING);
    }


}

EnemyErmioneArm::~EnemyErmioneArm() {

}
