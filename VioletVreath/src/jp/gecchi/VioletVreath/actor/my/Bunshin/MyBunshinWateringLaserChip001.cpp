#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxTrucker.h"
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

const velo MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(300); //この値を大きくすると、最高速度が早くなる。
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 15; //この値を大きくすると、カーブが緩くなる
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO_RENGE*0.7; //レーザー発射時の初期速度
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //計算簡素化用
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;

GgafDxCore::GgafDxModel* MyBunshinWateringLaserChip001::pModel_  = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;


MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        WateringLaserChip(prm_name, "MyLaserChip001", STATUS(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockon_ = nullptr;
    is_lockon_ = false;
    GgafDxModel* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwGgafCriticalException("MyBunshinWateringLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
    tmp_acc_vx_ = tmp_acc_vy_ = tmp_acc_vz_ = 0;
    pAimInfo_ = nullptr;
}

void MyBunshinWateringLaserChip001::initialize() {
    getKuroko()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(PX_C(80));
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);
    GgafDxTrucker* const pTrucker = getTrucker();
    pTrucker->forceVxMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
    pTrucker->forceVyMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
    pTrucker->forceVzMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
    pTrucker->forceVxMvAcceRange(-MAX_ACCE_RENGE, MAX_ACCE_RENGE);
    pTrucker->forceVyMvAcceRange(-MAX_ACCE_RENGE*1.5, MAX_ACCE_RENGE*1.5);
    pTrucker->forceVzMvAcceRange(-MAX_ACCE_RENGE*1.5, MAX_ACCE_RENGE*1.5);
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
    frame active_frames = getActiveFrame();
    double power = active_frames <= 300 ? UTIL::SHOT_POWER[active_frames] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    GgafDxTrucker* const pTrucker = getTrucker();
    frame active_frame = getActiveFrame();
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;

    if (active_frame >= 60*20) {
        sayonara(); //保険のタイムアウト20秒
    } else if (active_frame < 7) {
        //なにもしない
    } else if (pAimInfo && pAimInfo->pTarget == nullptr) {
        //なにもしない
    } else {
        GgafDxGeometricActor* pAimTarget = pAimInfo->pTarget;
        frame aim_time_out_t1 = pAimInfo->aim_time_out_t1;
        if (pAimTarget) {
            //先端チップ時（消える可能性のあるLeaderChipにあらず！）、T1が相変わらずロックオンターゲットならば更新
            if (getInfrontChip() == nullptr && pAimTarget == pLockon_->pTarget_ && pAimInfo_->spent_frames_to_t1 < aim_time_out_t1) {
                pAimInfo->t1_x = pAimTarget->_x; //t1更新
                pAimInfo->t1_y = pAimTarget->_y;
                pAimInfo->t1_z = pAimTarget->_z;
            }

            MyBunshinWateringLaserChip001* pAimLeaderChip = pAimInfo->pLeaderChip;
            if (this == pAimLeaderChip) {
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //●Leader が t1 へ Aim
                    if (pAimTarget->isActiveInTheTree() && active_frame < aim_time_out_t1)  {
                        //pAimTarget が存命
                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );
                        static const coord renge = MyBunshinWateringLaserChip001::INITIAL_VELO * 0.4;
                        static const ucoord renge2 = renge*2;
                        if ( (ucoord)(_x - pAimInfo->t1_x + renge) <= renge2) {
                            if ( (ucoord)(_y - pAimInfo->t1_y + renge) <= renge2) {
                                if ( (ucoord)(_z - pAimInfo->t1_z + renge) <= renge2) {
                                    pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                                }
                            }
                        }

                    } else {
                        //初めは pAimTarget があったのに、途中で消えた。
                        pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                    }
                } else if (pAimInfo->spent_frames_to_t2 == 0) {
                    //●Leader が t1 へ Aim し終わったあと
                    //t2を決める
                    static const Spacetime* pSpaceTime =  pGOD->getSpacetime();
                    static const double zf_r = UTIL::getDistance(
                                                      0.0, 0.0, 0.0,
                                                      (double)(pSpaceTime->_x_bound_right),
                                                      (double)(pSpaceTime->_y_bound_top),
                                                      (double)(pSpaceTime->_z_bound_far)
                                                     ) * 1.2;
                    LaserChip* pB = getBehindChip();
                    if (pB) {
                        pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                    } else {
                        pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                    }
                    coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                   pAimInfo->t2_x,
                                                   pAimInfo->t2_y,
                                                   pAimInfo->t2_z);
                    pAimInfo->spent_frames_to_t2 = active_frame + (t2_d/MyBunshinWateringLaserChip001::MAX_VELO_RENGE); //t2到達時間概算
                    aimChip(pAimInfo->t2_x,
                            pAimInfo->t2_y,
                            pAimInfo->t2_z );
                } else {
                    //●Leader が t2 を設定したあと。
                    if (active_frame < pAimInfo->spent_frames_to_t2)  {
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else {
                        aimChip(_x + pTrucker->_velo_vx_mv*4+1,
                                _y + pTrucker->_velo_vy_mv*4+1,
                                _z + pTrucker->_velo_vz_mv*4+1 );
                    }
                }
            } else {
                //●Leader以外
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //●Leader以外が t1 が定まるまでの動き
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame <= pAimInfo->spent_frames_to_t1) {
                    //●Leader以外が t1 が定まってから t1 到達までの動き
                    aimChip(pAimInfo->t1_x,
                            pAimInfo->t1_y,
                            pAimInfo->t1_z );
                } else if (active_frame > pAimInfo->spent_frames_to_t1) {
                    //●Leader以外が t1 を通過
                    if (pAimInfo->spent_frames_to_t2 == 0) {
                        //●その後 Leader以外が t2 が定まるまでの動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pTrucker->_velo_vx_mv*4+1,
                                    _y + pTrucker->_velo_vy_mv*4+1,
                                    _z + pTrucker->_velo_vz_mv*4+1 );
                        }
                    } else if (active_frame <= pAimInfo->spent_frames_to_t2) {
                        //●その後 Leader以外が t2 が定まって、t2に向かうまでの動き
                        aimChip(pAimInfo->t2_x,
                                pAimInfo->t2_y,
                                pAimInfo->t2_z );
                    } else if (active_frame > pAimInfo->spent_frames_to_t2) {
                        //●その後 Leader以外が t2 を通過した後の動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pTrucker->_velo_vx_mv*4+1,
                                    _y + pTrucker->_velo_vy_mv*4+1,
                                    _z + pTrucker->_velo_vz_mv*4+1 );
                        }
                    }
                }
            }

        }

    }
    pTrucker->behave();
    WateringLaserChip::processBehavior();
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
    tmp_acc_vx_ =  pTrucker->_acce_vx_mv;
    tmp_acc_vy_ =  pTrucker->_acce_vy_mv;
    tmp_acc_vz_ =  pTrucker->_acce_vz_mv;
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //分身はFKなので、絶対座標の確定が processSettlementBehavior() 以降となるため、ここで初期設定が必要
    GgafDxTrucker* const pTrucker = getTrucker();
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
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = pLockonTarget;
                pAimInfo_->t1_x = pAimInfo_->pTarget->_x;
                pAimInfo_->t1_y = pAimInfo_->pTarget->_y;
                pAimInfo_->t1_z = pAimInfo_->pTarget->_z;
                // aim_time_out_t1 を概算で求めておく
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                pAimInfo_->aim_time_out_t1 = (t1_d / MyBunshinWateringLaserChip001::INITIAL_VELO)*1.2;
            } else {
                //先端でロックオンしていない
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = nullptr;
            }
            pTrucker->forceVxMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
            pTrucker->forceVyMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
            pTrucker->forceVzMvVeloRange(-MAX_VELO_RENGE*1.5, MAX_VELO_RENGE*1.5);
        } else {
            //先端以外は前のを受け継ぐ
            pAimInfo_ = pF->pAimInfo_; //受け継ぐ
            velo v = pF->getTrucker()->_top_velo_vx_mv - PX_C(0.5); //レーザーが弛まないように PX_C(0.5) 遅くした
            pTrucker->forceVxMvVeloRange(-v, v);
            pTrucker->forceVyMvVeloRange(-v*1.5, v*1.5);
            pTrucker->forceVzMvVeloRange(-v*1.5, v*1.5);
#ifdef MY_DEBUG
if (pAimInfo_ == nullptr) {
throwGgafCriticalException("pAimInfo_ が引き継がれていません！"<<this<<
                           " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }
        //活動開始初回フレーム、チップの速度と向きの初期設定
        setFaceAngAs(pOrg_);
        setPositionAt(pOrg_);
        pTrucker->setVxyzMvVeloTwd(_rz, _ry, INITIAL_VELO); //初速はここで
        pTrucker->setZeroVxyzMvAcce();
    }

    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。
//    if (getActiveFrame() > 4) { //FKオブジェクトからのレーザー発射も考慮すると、_tmpXYZ が埋まるのは3フレーム以降。
//        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
//        MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
//        if (pF && pB && pF->isActive() && pB->isActive()) {
//            //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
//            //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
//            //_x,_y,_z にはまだ変な値が入っている。
//            //中間座標に再設定
//            _x = (pF->tmp_x_ + pB->tmp_x_ + tmp_x_)/3;
//            _y = (pF->tmp_y_ + pB->tmp_y_ + tmp_y_)/3;
//            _z = (pF->tmp_z_ + pB->tmp_z_ + tmp_z_)/3;
//            pTrucker->setVxyzMvAcce( (pF->tmp_acc_vx_ + pB->tmp_acc_vx_ + tmp_acc_vx_)/3,
//                                     (pF->tmp_acc_vy_ + pB->tmp_acc_vy_ + tmp_acc_vy_)/3,
//                                     (pF->tmp_acc_vz_ + pB->tmp_acc_vz_ + tmp_acc_vz_)/3 );
//        }
//    }
    if (getActiveFrame() > 3) { //FKオブジェクトからのレーザー発射も考慮すると、_tmpXYZ が埋まるのは3フレーム以降。
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        if (pF && pF->isActive()) {
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB && pB->isActive()) {
                //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
                //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
                //_x,_y,_z にはまだ変な値が入っている。
                //中間座標に再設定
                _x = (pF->tmp_x_ + pB->tmp_x_ + tmp_x_)/3;
                _y = (pF->tmp_y_ + pB->tmp_y_ + tmp_y_)/3;
                _z = (pF->tmp_z_ + pB->tmp_z_ + tmp_z_)/3;
                pTrucker->setVxyzMvAcce( (pF->tmp_acc_vx_ + pB->tmp_acc_vx_ + tmp_acc_vx_)/3,
                                         (pF->tmp_acc_vy_ + pB->tmp_acc_vy_ + tmp_acc_vy_)/3,
                                         (pF->tmp_acc_vz_ + pB->tmp_acc_vz_ + tmp_acc_vz_)/3 );
            } else {
                _x = (pF->tmp_x_ + tmp_x_)/2;
                _y = (pF->tmp_y_ + tmp_y_)/2;
                _z = (pF->tmp_z_ + tmp_z_)/2;
                pTrucker->setVxyzMvAcce( (pF->tmp_acc_vx_ + tmp_acc_vx_)/2,
                                         (pF->tmp_acc_vy_ + tmp_acc_vy_)/2,
                                         (pF->tmp_acc_vz_ + tmp_acc_vz_)/2 );
            }
        }
    }
    WateringLaserChip::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
        if (pAimInfo_->pLeaderChip == this) {
            pAimInfo_->t2_x = _x;
            pAimInfo_->t2_y = _y;
            pAimInfo_->t2_z = _z;
            pAimInfo_->spent_frames_to_t2 = getActiveFrame();
            if (pAimInfo_->spent_frames_to_t1 == 0) {
                pAimInfo_->t1_x = pAimInfo_->t2_x;
                pAimInfo_->t1_y = pAimInfo_->t2_y;
                pAimInfo_->t1_z = pAimInfo_->t2_z;
                pAimInfo_->spent_frames_to_t1 = getActiveFrame();
            }
        }
        sayonara();
    }
}


void MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ) {
    //    |                            vVT 仮的                              |
    //    |                                ^ ┌                              |
    //    |                 |仮的| > 5*vM /    ＼  vVP 仮自→仮的            |      仮的
    //    |                 となるような /       ＼                          |       ↑
    //    |                 vVTを設定   /         ┐                         |      仮自
    //    |                            /        ／vVM  仮自                  |       ↑
    //    |                           /       ／  (vVMx*5,vVMy*5,vVMz*5)     |       ｜
    //    |                          /      ／                               |       ｜
    //    |                         /     ／                                 |       ｜
    //    |                        /    ／ |仮自| = lVM * 5                  |       ｜
    //    |                      的 vT(tX,tY,tZ)                             |       的
    //    |             ┌       ^  ／                                       |       ↑
    //    |               ＼    / ┐vM 現在の移動方向ベクトル                |       ｜
    //    | vVP 仮自→仮的  ＼ /／ (vVMx,vVMy,vVMz)                          |       ｜
    //    |                   自                                             |       自
    //    |                     (_x,_y,_z)                                   |
    // ---+------------------------------------------                     ---+---------------------------
    //    |                                                                  |
    //
    // vVP が動きたい方向。vVPを求める！
#ifdef MY_DEBUG
    if (tX == INT_MAX) {
        throwGgafCriticalException("おかしい");
    }
#endif
    GgafDxTrucker* pTrucker = getTrucker();

    //自→的
    const int vTx = tX - _x;
    const int vTy = tY - _y;
    const int vTz = tZ - _z;

    //自→仮自。
    int vMx = pTrucker->_velo_vx_mv;
    int vMy = pTrucker->_velo_vy_mv;
    int vMz = pTrucker->_velo_vz_mv;

    //|仮自| = lVM * 5
    int lVM = MAX3(ABS(vMx), ABS(vMy), ABS(vMz)); //仮自ベクトル大きさ簡易版

    static const velo min_velo = MyBunshinWateringLaserChip001::INITIAL_VELO/2; // ÷2 は、最低移動する各軸のINITIAL_VELOの割合
    if  (lVM < min_velo) { //縮こまらないように
        if (lVM != 0) {
            double r = (1.0*min_velo/lVM);
            pTrucker->setVxyzMvVelo(vMx*r, vMy*r, vMz*r);
            vMx = pTrucker->_velo_vx_mv;
            vMy = pTrucker->_velo_vy_mv;
            vMz = pTrucker->_velo_vz_mv;
        } else {
            pTrucker->setVxyzMvVelo(min_velo, 0, 0);
            vMx = pTrucker->_velo_vx_mv;
            vMy = pTrucker->_velo_vy_mv;
            vMz = pTrucker->_velo_vz_mv;
        }
        lVM = min_velo;
    }

    //|的|
    const int lT = MAX3(ABS(vTx), ABS(vTy), ABS(vTz)); //的ベクトル大きさ簡易版
    //|仮自|/|的|      vT の何倍が vVT 仮的 になるのかを求める。
    const double r = (lVM*5 * 1.5) / lT;
    //* 1.5は 右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮的| > |仮自| という関係を維持するためにかけた適当な割合

    //vVP 仮自→仮的 の加速度設定
    //求めた vVP=( (vTx*r)-vMx*5), (vTy*r)-vMy*5), (vTz*r)-vMz*5) )
    const double accX = ((vTx * r) - vMx*5) * RR_MAX_ACCE;
    const double accY = ((vTy * r) - vMy*5) * RR_MAX_ACCE;
    const double accZ = ((vTz * r) - vMz*5) * RR_MAX_ACCE;

    pTrucker->setVxyzMvAcce(accX + SGN(accX)*3.0,
                            accY + SGN(accY)*3.0,
                            accZ + SGN(accZ)*3.0);
}

void MyBunshinWateringLaserChip001::onHit(const GgafActor* prm_pOtherActor) {
    GgafDxGeometricActor* pOther = (GgafDxGeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //ロックオン可能アクターならロックオン
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
        MyBunshin::AimInfo* pAimInfo = pAimInfo_;
        if (this == pAimInfo->pLeaderChip && pAimInfo->pTarget == prm_pOtherActor) {
            //先端が目標に見事命中した場合もT1終了
            pAimInfo->t1_x = _x;
            pAimInfo->t1_y = _y;
            pAimInfo->t1_z = _z;
            pAimInfo->spent_frames_to_t1 = getActiveFrame();
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;
    if (pAimInfo && pAimInfo->pLeaderChip == this) {
        if (pAimInfo->spent_frames_to_t2 == 0) {
            frame aim_time_out_t1 = pAimInfo_->aim_time_out_t1;
            static const Spacetime* pSpaceTime =  pGOD->getSpacetime();
            static const double zf_r = UTIL::getDistance(
                                              0.0, 0.0, 0.0,
                                              (double)(pSpaceTime->_x_bound_right),
                                              (double)(pSpaceTime->_y_bound_top),
                                              (double)(pSpaceTime->_z_bound_far)
                                             ) * 1.2;

            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pAimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            } else {
                pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pAimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            }

            if (pAimInfo->spent_frames_to_t1 == 0) {
                pAimInfo->t1_x = pAimInfo->t2_x;
                pAimInfo->t1_y = pAimInfo->t2_y;
                pAimInfo->t1_z = pAimInfo->t2_z;
                pAimInfo->spent_frames_to_t1 = getActiveFrame() + aim_time_out_t1;
            }

        }
        pAimInfo->pLeaderChip = nullptr;
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
    MyBunshinWateringLaserChip001::pModel_ = nullptr;
}

