#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxAxesMover.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxSeTransmitterForActor.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/texture/GgafDxTexture.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Main.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

const int MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(180); //この値を大きくすると、最高速度が早くなる。
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 16; //この値を大きくすると、カーブが緩くなる
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //計算簡素化用
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;


#define AIM_TIME_OUT (900)

MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyBunshinWateringLaserChip001", STATUS(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    pAxsMver_ = NEW GgafDxAxesMover(this);
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001::onCreateModel() MyBunshinWateringLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    _tmp_x = _x;
    _tmp_y = _y;
    _tmp_z = _z;
    _tmp_acc_vx = _tmp_acc_vy = _tmp_acc_vz = 0;
    pAimInfo_ = nullptr;
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(40000);
    setHitAble(true);
    setScaleR(6.0);
    setAlpha(0.99);
    pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
    pAxsMver_->forceVxyzMvAcceRange(-MAX_ACCE_RENGE, MAX_ACCE_RENGE);
}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockon_ = pOrg_->pLockonCtrler_->pMainLockonEffect_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    WateringLaserChip::onActive();
    pAimInfo_ = nullptr;
}

void MyBunshinWateringLaserChip001::processBehavior() {
    frame active_frame = getActiveFrame();
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;
    if (active_frame >= AIM_TIME_OUT*2) {
        sayonara(); //保険のタイムアウト
    } else if (active_frame < 6 || pAimInfo->pTarget == nullptr) {
        //なにもしない
    } else {
        GgafDxGeometricActor* pAimTarget = pAimInfo->pTarget;
        if (pAimTarget) {

            //先端チップ時（消える可能性のあるLeaderChipにあらず！）、T1が相変わらずロックオンターゲットならば更新
            if (getInfrontChip() == nullptr && pAimTarget == pLockon_->pTarget_ && pAimInfo_->_spent_frames_to_t1 < AIM_TIME_OUT) {
                pAimInfo->t1_x = pAimTarget->_x; //t1更新
                pAimInfo->t1_y = pAimTarget->_y;
                pAimInfo->t1_z = pAimTarget->_z;
            }

            MyBunshinWateringLaserChip001* pAimLeaderChip = pAimInfo->pLeaderChip_;
            if (this == pAimLeaderChip) {

                if (pAimInfo->_spent_frames_to_t1 == 0) {
                    //●Leader が t1 へ Aim
                    if (pAimTarget->isActiveInTheTree() && getActiveFrame() < AIM_TIME_OUT)  {
                        //pAimTarget が存命
                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );
                        static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO_RENGE;
                        if (_x >= pAimInfo->t1_x - renge) {
                            if (_x <= pAimInfo->t1_x + renge) {
                                if (_y >= pAimInfo->t1_y - renge) {
                                    if (_y <= pAimInfo->t1_y + renge) {
                                        if (_z >= pAimInfo->t1_z - renge) {
                                            if (_z <= pAimInfo->t1_z + renge) {
                                                 pAimInfo_->_spent_frames_to_t1 = getActiveFrame(); //Aim t1 終了
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        //初めは pAimTarget があったのに、途中で消えた。
                        pAimInfo_->_spent_frames_to_t1 = getActiveFrame(); //Aim t1 終了
                    }


                } else if (pAimInfo->_spent_frames_to_t2 == 0) {
                    //●Leader が t1 へ Aim し終わったあと
                    //t2を決める旅、onInactive消滅か、或いは、タイムアウト待ち
                    if (getActiveFrame() < AIM_TIME_OUT)  {
                        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                        if (pB) {
                            coord dx = _x - pB->_x;
                            coord dy = _y - pB->_y;
                            coord dz = _z - pB->_z;
                            aimChip(_x + dx*4+1,
                                    _y + dy*4+1,
                                    _z + dz*4+1 );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    } else {
                        pAimInfo_->_spent_frames_to_t2 = getActiveFrame(); //Aim t2 終了
                    }
                    pAimInfo->t2_x = pAimLeaderChip->_x;
                    pAimInfo->t2_y = pAimLeaderChip->_y;
                    pAimInfo->t2_z = pAimLeaderChip->_z;
                } else {
                    //●Leader が t2 を設定したあと。

                    if (getActiveFrame() < AIM_TIME_OUT)  {
                        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
                        if (pB) {
                            coord dx = _x - pB->_x;
                            coord dy = _y - pB->_y;
                            coord dz = _z - pB->_z;
                            aimChip(_x + dx*4+1,
                                    _y + dy*4+1,
                                    _z + dz*4+1 );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    } else {
                        aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                _y + pAxsMver_->_velo_vy_mv*4+1,
                                _z + pAxsMver_->_velo_vz_mv*4+1 );
                    }
                }

            } else {

                if (pAimInfo->_spent_frames_to_t1 == 0) {
                    //●Leader以外が t1 が定まるまでの動き
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame < pAimInfo->_spent_frames_to_t1) {
                    //●Leader以外が t1 が定まってから t1 到達までの動き
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame >= pAimInfo->_spent_frames_to_t1) {
                    //●Leader以外が t1 を通過
                    if (pAimInfo->_spent_frames_to_t2 == 0) {
                        //●その後 Leader以外が t2 が定まるまでの動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    } else if (active_frame < pAimInfo->_spent_frames_to_t2) {
                        //●その後 Leader以外が t2 が定まって、t2に向かうまでの動き
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else if (active_frame >= pAimInfo->_spent_frames_to_t2) {
                        //●その後 Leader以外が t2 を通過した後の動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pAxsMver_->_velo_vx_mv*4+1,
                                    _y + pAxsMver_->_velo_vy_mv*4+1,
                                    _z + pAxsMver_->_velo_vz_mv*4+1 );
                        }
                    }
                }
            }

        }

    }

    pAxsMver_->behave();
    WateringLaserChip::processBehavior();
    _tmp_x = _x;
    _tmp_y = _y;
    _tmp_z = _z;
    _tmp_acc_vx =  pAxsMver_->_acce_vx_mv;
    _tmp_acc_vy =  pAxsMver_->_acce_vy_mv;
    _tmp_acc_vz =  pAxsMver_->_acce_vz_mv;

}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //分身はFKなので、絶対座標の確定が processSettlementBehavior() 以降となるため、ここで初期設定が必要
    if (hasJustChangedToActive()) {
        //チップの初期設定

        //ロックオン情報の引き継ぎ
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        if (pF == nullptr) {
            //先端チップ
            GgafDxGeometricActor* pLockonTarget = pLockon_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //先端でロックオン中
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip_ = this;
                pAimInfo_->pTarget = pLockonTarget;
                pAimInfo_->t1_x = pAimInfo_->pTarget->_x;
                pAimInfo_->t1_y = pAimInfo_->pTarget->_y;
                pAimInfo_->t1_z = pAimInfo_->pTarget->_z;
                pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
            } else {
                //先端でロックオンしていない
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip_ = this;
                pAimInfo_->pTarget = nullptr;
                pAxsMver_->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
            }
        } else {
            //先端以外は前のを受け継ぐ
            pAimInfo_ = pF->pAimInfo_; //受け継ぐ
            coord velo = pF->pAxsMver_->_top_velo_vx_mv - PX_C(0.5);
            pAxsMver_->forceVxyzMvVeloRange(-velo, velo);
        }

        //活動開始初回フレーム、チップの速度と向きの初期設定
        setFaceAngAs(pOrg_);
        positionAs(pOrg_);
        pAxsMver_->setVxyzMvVeloTwd(_rz, _ry, PX_C(100)); //初速はここで
        pAxsMver_->setZeroVxyzMvAcce();
    }

    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。
    if (getActiveFrame() > 4) { //FKオブジェクトからのレーザー発射も考慮すると、_tmpXYZ が埋まるのは3フレーム以降。
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
        if (pF && pB && pF->isActive() && pB->isActive()) {
            //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
            //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
            //_x,_y,_z にはまだ変な値が入っている。
            //中間座標に再設定
            _x = ((pF->_tmp_x + pB->_tmp_x)/2 + _tmp_x)/2;
            _y = ((pF->_tmp_y + pB->_tmp_y)/2 + _tmp_y)/2;
            _z = ((pF->_tmp_z + pB->_tmp_z)/2 + _tmp_z)/2;
            pAxsMver_->setVxyzMvAcce( ( ((pF->_tmp_acc_vx + pB->_tmp_acc_vx)/2) + _tmp_acc_vx)/2,
                                      ( ((pF->_tmp_acc_vy + pB->_tmp_acc_vy)/2) + _tmp_acc_vy)/2,
                                      ( ((pF->_tmp_acc_vz + pB->_tmp_acc_vz)/2) + _tmp_acc_vz)/2 );
        }
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        if (pAimInfo_->pLeaderChip_ == this) {
            pAimInfo_->t2_x = _x;
            pAimInfo_->t2_y = _y;
            pAimInfo_->t2_z = _z;
            pAimInfo_->_spent_frames_to_t2 = getActiveFrame();

            if (pAimInfo_->_spent_frames_to_t1 == 0) {
                pAimInfo_->t1_x = pAimInfo_->t2_x;
                pAimInfo_->t1_y = pAimInfo_->t2_y;
                pAimInfo_->t1_z = pAimInfo_->t2_z;
                pAimInfo_->_spent_frames_to_t1 = getActiveFrame();
            }
        }
        sayonara();
    }
}


void MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ) {
    //    |                            vVT 仮的                        |
    //    |                                ^ ┌                        |
    //    |                 |仮的| > 5*vM /    ＼  vVP 仮自→仮的      |      仮的
    //    |                 となるような /       ＼                    |       ↑
    //    |                 vVTを設定   /         ┐                   |      仮自
    //    |                            /        ／vVM  仮自            |       ↑
    //    |                           /       ／  (vVMx,vVMy,vVMz)     |       ｜
    //    |                          /      ／                         |       ｜
    //    |                         /     ／                           |       ｜
    //    |                        /    ／ |仮自| = lVM * 5            |       ｜
    //    |                   vT 的   ／                               |       的
    //    |             ┌       ^  ／                                 |       ↑
    //    |               ＼    / ┐vM 現在の移動方向ベクトル          |       ｜
    //    | vVP 仮自→仮的  ＼ /／ (veloVxMv_,veloVyMv_,veloVzMv_)     |       ｜
    //    |                   自                                       |       自
    // ---+------------------------------------------               ---+---------------------------
    //    |                                                            |
    //
    // vVP が動きたい方向。vVPを求める！
#ifdef MY_DEBUG
    if (tX == INT_MAX) {
        throwGgafCriticalException("おかしい");
    }
#endif
    GgafDxAxesMover* pAxsMver = pAxsMver_;

    //自→的
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //自→仮自。
    const int vVMx = pAxsMver->_velo_vx_mv;
    const int vVMy = pAxsMver->_velo_vy_mv;
    const int vVMz = pAxsMver->_velo_vz_mv;
    //|仮自| = lVM * 5
    const int lVM = MAX3(ABS(vVMx), ABS(vVMy), ABS(vVMz)); //仮自ベクトル大きさ簡易版
    //|的|
    const int lT =  MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //的ベクトル大きさ簡易版
    //|仮自|/|的|      vT の何倍が vVT 仮的 になるのかを求める。
    const double r = (lVM*5 * 1.5) / lT;
    //* 1.5は 右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

    //vVP 仮自→仮的 の加速度設定
    const double accX = ((vTx * r) - vVMx*5) * RR_MAX_ACCE;
    const double accY = ((vTy * r) - vVMy*5) * RR_MAX_ACCE;
    const double accZ = ((vTz * r) - vVMz*5) * RR_MAX_ACCE;

    pAxsMver->setVxyzMvAcce(accX + SGN(accX)*3.0,
                            accY + SGN(accY)*3.0,
                            accZ + SGN(accZ)*3.0);
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現

    if ((pOther->getKind() & KIND_ENEMY_BODY) ) {

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }

getStatus()->set(STAT_Stamina, default_stamina_);
//sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
            //ロックオン可能アクターならロックオン
            if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
                pOrg_->pLockonCtrler_->lockon(pOther);
            }
        }

        if (this == pAimInfo_->pLeaderChip_ && pAimInfo_->pTarget == prm_pOtherActor) {
            //先端が目標に見事命中した場合もT1終了
            pAimInfo_->t1_x = _x;
            pAimInfo_->t1_y = _y;
            pAimInfo_->t1_z = _z;
            pAimInfo_->_spent_frames_to_t1 = getActiveFrame();
        }


    } else if (pOther->getKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;

    if (pAimInfo->pLeaderChip_ == this) {
        if (pAimInfo->_spent_frames_to_t2 == 0) {
            static const Spacetime* pSpaceTime =  P_GOD->getSpacetime();
            static const double zf_r = UTIL::getDistance(
                                              0.0, 0.0, 0.0,
                                              (double)(pSpaceTime->_x_bound_right),
                                              (double)(pSpaceTime->_y_bound_top),
                                              (double)(pSpaceTime->_z_bound_far)
                                             ) * 1.2;

            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pAimInfo->_spent_frames_to_t2 = getActiveFrame()+AIM_TIME_OUT;
            } else {
                pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pAimInfo->_spent_frames_to_t2 = getActiveFrame()+AIM_TIME_OUT;
            }

            if (pAimInfo->_spent_frames_to_t1 == 0) {
                pAimInfo->t1_x = pAimInfo->t2_x;
                pAimInfo->t1_y = pAimInfo->t2_y;
                pAimInfo->t1_z = pAimInfo->t2_z;
                pAimInfo->_spent_frames_to_t1 = getActiveFrame()+AIM_TIME_OUT;
            }

        }
        pAimInfo->pLeaderChip_ = nullptr;
    }

    pOrg_ = nullptr;
    pLockon_ = nullptr;
    pAimInfo_ = nullptr;

    WateringLaserChip::onInactive();
}

void MyBunshinWateringLaserChip001::chengeTex(int prm_tex_no) {
    if (MyBunshinWateringLaserChip001::pModel_) {
        MyBunshinWateringLaserChip001::tex_no_ = prm_tex_no;
        MyBunshinWateringLaserChip001::pModel_->setDefaultTextureMaterialNo(prm_tex_no);
    }
}

MyBunshinWateringLaserChip001::~MyBunshinWateringLaserChip001() {
    GGAF_DELETE(pAxsMver_);
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

