#include "MyBunshinWateringLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/Bunshin/MyBunshin.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/core/util/ResourceConnection.hpp"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/NaviVehicle.h"
#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/Model.h"
#include "jp/ggaf/dx/texture/Texture.h"
#include "jp/ggaf/dx/util/CollisionArea.h"
#include "jp/ggaf/dx/util/CollisionPart.h"
#include "jp/ggaf/lib/actor/laserchip/WateringLaserChip.h"
#include "jp/ggaf/lib/util/WorldCollisionChecker.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"

using namespace GgafLib;
using namespace VioletVreath;

const velo MyBunshinWateringLaserChip001::MAX_VELO = PX_C(1024); //この値を大きくすると、最高速度が早くなる。
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 25; //MAX_VELO に対する加速度、この値を大きくすると、カーブが緩くなる。小さくすると、カーブがきつくなるがギザギザになりやすい
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO*0.6; //レーザー発射時の初期速度
const acce MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO/R_MAX_ACCE;
const velo MyBunshinWateringLaserChip001::MIN_VELO_ = MyBunshinWateringLaserChip001::INITIAL_VELO/2; // ÷2 は、最低移動する各軸のINITIAL_VELOの割合
GgafDx::Model* MyBunshinWateringLaserChip001::pModel_ = nullptr;
int MyBunshinWateringLaserChip001::tex_no_ = 0;

enum {
    PHASE_T1,
    PHASE_T2,
    PHASE_T2_AFTER ,
    PHASE_BANPEI,
};


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
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    pLeaderChip_AimInfo_ = nullptr;
    inv_cnt_ = 0;
    prev_velo_ = 0;
    prev_velo_vc_x_ = 0;
    prev_velo_vc_y_ = 0;
    prev_velo_vc_z_ = 0;
}

void MyBunshinWateringLaserChip001::initialize() {
    getLocoVehicle()->linkFaceAngByMvAng(true);
    registerHitAreaCube_AutoGenMidColli(MAX_VELO/4); //速度に応じて大きさを変化
    setHitAble(true);
    setScaleR(6.0);
    setCullingDraw(false);
}

void MyBunshinWateringLaserChip001::onCreateModel() {

}

void MyBunshinWateringLaserChip001::setOrg(MyBunshin* prm_pOrg) {
    pOrg_ = prm_pOrg;
    pLockonCursor_ = pOrg_->pLockonCtrler_->pMainLockonCursor_;
}

void MyBunshinWateringLaserChip001::onActive() {
    getStatus()->reset();
    default_stamina_ = getStatus()->get(STAT_Stamina);
    VvMyActor<WateringLaserChip>::onActive();
    pLeaderChip_AimInfo_ = nullptr;
    inv_cnt_ = 0;
    sgn_vx0_ = 0;
    sgn_vy0_ = 0;
    sgn_vz0_ = 0;
    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    pNaviVehicle->forceVeloRange(MIN_VELO_*_n_dispatch_at_once, MAX_VELO*_n_dispatch_at_once);
    pNaviVehicle->forceAcceRange(0, MAX_ACCE_RENGE*_n_dispatch_at_once);
    getPhase()->reset(PHASE_T1);
}

void MyBunshinWateringLaserChip001::processBehavior() {
    frame active_frame = getActiveFrame();
    double power = active_frame <= 300 ? UTIL::SHOT_POWER[active_frame] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;
    AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    if (getActiveFrame() >= 60*10) {
        sayonara(); //保険のタイムアウト10秒
    } else if (pLeaderChip_AimInfo == nullptr || active_frame < 4) {
        //なにもしない
    } else {
        GgafDx::GeometricActor* pAimTarget = pLeaderChip_AimInfo->pTarget;
        if (!(pAimTarget && pAimTarget->isActiveInTheTree()) ) {
            pLeaderChip_AimInfo->pTarget = nullptr;
        }

        if (pLeaderChip_AimInfo->pTarget == nullptr && pLeaderChip_AimInfo->aim_time_out_t1 == 0) {
            //なにもしない
        } else {
            processBehavior_Aiming();
        }
    }

//    //ギザギザのためテスト
//    prev_velo_ = pNaviVehicle->_velo;
//    prev_velo_vc_x_ = pNaviVehicle->_velo_vc_x;
//    prev_velo_vc_y_ = pNaviVehicle->_velo_vc_y;
//    prev_velo_vc_z_ = pNaviVehicle->_velo_vc_z;
//    //ギザギザのためテストここまで
    //ギザギザのためテスト
//    MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
//    if (pF && pF->isActive()) {
//        pNaviVehicle->_velo = pF->prev_velo_;
//        pNaviVehicle->_velo_vc_x = pF->prev_velo_vc_x_;
//        pNaviVehicle->_velo_vc_y = pF->prev_velo_vc_y_;
//        pNaviVehicle->_velo_vc_z = pF->prev_velo_vc_z_;
//    }
    //ギザギザのためテストここまで
    pNaviVehicle->behave();

    VvMyActor<WateringLaserChip>::processBehavior();
}

void MyBunshinWateringLaserChip001::processBehavior_Aiming() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;
    frame active_frame = getActiveFrame();

    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
         case PHASE_T1: {
            if (getInfrontChip() == nullptr) {
                //先端チップ
                if (this != pLeaderChip_AimInfo_->pLeaderChip) {
                    //先端チップなのにリーダじゃない・・・だと
                    //pLeaderChip_AimInfo_ の AimInfo コピー新規で作成。AimInfo参照チェーンを切断
                    pLeaderChip_AimInfo_ = getNewAimInfoCopy(pLeaderChip_AimInfo_);
                    pLeaderChip_AimInfo_->pLeaderChip = this; //リーダー俺
                }
            }
            AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
            if (this == pLeaderChip_AimInfo->pLeaderChip) {
                //リーダーチップの場合
                GgafDx::GeometricActor* pAimTarget = pLeaderChip_AimInfo->pTarget;
                if (pAimTarget) {
                    //ターゲット存命ならばT1座標更新
                    pLeaderChip_AimInfo->updateT1(pAimTarget->_x, pAimTarget->_y, pAimTarget->_z);  //t1更新
                    //T1座標のちょっと未来の座標を求め t1_ahead に設定
                    coord aim_t1_x = pLeaderChip_AimInfo->t1_x;
                    coord aim_t1_y = pLeaderChip_AimInfo->t1_y;
                    coord aim_t1_z = pLeaderChip_AimInfo->t1_z;
                    coord ahead_vx = aim_t1_x - pLeaderChip_AimInfo->t1_x_prev;
                    coord ahead_vy = aim_t1_y - pLeaderChip_AimInfo->t1_y_prev;
                    coord ahead_vz = aim_t1_z - pLeaderChip_AimInfo->t1_z_prev;
                    if (ahead_vx == 0 &&  ahead_vy == 0 && ahead_vz == 0) {
                        pLeaderChip_AimInfo->setT1Ahead(aim_t1_x, aim_t1_y, aim_t1_z);
                    } else {
                        double out_ahead_nvx, out_ahead_nvy, out_ahead_nvz;
                        UTIL::getNormalizedVector(ahead_vx, ahead_vy, ahead_vz,
                                                  out_ahead_nvx, out_ahead_nvy, out_ahead_nvz);
                        //目標座標を、進行方向にヒットBOX分ずらす
                        static coord d_f = _hitarea_edge_length/2;
                        pLeaderChip_AimInfo->setT1Ahead(aim_t1_x + out_ahead_nvx*d_f,
                                                        aim_t1_y + out_ahead_nvy*d_f,
                                                        aim_t1_z + out_ahead_nvz*d_f);
                    }
                } else {
                    //ターゲット消失した場合
                    pLeaderChip_AimInfo->pTarget = nullptr;
                }
            } else {
                //リーダーチップ以外、先端チップ以外
                //T1Ahead が必ずあるはず
            }

            if (pLeaderChip_AimInfo->aim_time_out_t1 <= active_frame) {
                //T1 タイムアウトで終了
                //_TRACE_("aimChip("<<pLeaderChip_AimInfo->t1_ahead_x<<","<<pLeaderChip_AimInfo->t1_ahead_y<<","<<pLeaderChip_AimInfo->t1_ahead_z<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" T1 タイムアウト で done!!");
                pPhase->changeImmediately(PHASE_T2);
                goto L_PHASE_T2;
            }
            //T1Ahead（T1ちょっと未来）にAim
            bool is_done = aimChip(pLeaderChip_AimInfo->t1_ahead_x,
                                   pLeaderChip_AimInfo->t1_ahead_y,
                                   pLeaderChip_AimInfo->t1_ahead_z,
                                   true);

            if (is_done) {
                //T1Ahead に衝突、あるいは、通り過ぎで終了
                if (pLeaderChip_AimInfo->aim_time_out_t1 > active_frame) {
                    //早めれるなら早めようか・・・
                    pLeaderChip_AimInfo->aim_time_out_t1 = active_frame;
                }
                pPhase->changeImmediately(PHASE_T2);
                goto L_PHASE_T2;
            }

            break;
         }

L_PHASE_T2:
         case PHASE_T2: {
             AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
             if (pPhase->hasJustChanged() ) {
                 if (pLeaderChip_AimInfo->aim_time_out_t2 == 0) {
                     //T2 未設定だった場合、T2 の座標設定と概算を求める
                     LaserChip* pB = getBehindChip();
                     if (pB) { pB = pB->getBehindChip(); if (pB) {  pB = pB->getBehindChip(); }  }
                     if (pB) {
                         GgafDx::NaviVehicle* pB_pNaviVehicle = pB->getNaviVehicle();
                         pLeaderChip_AimInfo->setT2BySphere(
                                                ZF_R,
                                                _x, _y, _z,
                                                _x + pB_pNaviVehicle->_acce_vc_x,
                                                _y + pB_pNaviVehicle->_acce_vc_y,
                                                _z + pB_pNaviVehicle->_acce_vc_z
                                              );
                     } else {
                         pLeaderChip_AimInfo->setT2BySphere(
                                                ZF_R,
                                                _x, _y, _z,
                                                _x + pNaviVehicle->_velo_vc_x,
                                                _y + pNaviVehicle->_velo_vc_y,
                                                _z + pNaviVehicle->_velo_vc_z
                                              );
                     }
                     coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                    pLeaderChip_AimInfo->t2_x,
                                                    pLeaderChip_AimInfo->t2_y,
                                                    pLeaderChip_AimInfo->t2_z);
                     pLeaderChip_AimInfo->aim_time_out_t2 =
                             active_frame + (frame)(t2_d/(MyBunshinWateringLaserChip001::MAX_VELO*_n_dispatch_at_once)); //T2到達時間概算
                 }
             }
             if (pLeaderChip_AimInfo->aim_time_out_t2 <= active_frame) {
                 //T2 終了時の処理
                 pPhase->changeImmediately(PHASE_T2_AFTER);
                 goto L_PHASE_T2_AFTER;
             }
             aimChip(pLeaderChip_AimInfo->t2_x,
                     pLeaderChip_AimInfo->t2_y,
                     pLeaderChip_AimInfo->t2_z );
             break;
         }

L_PHASE_T2_AFTER:
         case PHASE_T2_AFTER: {
             //isOutOfSpacetime() が成立するか、保険のタイムアウト10秒 まで
             aimChip(_x + pNaviVehicle->_velo_vc_x*10+1,
                     _y + pNaviVehicle->_velo_vc_y*10+1,
                     _z + pNaviVehicle->_velo_vc_z*10+1 );
             break;
         }
         default: {
             break;
         }
     }
}

void MyBunshinWateringLaserChip001::processSettlementBehavior() {
    //分身はFKなので、絶対座標の確定が processSettlementBehavior() 以降となるため、ここで初期設定が必要
    GgafDx::NaviVehicle* const pNaviVehicle = getNaviVehicle();

    if (hasJustChangedToActive()) {
        //ロックオン情報の引き継ぎ
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        //チップの初期設定
        //活動開始初回フレーム、チップの速度と向きの初期設定
        //_dispatch_index= 2, 1, 0 なので、[0]根本の次の次、[1]根本の次、[2]根本 の順で処理されることになる。
        //n=0, 1, 2  … レーザーチップの [0]根本, [1]根本の次、[2]根本の次の次
        int n = _n_dispatch_at_once-1 - _dispatch_index;
        if (n == 0) {
            setFaceAngAs(pOrg_);
            pNaviVehicle->setVeloTwd(pOrg_->_rz, pOrg_->_ry, INITIAL_VELO*_n_dispatch_at_once); //初速
            pNaviVehicle->setAcceZero();
            setPositionAt(pOrg_);
        } else {
            setRxFaceAng(pOrg_->out_way_rx_[n]);
            setRyFaceAng(pOrg_->out_way_ry_[n]);
            setRzFaceAng(pOrg_->out_way_rz_[n]);
            pNaviVehicle->setVeloTwd(pOrg_->out_way_rz_[n], pOrg_->out_way_ry_[n], INITIAL_VELO*_n_dispatch_at_once); //初速
            pNaviVehicle->setAcceZero();
            double v = 1.0*n / _n_dispatch_at_once;
            setPosition(pOrg_->_x + (pNaviVehicle->_velo_vc_x * v) ,
                        pOrg_->_y + (pNaviVehicle->_velo_vc_y * v) ,
                        pOrg_->_z + (pNaviVehicle->_velo_vc_z * v) );
        }
        if (pF == nullptr) {
            //先端チップ
            GgafDx::GeometricActor* pLockonTarget = pLockonCursor_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //先端でロックオン中
                pLeaderChip_AimInfo_ = getNewAimInfo();
                pLeaderChip_AimInfo_->pLeaderChip = this;
                pLeaderChip_AimInfo_->pTarget = pLockonTarget;
                pLeaderChip_AimInfo_->setT1_and_T1Ahead(
                        pLeaderChip_AimInfo_->pTarget->_x,
                        pLeaderChip_AimInfo_->pTarget->_y,
                        pLeaderChip_AimInfo_->pTarget->_z);
                // aim_time_out_t1 を概算で求めておく
                dxcoord x = C_DX(_x);
                dxcoord y = C_DX(_y);
                dxcoord z = C_DX(_z);
                dxcoord tx = C_DX(pLockonTarget->_x);
                dxcoord ty = C_DX(pLockonTarget->_y);
                dxcoord tz = C_DX(pLockonTarget->_z);
                D3DXVECTOR3 V(tx-x, ty-y, tz-z);
                D3DXVECTOR3 W(C_DX(pNaviVehicle->_velo_vc_x), C_DX(pNaviVehicle->_velo_vc_y), C_DX(pNaviVehicle->_velo_vc_z));
                float rad = UTIL::get3DRadAngle(V, W); //成す角
                double rate_estimate = RCNV(0.0, PI, rad, 1.0, 4.5); //直線に近ければ 1.0 ～ 真逆 4.5 の割合を見積もる(※真横が往復で、約2.0 と考えた)
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                //距離÷初期速度 に割合を乗じて、到達時間を概算で見積もる。
                pLeaderChip_AimInfo_->aim_time_out_t1 = getActiveFrame() + ((t1_d / pNaviVehicle->_velo) * rate_estimate);
            } else {
                //先端でロックオンしていない
                pLeaderChip_AimInfo_ = getNewAimInfo();
                pLeaderChip_AimInfo_->pLeaderChip = this;
                pLeaderChip_AimInfo_->pTarget = nullptr;
                pLeaderChip_AimInfo_->aim_time_out_t1 = 0;
            }
        } else {
            //先端以外は前のレーザーチップのを受け継ぐ
            pLeaderChip_AimInfo_ = pF->pLeaderChip_AimInfo_; //参照
#ifdef MY_DEBUG
if (pLeaderChip_AimInfo_ == nullptr) {
throwCriticalException("pLeaderChip_AimInfo_ が引き継がれていません！"<<this<<
                       " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }
    }

    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。
    MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
    if (getActiveFrame() > 2) { // > 1ではだめ（N_DISPATCH_AT_ONCEのため）
        if (pF && pF->isActive()) {
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
            //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
            //_x,_y,_z にはまだ変な値が入っている。
            if (pB && pB->isActive()) {
//                if (_dispatch_index == 0) { //N_DISPATCH_AT_ONCE の節目が角張るので平均化を強くした
//                    _x = _x + (coord)((pB->_x-_x)*0.4 + (pF->_x-_x)*0.5);
//                    _y = _y + (coord)((pB->_y-_y)*0.4 + (pF->_y-_y)*0.5);
//                    _z = _z + (coord)((pB->_z-_z)*0.4 + (pF->_z-_z)*0.5);
//                } else {
//                    //中間座標に再設定
//                    //座標の重みは、（ひとつ前, 自身, 一つ先）＝ (0.2, 0.3, 0.4)
//                    _x = _x + (coord)((pB->_x-_x)*0.2 + (pF->_x-_x)*0.4);
//                    _y = _y + (coord)((pB->_y-_y)*0.2 + (pF->_y-_y)*0.4);
//                    _z = _z + (coord)((pB->_z-_z)*0.2 + (pF->_z-_z)*0.4);
//                }


//                if (pF->_dispatch_index + 1 == _dispatch_index) {
//
//                    if (_dispatch_index+1 == pB->_dispatch_index) {
//                        _x = (pB->_x + _x + pF->_x) / 3;
//                        _y = (pB->_y + _y + pF->_y) / 3;
//                        _z = (pB->_z + _z + pF->_z) / 3;
//
//                    } else {
//                        //pB は別のディスパッチグループ
//                        //重みは、（pB, 自身, pF） ＝ (0.5, 0.3, 0.2)
//                        _x = _x + (coord)((pB->_x-_x)*0.5 + (pF->_x-_x)*0.2);
//                        _y = _y + (coord)((pB->_y-_y)*0.5 + (pF->_y-_y)*0.2);
//                        _z = _z + (coord)((pB->_z-_z)*0.5 + (pF->_z-_z)*0.2);
//                    }
//
//                } else {
//                    //pF は別のディスパッチグループ
//                    //重みは、（pB, 自身, pF） ＝ (0.5, 0.3, 0.6)
//                    _x = _x + (coord)((pB->_x-_x)*0.2 + (pF->_x-_x)*0.5);
//                    _y = _y + (coord)((pB->_y-_y)*0.2 + (pF->_y-_y)*0.5);
//                    _z = _z + (coord)((pB->_z-_z)*0.2 + (pF->_z-_z)*0.5);
//                }


                _x = (pB->_x + _x + pF->_x) / 3;
                _y = (pB->_y + _y + pF->_y) / 3;
                _z = (pB->_z + _z + pF->_z) / 3;


                //TODO:平均すると先がへにょる
                //TODO:平均しないとぎざぎざになる
                //TODO:N_DISPATCH_AT_ONCE 単位で、まとまって動く、１フレームN_DISPATCH_AT_ONCE個のチップを NaviVehicle 処理するので、加速度に上限があるためグループでまとまってしまう？
                //N_DISPATCH_AT_ONCE 3 以上じゃだめかも・・・


                //速度ベクトルも平均化してギザギザ対策
//                GgafDx::NaviVehicle* pF_pNaviVehicle = pF->getNaviVehicle();
//                GgafDx::NaviVehicle* pB_pNaviVehicle = pB->getNaviVehicle();
//                if (pNaviVehicle->_velo > 0 && pF_pNaviVehicle->_velo > 0 && pB_pNaviVehicle->_velo > 0) {
//                    pNaviVehicle->_velo_vc_x = pNaviVehicle->_velo_vc_x + (velo)((pB_pNaviVehicle->_velo_vc_x - pNaviVehicle->_velo_vc_x)*0.2 + (pF_pNaviVehicle->_velo_vc_x - pNaviVehicle->_velo_vc_x)*0.4);
//                    pNaviVehicle->_velo_vc_y = pNaviVehicle->_velo_vc_y + (velo)((pB_pNaviVehicle->_velo_vc_y - pNaviVehicle->_velo_vc_y)*0.2 + (pF_pNaviVehicle->_velo_vc_y - pNaviVehicle->_velo_vc_y)*0.4);
//                    pNaviVehicle->_velo_vc_z = pNaviVehicle->_velo_vc_z + (velo)((pB_pNaviVehicle->_velo_vc_z - pNaviVehicle->_velo_vc_z)*0.2 + (pF_pNaviVehicle->_velo_vc_z - pNaviVehicle->_velo_vc_z)*0.4);
//                    pNaviVehicle->_velo = pNaviVehicle->_velo + (velo)((pB_pNaviVehicle->_velo - pNaviVehicle->_velo)*0.2 + (pF_pNaviVehicle->_velo - pNaviVehicle->_velo)*0.4);
//                }
                GgafDx::NaviVehicle* pF_pNaviVehicle = pF->getNaviVehicle();
                if (pNaviVehicle->_velo > 0 && pF_pNaviVehicle->_velo > 0 ) {


                }


            } else {
                //レーザー末尾処理
                //レーザー末尾がはねる（髪の毛がはねるみたいになる）のを若干防ぐ
                //一つ前と、自身のアングル値（＝向き）（_rz, _ry)の差と距離をとり、
                //自身のアングル差を加えて、距離を離した仮想の点を、自身の一つ後ろの点として予測する。
                coord d_pF = UTIL::getDistance(this, pF); //前のチップとの距離
                angle diff_rz = UTIL::getAngDiff(pF->_rz, _rz); //前のチップとの _rz 方向値差
                angle diff_ry = UTIL::getAngDiff(pF->_ry, _ry); //前のチップとの _ry 方向値差
                angle v_b_rz = UTIL::addAng(_rz, diff_rz*0.625); //自身の方向値に、_rz 方向値差を加える（0.625 倍は、気持ち緩めようと思ったため）
                angle v_b_ry = UTIL::addAng(_ry, diff_ry*0.625); //自身の方向値に、_ry 方向値差を加える（0.625 倍は、気持ち緩めようと思ったため）
                double v_b_vx, v_b_vy, v_b_vz;
                UTIL::convRzRyToVector(v_b_rz,v_b_ry,             //加えた方向の方向ベクトルを求める、仮想の自身の一つ後ろの点の座標を得るため。
                                       v_b_vx, v_b_vy, v_b_vz);
                coord v_b_x = _x - v_b_vx*d_pF;  //方向ベクトルに距離を乗じて座標を求める
                coord v_b_y = _y - v_b_vy*d_pF;
                coord v_b_z = _z - v_b_vz*d_pF;

                _x = _x + (coord)((v_b_x-_x)*0.2 + (pF->_x-_x)*0.4);
                _y = _y + (coord)((v_b_y-_y)*0.2 + (pF->_y-_y)*0.4);
                _z = _z + (coord)((v_b_z-_z)*0.2 + (pF->_z-_z)*0.4);
            }
        }

        if (pF) {
            setFaceAngTwd(pF);
        } else {
            //レーザーチップの向きを移動方向に設定（先端チップ）
            UTIL::convVectorToRzRy(pNaviVehicle->_velo_vc_x,
                                   pNaviVehicle->_velo_vc_y,
                                   pNaviVehicle->_velo_vc_z,
                                   _rz, _ry );
        }

    }
    VvMyActor<WateringLaserChip>::processSettlementBehavior();
}

void MyBunshinWateringLaserChip001::processJudgement() {
    if (isOutOfSpacetime()) {
//        if (pLeaderChip_AimInfo_->pLeaderChip == this) {
//            //T2情報を残しておく
//            pLeaderChip_AimInfo_->setT2(_x, _y, _z);
//            pLeaderChip_AimInfo_->aim_time_out_t2 = getActiveFrame();
//            if (pLeaderChip_AimInfo_->aim_time_out_t1 == 0) {
//                pLeaderChip_AimInfo_->setT1_and_T1Ahead(pLeaderChip_AimInfo_->t2_x, pLeaderChip_AimInfo_->t2_y, pLeaderChip_AimInfo_->t2_z);
//                pLeaderChip_AimInfo_->aim_time_out_t1 = getActiveFrame();
//            }
//        }
        sayonara();
    }
}

bool MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ, bool chk_done) {
    //    |                               仮的    →
    //    |                                ┌    vVT(vVTx,vVTy,vVTz)
    //    |                                ^ ＼
    //    |                                |   ＼
    //    |                                |     …                                                 |
    //    |                                |       |d|*7                                            |
    //    |                                |         …                                             |
    //    |                                |           ＼                      →                   |
    //    |                                |              的  座標(tX,tY,tZ)＝ vT(vTx,vTy,vTz)      |      仮的
    //    |                                |             ^ ┌        →    →                       |       ↑
    //    |                                |            /    ＼ |d|= vT - vVM                       |       的    ^
    //    |                                |           /       ＼       →                          |       ↑    |
    //    |                                |          /         ┐仮自 vVM(vVMx,vVMy,vVMz)          |      仮自   |      ^
    //    |                                |    |vT| /        ／                                    |       ↑    |      |
    //    |                                |        /       ／                                      |       ｜    |      |
    //    |                                |       /      ／                                        |       ｜    ||vT|  ||vT|*0.9
    //    |                                |      /     ／          *0.9の意味は右図のように直線に  |       ｜    |      |
    //    |                                |     /    ／ |vT|*0.9   並んだ際に仮自 が 的 を追い     |       ｜    |      |
    //    |                                |    /   ／              越さないようにするため          |       ｜    |      |
    //    |        設定される加速度の方向  |   /  ／                                                |       ｜    |      |
    //    |   setAcceByVc(vVTx,vVTy,vVTz)  ^  / ┐ 現在の移動方向ベクトルNaviVehicle                |       自    v      v
    //    |※メソッド内でMAX_ACCE_RENGE    | /／ (_velo_vc_x,_velo_vc_x,_velo_vc_z)                 |
    //    |  範囲に調整される              自                                                    ---+---------------------------
    //    |                      座標(_x,_y,_z)=ベクトルの基点(0,0,0)                               |
    // ---+------------------------------------------
    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    //自→的、方向ベクトル (→vT)
    coord vTx = tX - _x;
    coord vTy = tY - _y;
    coord vTz = tZ - _z;
    //|vT|
    coord lvT = UTIL::getDistanceFromOrigin(vTx, vTy, vTz);
    double ve = pNaviVehicle->_velo;
    //自→仮自  (→vVM)
    coord vVMx = lvT * (pNaviVehicle->_velo_vc_x / ve)*0.9;
    coord vVMy = lvT * (pNaviVehicle->_velo_vc_y / ve)*0.9;
    coord vVMz = lvT * (pNaviVehicle->_velo_vc_z / ve)*0.9;
    //仮自→仮的*10、((→vT) - (→vVM))*8  仮自から的を距離1として、的から距離7場所
    coord vVTx = (vTx - vVMx)*8;
    coord vVTy = (vTy - vVMy)*8;
    coord vVTz = (vTz - vVMz)*8;
    //自→仮的 へ加速度設定（※メソッド内で MAX_ACCE_RENGE 範囲に調整される）
    pNaviVehicle->setAcceByVc(vVTx, vVTy, vVTz);
    if (chk_done) {
        //衝突したら終了
        if (lvT < _hitarea_edge_length) {
//		if (lvT< MyBunshinWateringLaserChip001::MAX_VELO) {
            //諦める
            //_TRACE_("aimChip("<<tX<<","<<tY<<","<<tZ<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" BOXHIT で done!!");
            return true;
        }
        //ターゲットの付近(pNaviVehicle->_top_velo*2)で、内積が負の場合、ターゲットを惜しくも通り越してしまったと考えられないだろうか。
        //その場合は、諦めて戻ってきてほしくない。
        if (lvT < _hitarea_edge_length*3)  { //pNaviVehicle->_top_velo*2) {
            //自分の速度方向ベクトルと、ターゲットへの方向ベクトルの内積（ベクトルの違い具合）を計算し、
            //Aim を諦めるかどうかの判断に使用する。
            //自分の速度方向ベクトル
            velo velo_vc_x = pNaviVehicle->_velo_vc_x;
            velo velo_vc_y = pNaviVehicle->_velo_vc_y;
            velo velo_vc_z = pNaviVehicle->_velo_vc_z;
            //ターゲットへの方向ベクトル  vTx, vTy, vTz
            //内積
            coord dot = velo_vc_x*vTx + velo_vc_y*vTy + velo_vc_z*vTz;
            if (dot < 0) {
                //諦める
                //_TRACE_("aimChip("<<tX<<","<<tY<<","<<tZ<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" dot で done!!");
                return true;
            }
        }
    }
    return false;
}

void MyBunshinWateringLaserChip001::onHit(const GgafCore::Actor* prm_pOtherActor) {
    GgafDx::GeometricActor* pOther = (GgafDx::GeometricActor*) prm_pOtherActor;
    //ヒットエフェクト
    GgafDx::FigureActor* pE = UTIL::activateExplosionEffectOf(this); //爆発エフェクト出現
    GgafDx::CollisionPart* pColliPart = getWorldCollisionChecker()->getLastHitCollisionPart();
    pE->setPosition(pE->_x + pColliPart->_cx, pE->_y + pColliPart->_cy, pE->_z + pColliPart->_cz); //爆発エフェクト位置を補正

    if ((pOther->lookUpKind() & KIND_ENEMY_BODY) ) {
        //ロックオン可能アクターならロックオン
        if (pOther->getStatus()->get(STAT_LockonAble) == 1) {
            pOrg_->pLockonCtrler_->lockon(pOther);
        }

        int stamina = calcStamina(pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();//痛感テスト
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
        AimInfo* pLeaderChip_AimInfo = pLeaderChip_AimInfo_;
//        if (this == pLeaderChip_AimInfo->pLeaderChip && pLeaderChip_AimInfo->pTarget == prm_pOtherActor) {
        //先端が目標に見事命中した場合もT1終了
        if (pLeaderChip_AimInfo->pTarget == prm_pOtherActor) {
             //目標に見事命中した場合もT1終了
            frame active_frame = getActiveFrame();
            if (pLeaderChip_AimInfo->aim_time_out_t1 > active_frame) {
                //_TRACE_("aimChip(" << pLeaderChip_AimInfo->t1_ahead_x << "," << pLeaderChip_AimInfo->t1_ahead_y << "," << pLeaderChip_AimInfo->t1_ahead_z << ") this=(" << _x << "," << _y << "," << _z << ") name=" << getName() << "@" << getActiveFrame() << " onHit で done!!");
                pLeaderChip_AimInfo->aim_time_out_t1 = active_frame;
            }
            getPhase()->change(PHASE_T2);
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    //後続チップ(リーダーのpLeaderChip_AimInfo_を参照している)のために、pLeaderChip_AimInfo_の情報を後始末
    if (pLeaderChip_AimInfo_->pLeaderChip == this) {
        pLeaderChip_AimInfo_->pLeaderChip = nullptr;
    }
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    pLeaderChip_AimInfo_ = nullptr;
    VvMyActor<WateringLaserChip>::onInactive();
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

