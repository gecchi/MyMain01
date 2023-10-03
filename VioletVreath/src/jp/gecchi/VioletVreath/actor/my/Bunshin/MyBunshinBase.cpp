#include "MyBunshinBase.h"

#include "MyBunshin.h"
#include "MyBunshinController.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/MyShipScene.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/actor/supporter/CoordVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicle.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleFaceAngAssistant.h"
#include "jp/ggaf/dx/actor/supporter/LocoVehicleMvAngAssistant.h"
#include "jp/ggaf/dx/util/GeoElem.h"
#include "jp/ggaf/lib/util/Quaternion.hpp"
#include "jp/ggaf/lib/util/Direction26Util.h"

using namespace GgafLib;
using namespace VioletVreath;

const frame MyBunshinBase::BUNSHIN_D = 16;                  //トレース時の分身と分身の間隔
const angvelo MyBunshinBase::ANGVELO_TURN = D_ANG(2.7);     //分身の向きの角速度
const angvelo MyBunshinBase::ANGVELO_EXPANSE = D_ANG(2.7);  //分身広がり回転角速度
const int MyBunshinBase::RENGE = PX_C(70);                  //分身が戻ってくる時のMAX速さ
const velo MyBunshinBase::VELO_BUNSHIN_FREE_MV = PX_C(20);  //分身フリー移動時の分身の移動速度
int MyBunshinBase::now_bunshin_num_ = 0;

enum {
    TRACE_TWINBEE,   //ツインビーの分身のようなトレース
    TRACE_GRADIUS,   //グラディウスのオプションのようなトレース
    TRACE_FREEZE,    //グラディウスVのType1のオプションフリーズのような動き
};
enum {
    PHASE_INIT,
    PHASE_BUNSHIN_NOMAL_TRACE,
    PHASE_BUNSHIN_FREE_MODE_IGNITED,
    PHASE_BUNSHIN_FREE_MODE_READY,
    PHASE_BUNSHIN_FREE_MODE_MOVE,
    PHASE_BUNSHIN_FREE_MODE_STOP,
    PHASE_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS,
    PHASE_BANPEI,
};

MyBunshinBase::MyBunshinBase(const char* prm_name, unsigned int prm_bunshin_no) :
        DefaultGeometricActor(prm_name) {
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //DefaultGeometricActorでFKベースになるために必要

    trace_offset_.set(0,0,0);
    bunshin_no_ = prm_bunshin_no; //１～
    delay_r_ = RCNV(1,MAX_BUNSHIN_NUM,bunshin_no_,0.4,1.0);
    std::string bunshin_name = "BunshinController" + XTOS(bunshin_no_);
    pMyBunshinController_ = NEW MyBunshinController(bunshin_name.c_str(), this);
    this->appendGroupChildAsFk(pMyBunshinController_,
                          0, PX_C(80), 0,
                          D0ANG, D0ANG, D0ANG);

    pPosTrace_ = NEW PosTrace(MyBunshinBase::BUNSHIN_D * prm_bunshin_no);
    trace_mode_ = TRACE_GRADIUS;
    return_default_pos_frames_ = 0;
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();
    pCoordVehicle->forceVeloXYZRange(-MyBunshinBase::RENGE, MyBunshinBase::RENGE);
    pCoordVehicle->forceAcceXYZRange(-MyBunshinBase::RENGE / 30, MyBunshinBase::RENGE / 30);

    is_free_mode_ = false;
    is_isolate_mode_ = true;
    moving_frames_since_default_pos_ = 0;

    bunshin_default_radius_pos_ = 0;
    bunshin_default_ang_pos_  = 0;
    bunshin_default_expanse_ = 0;
    bunshin_default_angvelo_mv_ = 0;
    bunshin_velo_mv_radius_pos_ = 0;
    bunshin_radius_pos_ = 0;
    c_ax_x_ = 0.0f;
    c_ax_y_ = 0.0f;
    c_ax_z_ = 0.0f;

}

void MyBunshinBase::config(
        coord prm_radius_pos,
        angle prm_ang_pos,
        angle prm_expanse,
        angvelo prm_angvelo_mv)
{
    bunshin_default_radius_pos_ = prm_radius_pos;
    bunshin_default_ang_pos_    = UTIL::simplifyAng(prm_ang_pos);
    bunshin_default_expanse_    = UTIL::simplifyAng(prm_expanse);
    bunshin_default_angvelo_mv_ = prm_angvelo_mv;
    bunshin_velo_mv_radius_pos_ = (velo)(3000.0 * (bunshin_default_radius_pos_/60000.0));
    bunshin_radius_pos_         = bunshin_default_radius_pos_;
}

void MyBunshinBase::initialize() {
    setScaleR(2.0);
    getLocoVehicle()->linkFaceAngByMvAng(true);
}

void MyBunshinBase::onReset() {
    pMyBunshinController_->setRadiusPosition(bunshin_default_radius_pos_);
    bunshin_radius_pos_ = bunshin_default_radius_pos_;

    setRollFaceAng(bunshin_default_ang_pos_);
    getLocoVehicle()->setRollFaceAngVelo(bunshin_default_angvelo_mv_);
    getPhase()->reset(PHASE_INIT);
    trace_mode_ = TRACE_GRADIUS;
}

void MyBunshinBase::onActive() {
    is_free_mode_ = true;
    setPosition(pMYSHIP->_x,pMYSHIP->_y,pMYSHIP->_z);

    int len = pPosTrace_->_num;
    Pos* p = pPosTrace_->_paPos;
    for (int i = 0; i < len; i++) {
        p[i].set(pMYSHIP);
    }
    pMyBunshinController_->setRadiusPosition(0);
    resetBunshin(0);
    //MyBunshinBaseは、activateTree() ではなく、activate() されるため
    //分身のonActive();を手動で呼び出す
    pMyBunshinController_->onActive();
}

void MyBunshinBase::onInactive() {
    //MyBunshinBaseは、inactivateTree() ではなく、inactivate() されるため
    //分身のonInactive();を手動で呼び出す
    pMyBunshinController_->onInactive();
}

void MyBunshinBase::processBehavior() {
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafDx::CoordVehicle* const pCoordVehicle = getCoordVehicle();

    if (is_isolate_mode_) {
        pLocoVehicle->behave();
        pCoordVehicle->behave();
        return;
    }
    MyShip* pMyShip = pMYSHIP;
    VirtualButton* pVbPlay = VV_VB_PLAY;
    const bool is_pressed_VV_VB_OPTION = pVbPlay->isPressed(0, VV_VB_OPTION);
    const bool is_pressed_VV_VB_TURBO  = pVbPlay->isPressed(0, VV_VB_TURBO);
    const bool is_released_up_VV_VB_TURBO = pVbPlay->isReleasedUp(0, VV_VB_TURBO);
    GgafCore::Phase* pPhase = getPhase();

    switch (pPhase->getCurrent()) {
        case PHASE_INIT: {
            pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
            break;
        }
        case PHASE_BUNSHIN_NOMAL_TRACE: { //通常トレース
            if (pPhase->hasJustChanged()) {
                is_free_mode_ = false;
            }
            //初期位置から２０フレーム以内の動きは、TRACE_TWINBEEによって初期位置を維持させる
            if (pMyShip->is_move_) {
                if (is_pressed_VV_VB_OPTION) {
                    moving_frames_since_default_pos_ = 0;
                } else {
                    moving_frames_since_default_pos_++;
                }
            } else {
                if (moving_frames_since_default_pos_ <= 20) {
                    moving_frames_since_default_pos_ = 0;
                }
            }
            trace_mode_ = moving_frames_since_default_pos_ > 20 ? TRACE_GRADIUS : TRACE_TWINBEE;
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_IGNITED: { //分身フリーモード、点火待ち！
            if (pPhase->hasJustChanged()) {
                pMyBunshinController_->effectFreeModeIgnited(); //点火エフェクト
            }
            if (is_pressed_VV_VB_OPTION && is_pressed_VV_VB_TURBO) {
                if (pPhase->getFrame() >= (((MyBunshinBase::now_bunshin_num_ - (bunshin_no_-1) )*5) + 10) ) { //おしりのオプションから
                    pPhase->change(PHASE_BUNSHIN_FREE_MODE_READY);
                }
            } else {
                //分身フリーモード、リセット
                if (is_free_mode_) {
                    pPhase->change(PHASE_BUNSHIN_FREE_MODE_STOP);
                } else {
                    pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
                }
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_READY: { //分身フリーモード発射準備OK
            if (pPhase->hasJustChanged()) {
                pMyBunshinController_->pBunshin_->effectFreeModeReady(); //発射準備OKエフェクト
            }
            if ( pPhase->getFrame() >= ((bunshin_no_-1)*5) + 10 ) { //最後の分身が発射準備OKになったあと+10
                //強制発射
                pPhase->change(PHASE_BUNSHIN_FREE_MODE_MOVE);
            } else {
                if (is_pressed_VV_VB_OPTION) {
                    if(is_released_up_VV_VB_TURBO) { //VV_VB_TURBOだけ離すと即発射。
                        //ハーフ発射！！
                        pPhase->change(PHASE_BUNSHIN_FREE_MODE_MOVE);
                    } else {
                        //発射待ち・・・
                    }
                } else {
                    //VV_VB_OPTION を離すとリセット。
                    //リセット
                    if (is_free_mode_) {
                        pPhase->change(PHASE_BUNSHIN_FREE_MODE_STOP);
                    } else {
                        pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
                    }
                }
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_MOVE: { //分身フリーモード、操作移動！
            if (pPhase->hasJustChanged()) {
                //分身フリーモード移動開始
                pMyBunshinController_->pBunshin_->effectFreeModeLaunch(); //発射エフェクト
                is_free_mode_ = true;
                pCoordVehicle->setXYZZero();
                pCoordVehicle->setAcceXYZZero();
            }
            if (is_pressed_VV_VB_OPTION) {
                //分身フリーモードで移動中
                //オプションの広がり角より、MyBunshinBaseの移動速度と、MyBunshin旋回半径増加速度にベクトル分解。
                angvelo bunshin_angvelo_expance = pMyBunshinController_->getExpanse();
                pLocoVehicle->setMvVelo(ANG_COS(bunshin_angvelo_expance) * MyBunshinBase::VELO_BUNSHIN_FREE_MV); //MyBunshinBase
                pMyBunshinController_->addRadiusPosition(ANG_SIN(bunshin_angvelo_expance) * MyBunshinBase::VELO_BUNSHIN_FREE_MV);
                // VV_VB_OPTION を離すまで待つ・・・
            } else {
                //分身フリーモード、中断待機
                pLocoVehicle->setMvVelo(0);
                pPhase->change(PHASE_BUNSHIN_FREE_MODE_STOP);
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_STOP: { //分身フリーモード、停止中！
            if (pPhase->hasJustChanged()) {
                pMyBunshinController_->effectFreeModePause();
            }
            break;
        }
        case PHASE_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS: { //分身元の場所に戻る！
            if (pPhase->hasJustChanged()) {
            }
            const Pos* pTargetPos = pPosTrace_->getNext(); //通常時の本来の分身の座標位置を目標にする
            const coord tx = pTargetPos->x;
            const coord ty = pTargetPos->y;
            const coord tz = pTargetPos->z;
            if (pPhase->getFrame() == 3*(bunshin_no_-1)) { //ばらつかせ

                // (0,1,0) × RxRzRy ＝ ( (cosRx*-sinRz*cosRy + sinRx*sinRy),  cosRx*cosRz, (cosRx*-sinRz*-sinRy + sinRx*cosRy) )
                const double sinRx = ANG_SIN(_rx);
                const double cosRx = ANG_COS(_rx);
                const double sinRy = ANG_SIN(_ry);
                const double cosRy = ANG_COS(_ry);
                const double sinRz = ANG_SIN(_rz);
                const double cosRz = ANG_COS(_rz);
                pCoordVehicle->setVeloXYZ( (cosRx*-sinRz*cosRy + sinRx*sinRy)  * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                          (cosRx*cosRz)                       * MyBunshinBase::VELO_BUNSHIN_FREE_MV,
                                          (cosRx*-sinRz*-sinRy + sinRx*cosRy) * MyBunshinBase::VELO_BUNSHIN_FREE_MV );
            } else if (pPhase->getFrame() > 3*(bunshin_no_-1)) { //ばらつかせ
                pCoordVehicle->setAcceXYZ( (tx - (_x + pCoordVehicle->_velo_x*6)),
                                          (ty - (_y + pCoordVehicle->_velo_y*6)),
                                         (tz - (_z + pCoordVehicle->_velo_z*6)) );
            }
            if (ABS(_x - tx) < 10000 &&
                ABS(_y - ty) < 10000 &&
                ABS(_z - tz) < 10000 &&
                ABS(pCoordVehicle->_velo_x) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pCoordVehicle->_velo_y) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV &&
                ABS(pCoordVehicle->_velo_z) <= MyBunshinBase::VELO_BUNSHIN_FREE_MV)
            {
                //もどった！
                pCoordVehicle->setXYZZero();
                pCoordVehicle->setAcceXYZZero();
                setPosition(tx, ty, tz);
                moving_frames_since_default_pos_ = 0;
                pPhase->change(PHASE_BUNSHIN_NOMAL_TRACE);
            }
            break;
        }

        default :
            break;
    }

    //オプションフリーモードへの判断
    if (is_pressed_VV_VB_OPTION) {
        if (pVbPlay->isDoublePushedDown(0, VV_VB_TURBO)) { //VV_VB_OPTION + VV_VB_TURBOダブルプッシュ
            //分身フリーモード、点火！
            pPhase->change(PHASE_BUNSHIN_FREE_MODE_IGNITED);
        }
    }

    if (pVbPlay->isDoublePushedDown(0, VV_VB_OPTION, 8, 8)) {
        if (is_pressed_VV_VB_TURBO) {
            //VV_VB_OPTION ダブルプッシュ + VV_VB_TURBO押しっぱなしの場合
            //ハーフセット
            //フリーモード維持、半径位置も維持、
            resetBunshin(1);
        } else {
            //VV_VB_OPTION ダブルプッシュ、VV_VB_TURBOを押していないと、
            //オールリセット
            resetBunshin(0);
        }
    } else if (is_pressed_VV_VB_OPTION) {
        //分身操作
        if (is_pressed_VV_VB_TURBO) {
            trace_mode_ = TRACE_FREEZE;
            dir26 mv_way_sgn_x_MyShip = pMyShip->mv_way_sgn_x_;
            dir26 mv_way_sgn_y_MyShip = pMyShip->mv_way_sgn_y_;
            dir26 mv_way_sgn_z_MyShip = pMyShip->mv_way_sgn_z_;
            //分身広がり
            if (mv_way_sgn_x_MyShip == 1) {
                pMyBunshinController_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
            } else if (mv_way_sgn_x_MyShip == -1) {
                pMyBunshinController_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
            } else {
                if (mv_way_sgn_z_MyShip == 1) {
                    pMyBunshinController_->addExpanse(+MyBunshinBase::ANGVELO_EXPANSE);
                } else if (mv_way_sgn_z_MyShip == -1) {
                    pMyBunshinController_->addExpanse(-MyBunshinBase::ANGVELO_EXPANSE);
                }
            }
            //半径位置制御
            if (mv_way_sgn_y_MyShip == 1) {
                pMyBunshinController_->addRadiusPosition(+bunshin_velo_mv_radius_pos_);
            } else if (mv_way_sgn_y_MyShip == -1) {
                pMyBunshinController_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
            }
            bunshin_radius_pos_ = pMyBunshinController_->getRadiusPosition(); //標準半径位置を更新
        } else {  //if ( pVbPlay->isPressed(0, VV_VB_TURBO) )  の else
            //分身の向き(this土台の向き)操作
            trace_mode_ = TRACE_FREEZE;
            //カメラ位置によって上下左右の操作割当を変える
            const dir26 pos_up = pVAM->getPosUp();
            const double vX = pLocoVehicle->_vX;
            const double vY = pLocoVehicle->_vY;
            const double vZ = pLocoVehicle->_vZ;
            bool update_updown_rot_axis_timing = (pLocoVehicle->isTurningMvAng() || pVbPlay->isPushedDown(0, VV_VB_OPTION) || pVAM->isJustChangedPosCam());

            //LEFT RIGHT 回転軸 = pos_up = (up_sgn_x, up_sgn_y, up_sgn_z)
            double up_vx, up_vy, up_vz;
            Direction26Util::cnvDirNo2Vec(pos_up, up_vx, up_vy, up_vz);
            //b = (vX, vY, vZ)
            //a×b = (up_sgn_y*vZ-up_sgn_z*vY, up_sgn_z*vX-up_sgn_x*vZ, up_sgn_x*vY-up_sgn_y*vX)
            //※ (a1,a2,a3)×(b1,b2,b3)=(a2*b3-a3*b2, a3*b1-a1*b3, a1*b2-a2*b1)
            if (update_updown_rot_axis_timing) {
                // UP DOWN 回転軸
                double c_vx = up_vy*vZ-up_vz*vY;
                double c_vy = up_vz*vX-up_vx*vZ;
                double c_vz = up_vx*vY-up_vy*vX;
                if ( !(ZEROd_EQ(c_vx) && ZEROd_EQ(c_vy) && ZEROd_EQ(c_vz)) ) {
                    UTIL::getNormalizedVector(c_vx, c_vy, c_vz,
                                              c_ax_x_, c_ax_y_, c_ax_z_);
                }
            }
            if (pos_up == VAM_POS_UP) {
                //高速
                if (pVbPlay->isPressed(0, VV_VB_LEFT)) {
                    pLocoVehicle->addRyMvAng(-MyBunshinBase::ANGVELO_TURN);
                } else if (pVbPlay->isPressed(0, VV_VB_RIGHT)) {
                    pLocoVehicle->addRyMvAng(MyBunshinBase::ANGVELO_TURN);
                }
                if (pVbPlay->isPressed(0, VV_VB_UP)) {
                    pLocoVehicle->addRzMvAng(MyBunshinBase::ANGVELO_TURN);
                } else if (pVbPlay->isPressed(0, VV_VB_DOWN)) {
                    pLocoVehicle->addRzMvAng(-MyBunshinBase::ANGVELO_TURN);
                }

//TODO:上以外も斜めでなければ高速でいけるのでは？
            } else {
                //重いが仕方ない
                if (pVbPlay->isPressed(0, VV_VB_LEFT)) {
                    addTurnAngleAroundAx2( up_vx,  up_vy,  up_vz);
                } else if (pVbPlay->isPressed(0, VV_VB_RIGHT)) {
                    addTurnAngleAroundAx2(-up_vx, -up_vy, -up_vz);
                }
                if (pVbPlay->isPressed(0, VV_VB_UP)) {
                    addTurnAngleAroundAx1( c_ax_x_,  c_ax_y_,  c_ax_z_);
                } else if (pVbPlay->isPressed(0, VV_VB_DOWN)) {
                    addTurnAngleAroundAx1(-c_ax_x_, -c_ax_y_, -c_ax_z_);
                }
            }

        }
    }

    if (return_default_pos_frames_ > 0) {
        //分身が元の位置に戻る継続中
        trace_mode_ = TRACE_TWINBEE; //戻ってる最中はツインビートレース
        return_default_pos_frames_ --;
    }

    if (trace_mode_ == TRACE_GRADIUS) {
        if (pMyShip->is_move_) {
            pPosTrace_->next()->set(pMyShip);
        }
    } else if (trace_mode_ == TRACE_TWINBEE) {
        pPosTrace_->next()->set(pMyShip);
    } else if (trace_mode_ == TRACE_FREEZE) {
        if (pMyShip->is_move_) {
            int l = pPosTrace_->_num;
            coord dx = pMyShip->mv_offset_x_;
            coord dy = pMyShip->mv_offset_y_;
            coord dz = pMyShip->mv_offset_z_;
            Pos* p = pPosTrace_->_paPos;
            for (int i = 0; i < l; i++) {
                p[i].add(dx, dy, dz);
            }
        }
    }

    if (is_free_mode_) {
        //フリーモード中はフリーズの動き
        if (pMyShip->is_move_) {
            setPosition(_x + pMyShip->mv_offset_x_,
                        _y + pMyShip->mv_offset_y_,
                        _z + pMyShip->mv_offset_z_ );
        }
    } else {
        //通常時は trace_mode_ の動き
        setPosAt(pPosTrace_->getNext()); //環状なのでgetNext()が末尾座標情報。
        if (trace_mode_ == TRACE_GRADIUS) {
            //TRACE_GRADIUS で 土台が移動するならば、半径位置を土台の中心に寄せる
            Pos* p = pPosTrace_->get2Next();
            if (!(p->x == _x && p->y == _y && p->z == _z)) {
                pMyBunshinController_->addRadiusPosition(-bunshin_velo_mv_radius_pos_);
            }
        }
    }

    pLocoVehicle->behave();
    pCoordVehicle->behave();
}

void MyBunshinBase::resetBunshin(int prm_mode) {
    //prm_mode = 0 オールリセット
    //prm_mode = 1 ハーフリセット

    EffectTurbo002* pTurbo002 = CommonScene_dispatch(EffectTurbo002);
    if (pTurbo002) {
        pTurbo002->setPositionAt(pMyBunshinController_);
    }

    is_isolate_mode_ = false;
    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    GgafCore::Phase* pPhase = getPhase();
    //完全にデフォルト状態に元に戻ために、最低限必要なフレーム数基準値
    return_default_pos_frames_ = MyBunshinBase::BUNSHIN_D * (MAX_BUNSHIN_NUM+1); //少しばらつかせる演出
    //エフェクト

    //土台がの向きが元に戻る（前方に向く）指示
    pLocoVehicle->asstMvAng()->turnRzRyByDtTo(D0ANG, D0ANG,
                                             TURN_CLOSE_TO,
                                             false,
                                             return_default_pos_frames_ * delay_r_,
                                             0.3, 0.5,
                                             0,
                                             true);
    //分身の向きが元に戻る（前方に向く）指示
    pMyBunshinController_->turnExpanse(
                   D_ANG(0),
                   return_default_pos_frames_ * delay_r_
               );
    //分身の角度位置が元に戻る指示
    pLocoVehicle->asstFaceAng()->rollFaceAngByDtTo(
                          bunshin_default_ang_pos_,
                          SGN(bunshin_default_angvelo_mv_) > 0 ? TURN_COUNTERCLOCKWISE : TURN_CLOCKWISE,
                          return_default_pos_frames_/2, //ばらつかせるとズレるので  * delay_r_ しません
                          0.3, 0.5,
                          bunshin_default_angvelo_mv_,
                          true
                       );
    if (prm_mode == 0) {
        //VV_VB_OPTION ダブルプッシュ + VV_VB_TURBO押しっぱなしの場合
        //オールリセット
        //分身の半径位置が元に戻る指示
        bunshin_radius_pos_ = bunshin_default_radius_pos_;
        pMyBunshinController_->slideMvRadiusPosition(bunshin_radius_pos_, return_default_pos_frames_ * delay_r_ );
        //後はreturn_default_pos_frames_ が0になるまで
        //trace_mode_ = TRACE_TWINBEE;
        //が行われる
        pPhase->change(PHASE_BUNSHIN_FREE_MODE_BACK_TO_DEFAULT_POS); //分身の位置が元に戻るフェーズへ移行
    } else {
        //VV_VB_OPTION ダブルプッシュ、VV_VB_TURBOを押していないと、
        //チョットリセット
        //フリーモード維持、半径位置も維持、
        return_default_pos_frames_ = 0;
    }
}
void MyBunshinBase::addTurnAngleAroundAx1(double prm_ax_x, double prm_ax_y, double prm_ax_z) {
    //ある座標(x, y, z)において、回転の軸が v=(α, β, γ) (但し|v|=1) で、θ回す回転をしたい場合。
    //P = (0; x, y, z)
    //Q = (cos(θ/2); α sin(θ/2), β sin(θ/2), γ sin(θ/2))
    //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
    //として、次を計算する。
    //R P Q = (0; x2, y2, z2)
    //θ回転した後の座標は (x2, y2, z2)
    static const double p_sin_h = ANG_SIN(MyBunshinBase::ANGVELO_TURN/2);  //ANGVELO_TURN=回転させたい角度
    static const double p_cos_h = ANG_COS(MyBunshinBase::ANGVELO_TURN/2);

    double a = prm_ax_x*p_sin_h;
    double b = prm_ax_y*p_sin_h;
    double c = prm_ax_z*p_sin_h;

    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    Quaternion H(p_cos_h, -a, -b, -c); //R
    H.mul(0, pLocoVehicle->_vX, pLocoVehicle->_vY, pLocoVehicle->_vZ); //R*P
    H.mul(p_cos_h, a, b, c);                               //R*P*Q
    pLocoVehicle->setRzRyMvAng(H.i, H.j, H.k, false);
}

void MyBunshinBase::addTurnAngleAroundAx2(double prm_ax_x, double prm_ax_y, double prm_ax_z) {
    static const double p_sin_h = ANG_SIN(MyBunshinBase::ANGVELO_TURN/2);  //ANGVELO_TURN=回転させたい角度
    static const double p_cos_h = ANG_COS(MyBunshinBase::ANGVELO_TURN/2);

    double a = prm_ax_x*p_sin_h;
    double b = prm_ax_y*p_sin_h;
    double c = prm_ax_z*p_sin_h;

    GgafDx::LocoVehicle* pLocoVehicle = getLocoVehicle();
    Quaternion H(p_cos_h, -a, -b, -c); //R
    Quaternion H2 = H;
    H.mul(0, pLocoVehicle->_vX, pLocoVehicle->_vY, pLocoVehicle->_vZ); //R*P
    H.mul(p_cos_h, a, b, c);                               //R*P*Q
    pLocoVehicle->setRzRyMvAng(H.i, H.j, H.k, false);

    //上下入力時の回転軸も回転させる
    H2.mul(0, c_ax_x_, c_ax_y_, c_ax_z_); //R*P
    H2.mul(p_cos_h, a, b, c);             //R*P*Q
    c_ax_x_ = H2.i;
    c_ax_y_ = H2.j;
    c_ax_z_ = H2.k;
}

MyBunshinBase::~MyBunshinBase() {
    GGAF_DELETE(pPosTrace_);
}

void MyBunshinBase::setBunshinNum(int prm_num) {
    MyBunshinBase::now_bunshin_num_ = prm_num;
    MyBunshinBase** papBase = pMYSHIP_SCENE->papBunshinBase_;
    for (int i = 0; i < MAX_BUNSHIN_NUM; i++) {
        MyBunshinBase* p = papBase[i];
        if (i+1 <= prm_num) {
            //活動して無い場合活動させる。活動中だったら何もしない。
            if (!(p->isActive())) {
                p->activate();
            }
        } else {
            //引数を超える分身は非活動
            if (p->isActive()) {
                p->inactivate();
            }
        }
    }

    const angvelo INNER_ROT = D_ANG(1);   //分身がぐるぐる旋回している速度
    const angvelo OUTER_ROT = -D_ANG(1);
    const coord INNER_RADIUS = PX_C(50);  //内側分身の中心からの距離
    const coord OUTER_RADIUS = PX_C(120); //外側分身の中心からの距離
    switch (MyBunshinBase::now_bunshin_num_) {
        case 1: {
            papBase[0]->config(INNER_RADIUS, D0ANG, 0, INNER_ROT);
            break;
        }
        case 2: {
            papBase[0]->config(INNER_RADIUS, D0ANG  , 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D180ANG, 0, INNER_ROT);
            break;
        }
        case 3: {
            papBase[0]->config(INNER_RADIUS, D_ANG(120*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(120*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(120*2), 0, INNER_ROT);
            break;
        }
        case 4: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            break;
        }
        case 5: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D0ANG, 0, OUTER_ROT);
            break;
        }
        case 6: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D0ANG  , 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D180ANG, 0, OUTER_ROT);
            break;
        }
        case 7: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(120* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(120*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(120*-2), 0, OUTER_ROT);
            break;
        }
        case 8: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(90* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(90*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(90*-2), 0, OUTER_ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(90*-3), 0, OUTER_ROT);
            break;
        }
        case 9: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(72* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(72*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(72*-2), 0, OUTER_ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(72*-3), 0, OUTER_ROT);
            papBase[8]->config(OUTER_RADIUS, D_ANG(72*-4), 0, OUTER_ROT);
            break;
        }
        case 10: {
            papBase[0]->config(INNER_RADIUS, D_ANG(90*0), 0, INNER_ROT);
            papBase[1]->config(INNER_RADIUS, D_ANG(90*1), 0, INNER_ROT);
            papBase[2]->config(INNER_RADIUS, D_ANG(90*2), 0, INNER_ROT);
            papBase[3]->config(INNER_RADIUS, D_ANG(90*3), 0, INNER_ROT);
            papBase[4]->config(OUTER_RADIUS, D_ANG(60* 0), 0, OUTER_ROT);
            papBase[5]->config(OUTER_RADIUS, D_ANG(60*-1), 0, OUTER_ROT);
            papBase[6]->config(OUTER_RADIUS, D_ANG(60*-2), 0, OUTER_ROT);
            papBase[7]->config(OUTER_RADIUS, D_ANG(60*-3), 0, OUTER_ROT);
            papBase[8]->config(OUTER_RADIUS, D_ANG(60*-4), 0, OUTER_ROT);
            papBase[9]->config(OUTER_RADIUS, D_ANG(60*-5), 0, OUTER_ROT);
            break;
        }
        default :
            break;
    }
}


