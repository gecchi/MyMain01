#include "PauseCamWorker.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/ViewPointGuide.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "jp/gecchi/VioletVreath/actor/camera/CameraViewPoint.h"
#include "jp/gecchi/VioletVreath/actor/camera/Camera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoAssistantA.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

PauseCamWorker::PauseCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "PauseCamWorker";
    cd_ = 0;
    mdz_flg_ = false;
    pVPGuide_ = nullptr;
    mdz_vx_ = mdz_vy_ = mdz_vz_ = mdz_t_ = 0.0;
    pVPGuide_ = createInFactory(ViewPointGuide, "VPGuide");
}

void PauseCamWorker::initialize() {
    CameraWorker::initialize();
    pVPGuide_->inactivate();
    P_GOD->getUniverse()->getWorld()->getSceneDirector()->addSubGroup(pVPGuide_);
}

void PauseCamWorker::onActive() {
    _TRACE_("PauseCamWorker::onActive()");
    CameraWorker::onActive();
    //CameraWorker::onActive(); を上書きして、
    //その場座標をターゲット座標に上書き
    slideMvCamTo(pCam_->_x, pCam_->_y, pCam_->_z, 60);
    slideMvVpTo(pVp_->_x, pVp_->_y, pVp_->_z, 60);
}

void PauseCamWorker::processBehavior() {
    //TODO:精度を上げるアイディア
    //マウスポイントの履歴を取り、mdx,mdy,mdzは、３フレームほど過去との差にすると回転軸が安定するだろう

    long mx,my,mz,mdx,mdy,mdz;
    GgafDxInput::getMousePointer(&mx, &my, &mz);
    GgafDxInput::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Yはインバーズ

//    if (GgafDxInput::isPushedDownMouseButton(0) || GgafDxInput::isPushedDownMouseButton(1) || GgafDxInput::isPushedDownMouseButton(2)) {
//        pVPGuide_->activate(); //ガイドON
//    } else if(GgafDxInput::isReleasedUpMouseButton(0) || GgafDxInput::isReleasedUpMouseButton(1) || GgafDxInput::isReleasedUpMouseButton(2)) {
//        pVPGuide_->inactivate(); //ガイドOFF
//    }

    if (GgafDxInput::isPushedDownMouseButton(0) || GgafDxInput::isPushedDownMouseButton(1) || GgafDxInput::isPushedDownMouseButton(2)) {
        RECT cRect; // クライアント領域の矩形
        int cw, ch; // クライアント領域の幅、高さ
        // クライアント領域の幅・高さを計算
        GetClientRect(GgafDxGod::_pHWndPrimary, &cRect);
        cw = cRect.right - cRect.left;
        ch = cRect.bottom - cRect.top;
        if (cw > ch) {
            cd_ = ch;
        } else {
            cd_ = cw;
        }
    }

    if ( !(GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1)) &&
         (GgafDxInput::isBeingPressedMouseButton(0) || GgafDxInput::isBeingPressedMouseButton(1) || GgafDxInput::isBeingPressedMouseButton(2))
    ) {
        //視点を中心にカメラが回転移動
        //カメラを中心に視点が回転移動
        //カメラをと視点が平行移動
        //共通の計算

        //ワールド回転軸方向ベクトル、(vX_axis, vY_axis, vZ_axis) を計算 begin =======>

        //平面回転軸(vx,vy)を求める
        //double a = asin(1.0*dx/dy); //a XY平面のなす角 90度回転 x→y y→-x
        double vx = mdy;
        double vy = -mdx;
        double vz = 0;
        double d = sqrt(vx * vx + vy * vy); //ポインタ移動ピクセル距離

        double t = 1.0 / d;
        vx = t * vx;
        vy = t * vy;
        vz = 0;
        //平面回転軸(vx,vy)をVPのワールド空間軸に変換
        //VP→CAMのワールド空間方向ベクトルを法線とする平面上に回転軸ベクトルは存在する

        D3DXMATRIX InvView;
        D3DXMatrixInverse( &InvView, nullptr, pCam_->getViewMatrix());
        //(vx,vy,vz) * InvView
        // 11_, 12_, 13_, 14_
        // 21_, 22_, 23_, 24_
        // 31_, 32_, 33_, 34_
        // vx*11_ + vy*21_ + vz*31_ + 41_, vx*12_ + vy*22_ + vz*32_ + 42_, vx*13_ + vy*23_ + vz*33_ + 43_, vx*14_ + vy*24_ + vz*34_ + 44_
        //方向ベクトル(0,0,0)->(vx,vy,vz) を逆ビュー変換
        //変換後方向ベクトル = (vx,vy,vz)変換後座標 - (0,0,0)変換後座標
        //               <------------  (vx,vy,vz)変換後座標-------------------------->    <-- (0,0,0)変換後座標 -->
        double vX_axis = vx*InvView._11 + vy*InvView._21 + vz*InvView._31 + InvView._41  -    InvView._41;
        double vY_axis = vx*InvView._12 + vy*InvView._22 + vz*InvView._32 + InvView._42  -    InvView._42;
        double vZ_axis = vx*InvView._13 + vy*InvView._23 + vz*InvView._33 + InvView._43  -    InvView._43;
        //正規化
        double d2 = sqrt(vX_axis * vX_axis + vY_axis * vY_axis + vZ_axis * vZ_axis);
        double t2 = 1.0 / d2;
        vX_axis = t2 * vX_axis;
        vY_axis = t2 * vY_axis;
        vZ_axis = t2 * vZ_axis;
        //<==========  ワールド回転軸方向ベクトル、(vX_axis, vY_axis, vZ_axis) を計算 end

        //ある座標(x, y, z)において、回転の軸が(α, β, γ)で、θ回す回転
        //P = (0; x, y, z)
        //Q = (cos(θ/2); α sin(θ/2), β sin(θ/2), γ sin(θ/2))
        //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
        //R P Q = (0; 答え)
        //(α, β, γ) = (vX_axis,vY_axis,vY_axis);
        //(x, y, z) は CAM か VP

        //視点を中心にカメラが回転移動
        if (GgafDxInput::isBeingPressedMouseButton(0) && (mdx != 0 || mdy != 0)) {
            //視点→カメラ の方向ベクトル(x,y,z)
            double x = t_x_CAM_ - t_x_VP_;
            double y = t_y_CAM_ - t_y_VP_;
            double z = t_z_CAM_ - t_z_VP_;

            //回転させたい角度
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            slideMvCamTo(Q._x + t_x_VP_, Q._y + t_y_VP_, Q._z + t_z_VP_, 60);
        }
        //カメラを中心に視点が回転移動
        if (GgafDxInput::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            //カメラ→視点 の方向ベクトル(x,y,z)
            double x = t_x_VP_ - t_x_CAM_;
            double y = t_y_VP_ - t_y_CAM_;
            double z = t_z_VP_ - t_z_CAM_;
            //回転させたい角度
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            slideMvVpTo(Q._x + t_x_CAM_, Q._y + t_y_CAM_, Q._z + t_z_CAM_, 60);
        }
        //カメラをと視点が平行移動
        if (GgafDxInput::isBeingPressedMouseButton(2) && (mdx != 0 || mdy != 0)) {
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //回転させたい角度
            double cosHalf = cos(ang/2);
            double x = t_x_VP_ - t_x_CAM_;
            double y = t_y_VP_ - t_y_CAM_;
            double z = t_z_VP_ - t_z_CAM_;
            //正規化
            double d3 = sqrt(x * x + y * y + z * z);
            double t3 = 1.0 / d3;
            x = t3 * x;
            y = t3 * y;
            z = t3 * z;

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            double r = ((d/cd_) * PX_C(PROPERTY::GAME_BUFFER_WIDTH*2));
            slideMvCamTo(t_x_CAM_ + (Q._x*r),
                         t_y_CAM_ + (Q._y*r),
                         t_z_CAM_ + (Q._z*r) , 60);
            slideMvVpTo(t_x_VP_ + (Q._x*r),
                        t_y_VP_ + (Q._y*r),
                        t_z_VP_ + (Q._z*r) , 60);
        }

    } else if (mdz != 0 || (GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
        if (mdz_flg_ == false) {
            //ホイールした（両方押し）最初のフレーム
            mdz_total_ = 0;
            //カメラ → 視点 の方向ベクトル
            double vx = pVp_->_x - pCam_->_x;
            double vy = pVp_->_y - pCam_->_y;
            double vz = pVp_->_z - pCam_->_z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            mdz_vx_ = t * vx;
            mdz_vy_ = t * vy;
            mdz_vz_ = t * vz;
        }
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
            r = ((1.0*mdy/cd_) * PROPERTY::GAME_BUFFER_WIDTH*2)*LEN_UNIT;
        }
        if (mdx != 0 || mdy != 0 || mdz != 0) {
            slideMvCamTo(t_x_CAM_ + mdz_vx_*r,
                         t_y_CAM_ + mdz_vy_*r,
                         t_z_CAM_ + mdz_vz_*r , 60);
            slideMvVpTo(t_x_VP_ + mdz_vx_*r,
                        t_y_VP_ + mdz_vy_*r,
                        t_z_VP_ + mdz_vz_*r , 60);
        }
        mdz_flg_ = true;
    } else {
        mdz_flg_ = false;
    }

    CameraWorker::processBehavior();
}

PauseCamWorker::~PauseCamWorker() {
}
