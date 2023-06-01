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

const velo MyBunshinWateringLaserChip001::MAX_VELO = PX_C(512); //この値を大きくすると、最高速度が早くなる。
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 20; //MAX_VELO に対する加速度、この値を大きくすると、カーブが緩くなる
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO*0.7; //レーザー発射時の初期速度
const acce MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO/R_MAX_ACCE;
const velo MyBunshinWateringLaserChip001::MIN_VELO_ = MyBunshinWateringLaserChip001::INITIAL_VELO/3; // ÷3 は、最低移動する各軸のINITIAL_VELOの割合
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
    pTipChip_AimInfo_ = nullptr;
    inv_cnt_ = 0;
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
    pTipChip_AimInfo_ = nullptr;
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
    MyBunshin::AimInfo* pTipChip_AimInfo = pTipChip_AimInfo_;

    if (getActiveFrame() >= 60*10) {
        sayonara(); //保険のタイムアウト10秒
    } else if (pTipChip_AimInfo == nullptr || active_frame < 4) {
        //なにもしない
    } else {
        if (pTipChip_AimInfo->pTarget == nullptr) {
            //なにもしない
        } else {
            processBehavior_Aiming();
        }
    }

    getNaviVehicle()->behave();
    VvMyActor<WateringLaserChip>::processBehavior();
}

void MyBunshinWateringLaserChip001::processBehavior_Aiming() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;
    MyBunshin::AimInfo* pTipChip_AimInfo = pTipChip_AimInfo_;
    GgafDx::GeometricActor* pAimTarget = pTipChip_AimInfo->pTarget;
    frame active_frame = getActiveFrame();
    MyBunshinWateringLaserChip001* pAimLeaderChip = pTipChip_AimInfo->pLeaderChip;
    GgafDx::NaviVehicle* pNaviVehicle = getNaviVehicle();
    GgafCore::Phase* pPhase = getPhase();
    switch (pPhase->getCurrent()) {
         case PHASE_T1: {
            if (this == pAimLeaderChip) {
                //リーダーチップの場合
                if (pAimTarget && pAimTarget->isActiveInTheTree() ) {
                    //ターゲット存命ならばT1座標更新
                    pTipChip_AimInfo->updateT1(pAimTarget->_x, pAimTarget->_y, pAimTarget->_z);  //t1更新

                    //T1座標のちょっと未来の座標を求め t1_ahead に設定
                    coord aim_t1_x = pTipChip_AimInfo->t1_x;
                    coord aim_t1_y = pTipChip_AimInfo->t1_y;
                    coord aim_t1_z = pTipChip_AimInfo->t1_z;
                    coord vx = aim_t1_x - pTipChip_AimInfo->t1_x_prev;
                    coord vy = aim_t1_y - pTipChip_AimInfo->t1_y_prev;
                    coord vz = aim_t1_z - pTipChip_AimInfo->t1_z_prev;
                    if (vx == 0 &&  vy == 0 && vz == 0) {
                        pTipChip_AimInfo->setT1Ahead(aim_t1_x, aim_t1_y, aim_t1_z);
                    } else {
                        double out_nvx, out_nvy, out_nvz;
                        UTIL::getNormalizedVector(vx, vy, vz,
                                                  out_nvx, out_nvy, out_nvz);
                        //ヒットBOX registerHitAreaCube_AutoGenMidColli(MAX_VELO/4); より
                        coord d_f = _hitarea_edge_length/2;
                        pTipChip_AimInfo->setT1Ahead(aim_t1_x + out_nvx*d_f,
                                                     aim_t1_y + out_nvy*d_f,
                                                     aim_t1_z + out_nvz*d_f);
                    }


                } else {
                    //ターゲット消失した場合
                }

            } else {
                //リーダーチップ以外の場合
                //T1Ahead が必ずあるはず
            }

            if (pTipChip_AimInfo->aim_time_out_t1 <= active_frame) {
                //T1 タイムアウトで終了
                //_TRACE_("aimChip("<<pTipChip_AimInfo->t1_ahead_x<<","<<pTipChip_AimInfo->t1_ahead_y<<","<<pTipChip_AimInfo->t1_ahead_z<<") this=(" << _x << "," << _y << "," << _z << ") name="<<getName()<<"@"<<getActiveFrame()<<" T1 タイムアウト で done!!");
                pPhase->changeImmediately(PHASE_T2);
                goto L_PHASE_T2;
            }
            //T1Ahead（T1ちょっと未来）にAim
            bool is_done = aimChip(pTipChip_AimInfo->t1_ahead_x,
                                   pTipChip_AimInfo->t1_ahead_y,
                                   pTipChip_AimInfo->t1_ahead_z,
                                   true);
            if (is_done) {
                //T1Ahead に衝突、あるいは、通り過ぎで終了
                if (pTipChip_AimInfo->aim_time_out_t1 > active_frame) {
                    //早めれるなら早めよう
                    pTipChip_AimInfo->aim_time_out_t1 = active_frame;
                }
                pPhase->changeImmediately(PHASE_T2);
                goto L_PHASE_T2;
            }

            break;
         }

L_PHASE_T2:
         case PHASE_T2: {
             if (pPhase->hasJustChanged() ) {
                 if (pTipChip_AimInfo->aim_time_out_t2 == 0) {
                     //T2 未設定だった場合、T2 の座標設定と概算を求める
                     LaserChip* pB = getBehindChip();
                     if (pB) { pB = pB->getBehindChip(); if (pB) {  pB = pB->getBehindChip(); }  }
                     if (pB) {
                         pTipChip_AimInfo->setT2BySphere(ZF_R, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                     } else {
                         pTipChip_AimInfo->setT2BySphere(ZF_R, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                     }
                     coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                    pTipChip_AimInfo->t2_x,
                                                    pTipChip_AimInfo->t2_y,
                                                    pTipChip_AimInfo->t2_z);
                     pTipChip_AimInfo->aim_time_out_t2 =
                             active_frame + (frame)(t2_d/(MyBunshinWateringLaserChip001::MAX_VELO*_n_dispatch_at_once)); //T2到達時間概算
                 }
             }
             if (pTipChip_AimInfo->aim_time_out_t2 <= active_frame) {
                 //T2 終了時の処理
                 pPhase->changeImmediately(PHASE_T2_AFTER);
                 goto L_PHASE_T2_AFTER;
             }
             aimChip(pTipChip_AimInfo->t2_x,
                     pTipChip_AimInfo->t2_y,
                     pTipChip_AimInfo->t2_z );
             break;
         }

L_PHASE_T2_AFTER:
         case PHASE_T2_AFTER: {
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
        //チップの初期設定
        //ロックオン情報の引き継ぎ
        MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*) getInfrontChip();
        if (pF == nullptr) {
            //先端チップ
            GgafDx::GeometricActor* pLockonTarget = pLockonCursor_->pTarget_;
            if (pLockonTarget && pLockonTarget->isActiveInTheTree()) {
                //先端でロックオン中
                pTipChip_AimInfo_ = pOrg_->getNewAimInfo();
                pTipChip_AimInfo_->pLeaderChip = this;
                pTipChip_AimInfo_->pTarget = pLockonTarget;
                pTipChip_AimInfo_->setT1_and_T1Ahead(
                        pTipChip_AimInfo_->pTarget->_x,
                        pTipChip_AimInfo_->pTarget->_y,
                        pTipChip_AimInfo_->pTarget->_z);
                // aim_time_out_t1 を概算で求めておく
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                pTipChip_AimInfo_->aim_time_out_t1 = (t1_d / (MyBunshinWateringLaserChip001::INITIAL_VELO*_n_dispatch_at_once) * 1.5); //1.5 は気持ち多め
            } else {
                //先端でロックオンしていない
                pTipChip_AimInfo_ = pOrg_->getNewAimInfo();
                pTipChip_AimInfo_->pLeaderChip = this;
                pTipChip_AimInfo_->pTarget = nullptr;
            }
        } else {
            //先端以外は前のレーザーチップのを受け継ぐ
            pTipChip_AimInfo_ = pF->pTipChip_AimInfo_; //参照
#ifdef MY_DEBUG
if (pTipChip_AimInfo_ == nullptr) {
throwCriticalException("pTipChip_AimInfo_ が引き継がれていません！"<<this<<
                       " _frame_of_life_when_activation="<<_frame_of_life_when_activation);
}
#endif
        }
        //活動開始初回フレーム、チップの速度と向きの初期設定
        setFaceAngAs(pOrg_);
        //setPositionAt(pOrg_);
        pNaviVehicle->setVeloTwd(_rz, _ry, INITIAL_VELO*_n_dispatch_at_once); //初速はここで
        pNaviVehicle->setAcceZero();
        int n = _n_dispatch_at_once-1 - _dispatch_index;
        if (n == 0) {
            setPositionAt(pOrg_);
        } else {
//            setPosition(pOrg_->_x + ((pNaviVehicle->_velo_vc_x/_n_dispatch_at_once) * n) ,
//                        pOrg_->_y + ((pNaviVehicle->_velo_vc_y/_n_dispatch_at_once) * n) ,
//                        pOrg_->_z + ((pNaviVehicle->_velo_vc_z/_n_dispatch_at_once) * n) );
            double v = 1.0*n / _n_dispatch_at_once;
            setPosition(pOrg_->_x + (pNaviVehicle->_velo_vc_x * v) ,
                        pOrg_->_y + (pNaviVehicle->_velo_vc_y * v) ,
                        pOrg_->_z + (pNaviVehicle->_velo_vc_z * v) );
        }
    }

    //平均曲線座標設定。(レーザーを滑らかにするノーマライズ）
    //processSettlementBehavior() のメソッドの意義とは離れて座標をいじり移動している。
    //本来は processBehaviorAfter() 的な意味の処理であるが、全レーザーチップが移動後でないと意味がないので
    //仕方ないのでprocessSettlementBehavior()に食い込んでいます。
    //したがって本クラスを継承した場合、継承クラスのprocessSettlementBehavior()では、先頭で呼び出した方が良い。

    MyBunshinWateringLaserChip001* pF = (MyBunshinWateringLaserChip001*)getInfrontChip();
    if (getActiveFrame() > 2) {//FKオブジェクトからのレーザー発射も考慮すると、_tmpXYZ が埋まるのは3フレーム以降。
        if (pF && pF->isActive()) {
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB && pB->isActive()) {
                //_pChip_behind == nullptr の判定だけではだめ。_pChip_behind->_is_active_flg と判定すること
                //なぜなら dispatch の瞬間に_pChip_behind != nullptr となるが、active()により有効になるのは次フレームだから
                //_x,_y,_z にはまだ変な値が入っている。
                //中間座標に再設定
                //座標の重みは、（ひとつ前, 自身, 一つ先）＝ (0.2, 0.3, 0.4)
                _x = _x + (coord)((pB->_x-_x)*0.2 + (pF->_x-_x)*0.4);
                _y = _y + (coord)((pB->_y-_y)*0.2 + (pF->_y-_y)*0.4);
                _z = _z + (coord)((pB->_z-_z)*0.2 + (pF->_z-_z)*0.4);
            } else {
                //レーザー末尾がはねる（髪の毛がはねるみたいになる）のを若干防ぐ
                //一つ前の座標と、自身の座標を直線で結んで、仮想の自分の後ろの点を作成。
                //一つ前の座標、自身の座標、仮想の自分の後ろの点で平均を取る
                //座標の重みは、（仮想のひとつ前, 自身(末尾), 一つ先）＝ (0.2, 0.3, 0.4)
                coord v_b_x = _x - (pF->_x - _x);
                coord v_b_y = _y - (pF->_y - _y);
                coord v_b_z = _z - (pF->_z - _z);
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
        if (pTipChip_AimInfo_->pLeaderChip == this) {
            //T2情報を残しておく
            pTipChip_AimInfo_->setT2(_x, _y, _z);
            pTipChip_AimInfo_->aim_time_out_t2 = getActiveFrame();
            if (pTipChip_AimInfo_->aim_time_out_t1 == 0) {
                pTipChip_AimInfo_->setT1_and_T1Ahead(pTipChip_AimInfo_->t2_x, pTipChip_AimInfo_->t2_y, pTipChip_AimInfo_->t2_z);
                pTipChip_AimInfo_->aim_time_out_t1 = getActiveFrame();
            }
        }
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
        if (lvT < _hitarea_edge_length*4)  { //pNaviVehicle->_top_velo*2) {
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

        int stamina = UTIL::calcMyStamina(this, pOther);
        if (stamina <= 0) {
            //一撃でチップ消滅の攻撃力
            getStatus()->set(STAT_Stamina, default_stamina_);
            sayonara();
        } else {
            //耐えれるならば、通貫し、スタミナ回復（攻撃力100の雑魚ならば通貫）
            getStatus()->set(STAT_Stamina, default_stamina_);
        }
        MyBunshin::AimInfo* pTipChip_AimInfo = pTipChip_AimInfo_;
//        if (this == pTipChip_AimInfo->pLeaderChip && pTipChip_AimInfo->pTarget == prm_pOtherActor) {
        //先端が目標に見事命中した場合もT1終了
        if (pTipChip_AimInfo->pTarget == prm_pOtherActor) {
             //目標に見事命中した場合もT1終了
            frame active_frame = getActiveFrame();
            if (pTipChip_AimInfo->aim_time_out_t1 > active_frame) {
                //_TRACE_("aimChip(" << pTipChip_AimInfo->t1_ahead_x << "," << pTipChip_AimInfo->t1_ahead_y << "," << pTipChip_AimInfo->t1_ahead_z << ") this=(" << _x << "," << _y << "," << _z << ") name=" << getName() << "@" << getActiveFrame() << " onHit で done!!");
                pTipChip_AimInfo->aim_time_out_t1 = active_frame;
            }
            getPhase()->change(PHASE_T2);
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;

    //後続チップ(リーダーのpTipChip_AimInfo_を参照している)のために、pTipChip_AimInfo_の情報を後始末
    MyBunshin::AimInfo* pTipChip_AimInfo = pTipChip_AimInfo_;
    if (pTipChip_AimInfo && pTipChip_AimInfo->pLeaderChip == this) {
        if (pTipChip_AimInfo->aim_time_out_t2 == 0) {
            frame aim_time_out_t1 = pTipChip_AimInfo_->aim_time_out_t1;
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pTipChip_AimInfo->setT2BySphere(ZF_R, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pTipChip_AimInfo->aim_time_out_t2 = getActiveFrame() + aim_time_out_t1;
            } else {
                pTipChip_AimInfo->setT2BySphere(ZF_R, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pTipChip_AimInfo->aim_time_out_t2 = getActiveFrame() + aim_time_out_t1;
            }

            if (pTipChip_AimInfo->aim_time_out_t1 == 0) {
                pTipChip_AimInfo->setT1_and_T1Ahead(pTipChip_AimInfo->t2_x, pTipChip_AimInfo->t2_y, pTipChip_AimInfo->t2_z);
                pTipChip_AimInfo->aim_time_out_t1 = getActiveFrame() + aim_time_out_t1;
            }

        }
        pTipChip_AimInfo->pLeaderChip = nullptr;
    }
    pOrg_ = nullptr;
    pLockonCursor_ = nullptr;
    pTipChip_AimInfo_ = nullptr;
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

