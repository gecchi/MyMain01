#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/LinkedListRing.hpp"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/dx/actor/supporter/VecDriver.h"
#include "jp/ggaf/dx/actor/supporter/GeoDriver.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/lib/util/CollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafLib;
using namespace VioletVreath;

const velo MyBunshinWateringLaserChip001::MAX_VELO_RENGE = PX_C(350); //この値を大きくすると、最高速度が早くなる。
const double MyBunshinWateringLaserChip001::INV_MAX_VELO_RENGE = 1.0 / MAX_VELO_RENGE;
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 15; //この値を大きくすると、カーブが緩くなる
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO_RENGE*0.8; //レーザー発射時の初期速度
const double MyBunshinWateringLaserChip001::RR_MAX_ACCE = 1.0 / R_MAX_ACCE; //計算簡素化用
const float MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO_RENGE/R_MAX_ACCE;
const velo MyBunshinWateringLaserChip001::MIN_VELO_ = MyBunshinWateringLaserChip001::INITIAL_VELO/10; // ÷10 は、最低移動する各軸のINITIAL_VELOの割合
GgafDx::Model* MyBunshinWateringLaserChip001::pModel_ = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;


MyBunshinWateringLaserChip001::MyBunshinWateringLaserChip001(const char* prm_name) :
        VvMyActor<WateringLaserChip>(prm_name, "MyLaserChip001", StatusReset(MyBunshinWateringLaserChip001)) {
    _class_name = "MyBunshinWateringLaserChip001";
    default_stamina_ = getStatus()->get(STAT_Stamina);
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    is_lockon_ = false;
    GgafDx::Model* pModel = getModel();
    if (!MyBunshinWateringLaserChip001::pModel_) {
        if (pModel->_num_materials != MAX_LASER_LEVEL) {
            throwCriticalException("MyBunshinWateringLaserChip001モデルは、テクスチャ（マテリアル）が"<<MAX_LASER_LEVEL<<"つ必要です。");
        }
        MyBunshinWateringLaserChip001::pModel_ = pModel;
    }
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    pAimInfo_ = nullptr;
    inv_cnt_ = 0;
}

void MyBunshinWateringLaserChip001::initialize() {
    getVecDriver()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(PX_C(80));
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);

}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockonCursor_ = pOrg_->pLockonCtrler_->pMainLockonEffect_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    WateringLaserChip::onActive();
    pAimInfo_ = nullptr;
    inv_cnt_ = 0;
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    GgafDx::GeoDriver* pGeoDriver = getGeoDriver();
    pGeoDriver->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
    pGeoDriver->forceVxyzMvAcceRange(-MAX_ACCE_RENGE, MAX_ACCE_RENGE);
}

void MyBunshinWateringLaserChip001::processBehavior() {
    frame active_frames = getActiveFrame();
    double power = active_frames <= 300 ? UTIL::SHOT_POWER[active_frames] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;

    GgafDx::GeoDriver* const pGeoDriver = getGeoDriver();
    frame active_frame = getActiveFrame();
    MyBunshin::AimInfo* pAimInfo = pAimInfo_;

    if (active_frame >= 60*20) {
        sayonara(); //保険のタイムアウト20秒
    } else if (pAimInfo == nullptr || active_frame < 7) {
        //なにもしない
    } else {
        GgafDx::GeometricActor* pAimTarget = pAimInfo->pTarget;
        if (pAimTarget) {
            frame aim_time_out_t1 = pAimInfo->aim_time_out_t1;
            //先端チップ時（消える可能性のあるLeaderChipにあらず！）、T1が相変わらずロックオンターゲットならば更新
            if (getInfrontChip() == nullptr && pAimTarget == pLockonCursor_->pTarget_ && pAimInfo->spent_frames_to_t1 < aim_time_out_t1) {
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
                        int vx1 = pGeoDriver->_velo_vx_mv;
                        int vy1 = pGeoDriver->_velo_vy_mv;
                        int vz1 = pGeoDriver->_velo_vz_mv;

                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );

                        int vx2 = pGeoDriver->_velo_vx_mv;
                        int vy2 = pGeoDriver->_velo_vy_mv;
                        int vz2 = pGeoDriver->_velo_vz_mv;

                        int sgn_vx = SGN(vx1 - vx2);
                        int sgn_vy = SGN(vy1 - vy2);
                        int sgn_vz = SGN(vz1 - vz2);

                        if (sgn_vy0_ != sgn_vy) {
                            inv_cnt_++;
                            sgn_vy0_ = sgn_vy;
                        } else if (sgn_vz0_ != sgn_vz) {
                            inv_cnt_++;
                            sgn_vz0_ = sgn_vz;
                        } else if (sgn_vx0_ != sgn_vx) {
                            inv_cnt_++;
                            sgn_vx0_ = sgn_vx;
                        }
                        if (inv_cnt_ > 10) { //10回も速度の正負が入れ替わったら終了
                            pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                        } else {
                            static const coord renge = MyBunshinWateringLaserChip001::INITIAL_VELO / 4;
                            static const ucoord renge2 = renge*2;
                            if ( (ucoord)(_x - pAimInfo->t1_x + renge) <= renge2) {
                                if ( (ucoord)(_y - pAimInfo->t1_y + renge) <= renge2) {
                                    if ( (ucoord)(_z - pAimInfo->t1_z + renge) <= renge2) {
                                        pAimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                                    }
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
                        pB = pB->getBehindChip();
                        if (pB) {
                            pB = pB->getBehindChip();
                        }
                    }
                    if (pB) {
                        pAimInfo->setT2(zf_r, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                    } else {
                        pAimInfo->setT2(zf_r, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                    }
                    coord t2_d = UTIL::getApproxDistance(_x, _y, _z,
                                                         pAimInfo->t2_x,
                                                         pAimInfo->t2_y,
                                                         pAimInfo->t2_z);
                    pAimInfo->spent_frames_to_t2 = active_frame + (frame)(t2_d*MyBunshinWateringLaserChip001::INV_MAX_VELO_RENGE); //t2到達時間概算
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
                        aimChip(_x + pGeoDriver->_velo_vx_mv*4+1,
                                _y + pGeoDriver->_velo_vy_mv*4+1,
                                _z + pGeoDriver->_velo_vz_mv*4+1 );
                    }
                }
            } else {
//                MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
//                if (pF) {
//                    pF = (MyBunshinWateringLaserChip001*)pF->getInfrontChip();
//                    if (pF) {
//                        pF = (MyBunshinWateringLaserChip001*)pF->getInfrontChip();
//                        if (pF) {
//                            pF = (MyBunshinWateringLaserChip001*)pF->getInfrontChip();
//                        }
//                    }
//                }
//                if (pF) {
//                    aimChip(pF->_x,
//                            pF->_y,
//                            pF->_z );
//                } else {
//                }
                //●Leader以外
                if (pAimInfo->spent_frames_to_t1 == 0) {
                    //●Leader以外が t1 が定まるまでの動き
                    if (pAimLeaderChip) {
                        aimChip(pAimLeaderChip->_x,
                                pAimLeaderChip->_y,
                                pAimLeaderChip->_z );
                    } else {
                        aimChip(pAimInfo->t1_x,
                                pAimInfo->t1_y,
                                pAimInfo->t1_z );
                    }
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
                            aimChip(_x + pGeoDriver->_velo_vx_mv*4+1,
                                    _y + pGeoDriver->_velo_vy_mv*4+1,
                                    _z + pGeoDriver->_velo_vz_mv*4+1 );
                        }
                    } else if (active_frame <= pAimInfo->spent_frames_to_t2) {
                        //●その後 Leader以外が t2 が定まって、t2に向かうまでの動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(pAimInfo->t2_x,
                                    pAimInfo->t2_y,
                                    pAimInfo->t2_z );
                        }
                    } else if (active_frame > pAimInfo->spent_frames_to_t2) {
                        //●その後 Leader以外が t2 を通過した後の動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pGeoDriver->_velo_vx_mv*4+1,
                                    _y + pGeoDriver->_velo_vy_mv*4+1,
                                    _z + pGeoDriver->_velo_vz_mv*4+1 );
                        }
                    } else {
                        _TRACE_("【警告】ありえない");
                    }
                }
            }

        } //if (pAimTarget)

    }
    pGeoDriver->behave();
    WateringLaserChip::processBehavior();
    tmp_x_ = _x;
    tmp_y_ = _y;
    tmp_z_ = _z;
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //分身はFKなので、絶対座標の確定が processSettlementBehavior() 以降となるため、ここで初期設定が必要
    GgafDx::GeoDriver* const pGeoDriver = getGeoDriver();
    if (hasJustChangedToActive()) {
        //チップの初期設定
        //ロックオン情報の引き継ぎ
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        if (pF == nullptr) {
            //先端チップ
            GgafDx::GeometricActor* pLockonTarget = pLockonCursor_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //先端でロックオン中
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = pLockonTarget;
                pAimInfo_->t1_x = pAimInfo_->pTarget->_x;
                pAimInfo_->t1_y = pAimInfo_->pTarget->_y;
                pAimInfo_->t1_z = pAimInfo_->pTarget->_z;
                // aim_time_out_t1 を概算で求めておく
                coord t1_d = UTIL::getApproxDistance(this, pLockonTarget);
                pAimInfo_->aim_time_out_t1 = (t1_d / MyBunshinWateringLaserChip001::INITIAL_VELO)*1.2;
            } else {
                //先端でロックオンしていない
                pAimInfo_ = pOrg_->getAimInfo();
                pAimInfo_->pLeaderChip = this;
                pAimInfo_->pTarget = nullptr;
            }
            pGeoDriver->forceVxyzMvVeloRange(-MAX_VELO_RENGE, MAX_VELO_RENGE);
        } else {
            //先端以外は前のを受け継ぐ
            pAimInfo_ = pF->pAimInfo_; //受け継ぐ
            velo v = MAX_VELO_RENGE - PX_C(1); //レーザーが弛まないように PX_C(1) 遅くした
            pGeoDriver->forceVxyzMvVeloRange(-v, v);
#ifdef MY_DEBUG
if (pAimInfo_ == nullptr) {
throwCriticalException("pAimInfo_ が引き継がれていません！"<<this<<
                           " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }
        //活動開始初回フレーム、チップの速度と向きの初期設定
        setFaceAngAs(pOrg_);
        setPositionAt(pOrg_);
        pGeoDriver->setVxyzMvVeloTwd(_rz, _ry, INITIAL_VELO); //初速はここで
        pGeoDriver->setZeroVxyzMvAcce();
    }

    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。
    if (getActiveFrame() > 3) {//FKオブジェクトからのレーザー発射も考慮すると、_tmpXYZ が埋まるのは3フレーム以降。
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
        if (pF && pF->isActive()) {
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB && pB->isActive()) {
                //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
                //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
                //_x,_y,_z にはまだ変な値が入っている。
                //中間座標に再設定
                //座標の重みは、（ひとつ前, 自身, 一つ先）＝ (0.2, 0.5, 0.3)
                if (pAimInfo_->pTarget) {
                    _x = tmp_x_ + (coord)((pB->tmp_x_-tmp_x_)*0.1 + (pF->tmp_x_-tmp_x_)*0.4);
                    _y = tmp_y_ + (coord)((pB->tmp_y_-tmp_y_)*0.1 + (pF->tmp_y_-tmp_y_)*0.4);
                    _z = tmp_z_ + (coord)((pB->tmp_z_-tmp_z_)*0.1 + (pF->tmp_z_-tmp_z_)*0.4);
                } else {
                    _x = tmp_x_ + (coord)((pB->tmp_x_-tmp_x_)*0.1 + (pF->tmp_x_-tmp_x_)*0.1);
                    _y = tmp_y_ + (coord)((pB->tmp_y_-tmp_y_)*0.1 + (pF->tmp_y_-tmp_y_)*0.1);
                    _z = tmp_z_ + (coord)((pB->tmp_z_-tmp_z_)*0.1 + (pF->tmp_z_-tmp_z_)*0.1);
                }
            } else {
                if (pAimInfo_->pTarget) {
                    //補正後の一つ前の座標と、自身の座標を直線で結んで、仮想の自分の後ろの点を作成。
                    //補正前の一つ前の座標、自身の座標、仮想の自分の後ろの点で平均を取る
                    coord v_b_x = _x - (pF->_x - _x);
                    coord v_b_y = _y - (pF->_y - _y);
                    coord v_b_z = _z - (pF->_z - _z);
                    _x = tmp_x_ + (coord)((v_b_x-tmp_x_)*0.2 + (pF->tmp_x_-tmp_x_)*0.3);
                    _y = tmp_y_ + (coord)((v_b_y-tmp_y_)*0.2 + (pF->tmp_y_-tmp_y_)*0.3);
                    _z = tmp_z_ + (coord)((v_b_z-tmp_z_)*0.2 + (pF->tmp_z_-tmp_z_)*0.3);
                }

            }

//            //レーザーチップの向きを一つ前のチップに設定
//            setFaceAngTwd(pF);
        } else {
//            //レーザーチップの向きを移動方向に設定（先端チップ）
//            UTIL::convVectorToRzRy(pGeoDriver->_velo_vx_mv,
//                                   pGeoDriver->_velo_vy_mv,
//                                   pGeoDriver->_velo_vz_mv,
//                                   _rz, _ry );
        }

        UTIL::convVectorToRzRy(pGeoDriver->_velo_vx_mv,
                               pGeoDriver->_velo_vy_mv,
                               pGeoDriver->_velo_vz_mv,
                               _rz, _ry );
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
    //    |               |仮的| > |仮自| /    ＼  vVP 仮自→仮的            |      仮的
    //    |                 となるような /       ＼                          |       ↑
    //    |                 vVTを設定   /         ┐                         |      仮自
    //    |               (|仮自|*1.2) /        ／vVM  仮自                  |       ↑
    //    |                           /       ／ =(vMx*5,vMy*5,vMz*5)        |       ｜
    //    |                          /      ／                               |       ｜
    //    |                         /     ／                                 |       ｜
    //    |                        /    ／ |仮自| = lVM * 5                  |       ｜
    //    |                      的 vT(vTx,vTy,vTz)                          |       的
    //    |             ┌       ^  ／                                       |       ↑
    //    |               ＼    / ┐vM 現在の移動方向ベクトル                |       ｜
    //    | vVP 仮自→仮的  ＼ /／ (vMx,vMy,vMz)                             |       ｜
    //    |                   自                                             |       自
    //    |                     (_x,_y,_z)                                   |
    // ---+------------------------------------------                     ---+---------------------------
    //    |                                                                  |
    //
    // vVP が動きたい方向。vVPを求める！
#ifdef MY_DEBUG
    if (tX == INT_MAX) {
        throwCriticalException("おかしい");
    }
#endif


    static const coord rv = 10.0;
    GgafDx::GeoDriver* pGeoDriver = getGeoDriver();
    //自→仮、自方向ベクトル(vM)
    coord vMx = pGeoDriver->_velo_vx_mv;
    coord vMy = pGeoDriver->_velo_vy_mv;
    coord vMz = pGeoDriver->_velo_vz_mv;
    //|vM|
//    double lvM = sqrt(vMx*vMx + vMy*vMy + vMz*vMz);
    coord lvM = UTIL::getApproxDistanceFromOrigin(vMx, vMy, vMz);
    //|vM|があまりに小さい場合＝速度が遅すぎる場合を考慮
    if  (lvM < MIN_VELO_) { //縮こまらないように
        if (ZEROd_EQ(lvM)) {
            //速度が殆ど０でもうどっち向いてるかわからんので、X軸方向に飛ばす
            pGeoDriver->setVxyzMvVelo(MIN_VELO_, 0, 0);
        } else {
            //速度 MIN_VELO_ を保証する
            double r = (1.0*MIN_VELO_/lvM);
            pGeoDriver->setVxyzMvVelo(vMx*r, vMy*r, vMz*r);
        }
        vMx = pGeoDriver->_velo_vx_mv;
        vMy = pGeoDriver->_velo_vy_mv;
        vMz = pGeoDriver->_velo_vz_mv;
        lvM = MIN_VELO_;
    }
    coord vVMx = vMx * rv;
    coord vVMy = vMy * rv;
    coord vVMz = vMz * rv;
    coord lvVM = lvM * rv;


    //自→的、方向ベクトル (vT)
    coord vTx = tX - _x;
    coord vTy = tY - _y;
    coord vTz = tZ - _z;
    //|vT|
//    double lvT = sqrt(vTx*vTx + vTy*vTy + vTz*vTz);
    coord lvT = UTIL::getApproxDistanceFromOrigin(vTx, vTy, vTz);
    //|仮的| を lvVM の長さに合わせて作成
    double rMT = (lvVM * 1.2 / lvT) ;
    //1.2は右上図のように一直線に並んだ際も、進行方向を維持するために、
    //|仮自| < |仮的| という関係を維持するためにかけた適当な割合
    coord vVTx = vTx * rMT;
    coord vVTy = vTy * rMT;
    coord vVTz = vTz * rMT;
    coord lvVT = lvT * rMT;
//    double cos_th = ((vMx*vTx + vMy*vTy + vMz*vTz) / (lvT * lvM)); //なす角
//    if (cos_th < 0.5) {
//        cos_th = 0.5;
//    }
    //vVP 仮自→仮的 の加速度設定
    //→vVP=( vVTx-vVMx, vVTy-vVMy, vVTz-vVMz )
    const acce accX = (vVTx-vVMx) * RR_MAX_ACCE; // * cos_th;
    const acce accY = (vVTy-vVMy) * RR_MAX_ACCE; // * cos_th;
    const acce accZ = (vVTz-vVMz) * RR_MAX_ACCE; // * cos_th;
    double top_acce_mv = pGeoDriver->_top_acce_vx_mv*1.05; //ちょっとずつなら拡張しちょいよみたいな
    if (MAX_VELO_RENGE < top_acce_mv && top_acce_mv < MAX_VELO_RENGE) {
        pGeoDriver->forceVxyzMvAcceRange(-top_acce_mv, top_acce_mv);
    }
    pGeoDriver->setVxyzMvAcce(accX, accY, accZ);
}


void MyBunshinWateringLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    GgafDx::FigureActor* pE = UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
    GgafDx::CollisionPart* pColliPart = getCollisionChecker()->getLastHitCollisionPart();
    pE->setPosition(pE->_x + pColliPart->_cx, pE->_y + pColliPart->_cy, pE->_z + pColliPart->_cz); //爆発エフェクト位置を補正

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
    pLockonCursor_ = nullptr;
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

