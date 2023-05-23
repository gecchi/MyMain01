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
const int MyBunshinWateringLaserChip001::R_MAX_ACCE = 18; //MAX_VELO に対する加速度、この値を大きくすると、カーブが緩くなる
const velo MyBunshinWateringLaserChip001::INITIAL_VELO = MAX_VELO*0.7; //レーザー発射時の初期速度
const acce MyBunshinWateringLaserChip001::MAX_ACCE_RENGE = MAX_VELO/R_MAX_ACCE;
const velo MyBunshinWateringLaserChip001::MIN_VELO_ = MyBunshinWateringLaserChip001::INITIAL_VELO/20; // ÷8 は、最低移動する各軸のINITIAL_VELOの割合
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
}

void MyBunshinWateringLaserChip001::processBehavior() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;

    frame active_frame = getActiveFrame();
    double power = active_frame <= 300 ? UTIL::SHOT_POWER[active_frame] : UTIL::SHOT_POWER[300];
    getStatus()->set(STAT_AttackPowerRate, power);
    _power = power;
    GgafDx::NaviVehicle* const pNaviVehicle = getNaviVehicle();
    MyBunshin::AimInfo* pTipChip_AimInfo = pTipChip_AimInfo_;

    if (active_frame >= 60*10) {
        sayonara(); //保険のタイムアウト10秒
    } else if (pTipChip_AimInfo == nullptr || active_frame < 4) {
        //なにもしない
    } else {
        GgafDx::GeometricActor* pAimTarget = pTipChip_AimInfo->pTarget;
        if (pAimTarget) {
            frame aim_time_out_t1 = pTipChip_AimInfo->aim_time_out_t1;
            //先端チップ時（消える可能性のあるLeaderChipにあらず！）、T1が相変わらずロックオンターゲットならば更新
            if (getInfrontChip() == nullptr && pAimTarget == pLockonCursor_->pTarget_ && pTipChip_AimInfo->spent_frames_to_t1 < aim_time_out_t1) {
                pTipChip_AimInfo->updateT1(pAimTarget->_x, pAimTarget->_y, pAimTarget->_z);  //t1更新
            }
            MyBunshinWateringLaserChip001* pAimLeaderChip = pTipChip_AimInfo->pLeaderChip;
            if (this == pAimLeaderChip) {
                //リーダーチップの場合
                if (pTipChip_AimInfo->spent_frames_to_t1 == 0) {
                    //●Leader が t1 へ Aim 中
                    if (pAimTarget->isActiveInTheTree() && active_frame < aim_time_out_t1)  {
                        //pAimTarget が存命 T1へAim
                        int vx1 = pNaviVehicle->_velo_vc_x;
                        int vy1 = pNaviVehicle->_velo_vc_y;
                        int vz1 = pNaviVehicle->_velo_vc_z;

                        //ここを未来の座標に設定する。
//                        aimChip(pTipChip_AimInfo->t1_x,
//                                pTipChip_AimInfo->t1_y,
//                                pTipChip_AimInfo->t1_z );
                        //ターゲット移動方向のちょっと未来の座標にホーミングする
                        coord aim_t1_x = pTipChip_AimInfo->t1_x;
                        coord aim_t1_y = pTipChip_AimInfo->t1_y;
                        coord aim_t1_z = pTipChip_AimInfo->t1_z;
                        coord vx = aim_t1_x - pTipChip_AimInfo->t1_x_prev;
                        coord vy = aim_t1_y - pTipChip_AimInfo->t1_y_prev;
                        coord vz = aim_t1_z - pTipChip_AimInfo->t1_z_prev;
                        if (vx == 0 &&  vy == 0 && vz == 0) {
                            aimChip(aim_t1_x, aim_t1_y, aim_t1_z);
                        } else {
                            double out_nvx, out_nvy, out_nvz;
                            UTIL::getNormalizedVector(vx, vy, vz,
                                                      out_nvx, out_nvy, out_nvz);
                            //ヒットBOX registerHitAreaCube_AutoGenMidColli(MAX_VELO/4); より
                            coord d_f = ((MAX_VELO/4) / 2);
                            aimChip(aim_t1_x + out_nvx*d_f,
                                    aim_t1_y + out_nvy*d_f,
                                    aim_t1_z + out_nvz*d_f);
                        }

                        int vx2 = pNaviVehicle->_velo_vc_x;
                        int vy2 = pNaviVehicle->_velo_vc_y;
                        int vz2 = pNaviVehicle->_velo_vc_z;

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
                            pTipChip_AimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                        } else {
                            // t1 と衝突したら終了
                            static const coord renge = MyBunshinWateringLaserChip001::MAX_VELO;
                            static const ucoord renge2 = renge*2;
                            if ( (ucoord)(_x - pTipChip_AimInfo->t1_x + renge) <= renge2) {
                                if ( (ucoord)(_y - pTipChip_AimInfo->t1_y + renge) <= renge2) {
                                    if ( (ucoord)(_z - pTipChip_AimInfo->t1_z + renge) <= renge2) {
                                        pTipChip_AimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                                    }
                                }
                            }
                        }

                    } else {
                        //初めは pAimTarget があったのに、途中で消えた。
                        pTipChip_AimInfo_->spent_frames_to_t1 = active_frame; //Aim t1 終了
                    }
                } else if (pTipChip_AimInfo->spent_frames_to_t2 == 0) {
                    //●Leader が t1 へ Aim し終わったあと
                    //t2を決める
                    LaserChip* pB = getBehindChip();
                    if (pB) {
                        pB = pB->getBehindChip();
                        if (pB) {
                            pB = pB->getBehindChip();
                        }
                    }
                    if (pB) {
                        pTipChip_AimInfo->setT2BySphere(ZF_R, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                    } else {
                        pTipChip_AimInfo->setT2BySphere(ZF_R, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                    }
                    coord t2_d = UTIL::getDistance(_x, _y, _z,
                                                   pTipChip_AimInfo->t2_x,
                                                   pTipChip_AimInfo->t2_y,
                                                   pTipChip_AimInfo->t2_z);
                    pTipChip_AimInfo->spent_frames_to_t2 = active_frame + (frame)(t2_d/(MyBunshinWateringLaserChip001::MAX_VELO*_n_dispatch_at_once)); //t2到達時間概算
                    aimChip(pTipChip_AimInfo->t2_x,
                            pTipChip_AimInfo->t2_y,
                            pTipChip_AimInfo->t2_z );
                } else {
                    //●Leader が t2 を設定したあと。
                    if (active_frame < pTipChip_AimInfo->spent_frames_to_t2)  {
                        aimChip(pTipChip_AimInfo->t2_x,
                                pTipChip_AimInfo->t2_y,
                                pTipChip_AimInfo->t2_z );
                    } else {
                        aimChip(_x + pNaviVehicle->_velo_vc_x*4+1,
                                _y + pNaviVehicle->_velo_vc_y*4+1,
                                _z + pNaviVehicle->_velo_vc_z*4+1 );
                    }
                }
            } else {
                //リーダーチップ以外
                if (pTipChip_AimInfo->spent_frames_to_t1 == 0) {
                    //●Leader以外が t1 が定まるまでの動き
                    if (pAimLeaderChip) {
                        coord aim_t1_x = pTipChip_AimInfo->t1_x;
                        coord aim_t1_y = pTipChip_AimInfo->t1_y;
                        coord aim_t1_z = pTipChip_AimInfo->t1_z;
                        aimChip(aim_t1_x,
                                aim_t1_y,
                                aim_t1_z );
                    } else {
                        aimChip(_x + pNaviVehicle->_velo_vc_x*4+1,
                                _y + pNaviVehicle->_velo_vc_y*4+1,
                                _z + pNaviVehicle->_velo_vc_z*4+1 );
                    }
                } else if (active_frame <= pTipChip_AimInfo->spent_frames_to_t1) {
                    //●Leader以外が t1 が定まってから t1 到達までの動き
                    aimChip(pTipChip_AimInfo->t1_x,
                            pTipChip_AimInfo->t1_y,
                            pTipChip_AimInfo->t1_z );
                } else if (active_frame > pTipChip_AimInfo->spent_frames_to_t1) {
                    //●Leader以外が t1 を通過
                    if (pTipChip_AimInfo->spent_frames_to_t2 == 0) {
                        //●その後 Leader以外が t2 が定まるまでの動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pNaviVehicle->_velo_vc_x*4+1,
                                    _y + pNaviVehicle->_velo_vc_y*4+1,
                                    _z + pNaviVehicle->_velo_vc_z*4+1 );
                        }
                    } else if (active_frame <= pTipChip_AimInfo->spent_frames_to_t2) {
                        //●その後 Leader以外が t2 が定まって、t2に向かうまでの動き
                        coord aim_t2_x = pTipChip_AimInfo->t2_x;
                        coord aim_t2_y = pTipChip_AimInfo->t2_y;
                        coord aim_t2_z = pTipChip_AimInfo->t2_z;
                        aimChip(aim_t2_x,
                                aim_t2_y,
                                aim_t2_z );
                    } else if (active_frame > pTipChip_AimInfo->spent_frames_to_t2) {
                        //●その後 Leader以外が t2 を通過した後の動き
                        if (pAimLeaderChip) {
                            aimChip(pAimLeaderChip->_x,
                                    pAimLeaderChip->_y,
                                    pAimLeaderChip->_z );
                        } else {
                            aimChip(_x + pNaviVehicle->_velo_vc_x*4+1,
                                    _y + pNaviVehicle->_velo_vc_y*4+1,
                                    _z + pNaviVehicle->_velo_vc_z*4+1 );
                        }
                    } else {
                        _TRACE_("【警告】ありえない");
                    }
                }
            }

        } //if (pAimTarget)

    }
    pNaviVehicle->behave();
    VvMyActor<WateringLaserChip>::processBehavior();
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
                pTipChip_AimInfo_->setT1(
                        pTipChip_AimInfo_->pTarget->_x,
                        pTipChip_AimInfo_->pTarget->_y,
                        pTipChip_AimInfo_->pTarget->_z);
                // aim_time_out_t1 を概算で求めておく
                coord t1_d = UTIL::getDistance(this, pLockonTarget);
                pTipChip_AimInfo_->aim_time_out_t1 = (t1_d / (MyBunshinWateringLaserChip001::INITIAL_VELO*_n_dispatch_at_once));
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
            pTipChip_AimInfo_->t2_x = _x;
            pTipChip_AimInfo_->t2_y = _y;
            pTipChip_AimInfo_->t2_z = _z;
            pTipChip_AimInfo_->spent_frames_to_t2 = getActiveFrame();
            if (pTipChip_AimInfo_->spent_frames_to_t1 == 0) {
                pTipChip_AimInfo_->setT1(pTipChip_AimInfo_->t2_x, pTipChip_AimInfo_->t2_y, pTipChip_AimInfo_->t2_z);
                pTipChip_AimInfo_->spent_frames_to_t1 = getActiveFrame();
            }
        }
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::aimChip(int tX, int tY, int tZ) {
    //
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
        if (this == pTipChip_AimInfo->pLeaderChip && pTipChip_AimInfo->pTarget == prm_pOtherActor) {
            //先端が目標に見事命中した場合もT1終了
            pTipChip_AimInfo->setT1(_x, _y, _z);
            pTipChip_AimInfo->spent_frames_to_t1 = getActiveFrame();
        }

    } else if (pOther->lookUpKind() & KIND_CHIKEI) {
        //地形相手は無条件さようなら
        sayonara();
    }
}

void MyBunshinWateringLaserChip001::onInactive() {
    static const Spacetime* pSpaceTime =  pCARETAKER->getSpacetime();
    static const double ZF_R = pSpaceTime->_x_bound_right - pSpaceTime->_x_bound_left;

    MyBunshin::AimInfo* pTipChip_AimInfo = pTipChip_AimInfo_;
    if (pTipChip_AimInfo && pTipChip_AimInfo->pLeaderChip == this) {
        if (pTipChip_AimInfo->spent_frames_to_t2 == 0) {
            frame aim_time_out_t1 = pTipChip_AimInfo_->aim_time_out_t1;
            MyBunshinWateringLaserChip001* pB = (MyBunshinWateringLaserChip001*)getBehindChip();
            if (pB) {
                pTipChip_AimInfo->setT2BySphere(ZF_R, pB->_x, pB->_y, pB->_z, _x, _y, _z);
                pTipChip_AimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            } else {
                pTipChip_AimInfo->setT2BySphere(ZF_R, pOrg_->_x, pOrg_->_y, pOrg_->_z, _x, _y, _z);
                pTipChip_AimInfo->spent_frames_to_t2 = getActiveFrame() + aim_time_out_t1;
            }

            if (pTipChip_AimInfo->spent_frames_to_t1 == 0) {
                pTipChip_AimInfo->setT1(pTipChip_AimInfo->t2_x, pTipChip_AimInfo->t2_y, pTipChip_AimInfo->t2_z);
                pTipChip_AimInfo->spent_frames_to_t1 = getActiveFrame() + aim_time_out_t1;
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

