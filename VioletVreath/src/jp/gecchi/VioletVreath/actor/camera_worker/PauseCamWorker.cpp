#include "stdafx.h"
#include "PauseCamWorker.h"

#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/util/GgafDxQuaternion.h"
#include "jp/gecchi/VioletVreath/actor/ViewPointGuide.h"
#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "jp/gecchi/VioletVreath/actor/ViewPoint.h"
#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKurokoHelperA.h"

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
//    cam_x_ = cam_y_ = cam_z_ = vp_x_ = vp_y_ = vp_z_ = 0;
//    orderActorToFactory(UTIL::easy_hash("VPGuide"), ViewPointGuide, "VPGuide");
//    pVPGuide_ = (ViewPointGuide*)(obtainActorFromFactory(UTIL::easy_hash("VPGuide")));
    pVPGuide_ = createInFactory(ViewPointGuide, "VPGuide");
}

void PauseCamWorker::initialize() {
    CameraWorker::initialize();
    pVPGuide_->inactivate();
    P_WORLD->getSceneDirector()->addSubGroup(pVPGuide_);
}

void PauseCamWorker::onActive() {
    _TRACE_("PauseCamWorker::onActive()");
    CameraWorker::onActive();
    //その場からの為、 CameraWorker::onActive();上書き
    slideMvCamTo(pCam_->_x, pCam_->_y, pCam_->_z, 60);
    slideMvVpTo(pVp_->_x, pVp_->_y, pVp_->_z, 60);
}
void PauseCamWorker::processBehavior() {
    GgafDxInput::updateMouseState();

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
//        if (!pCam->_pKuroko->hlprA()->isSlidingMv()) {
//            t_x_CAM_ = pCam->_x;
//            t_y_CAM_ = pCam->_y;
//            t_z_CAM_ = pCam->_z;
//        }
//        if (!pVP->_pKuroko->hlprA()->isSlidingMv()) {
//            //正確なVPに再設定
//            pVP->_x = DX_C(pCam->_pVecCamLookatPoint->x);
//            pVP->_y = DX_C(pCam->_pVecCamLookatPoint->y);
//            pVP->_z = DX_C(pCam->_pVecCamLookatPoint->z);
//            t_x_VP_ = pVP->_x;
//            t_y_VP_ = pVP->_y;
//            t_z_VP_ = pVP->_z;
//        }
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
        D3DXMatrixInverse( &InvView, nullptr, &pCam_->_matView);
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

//            angle rz1 = UTIL::getAngle2D(z, y);

            //回転させたい角度
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
//            angle rz2 = UTIL::getAngle2D(Q._z,Q._y);

            //Q.x_, Q.y_, Q.z_ が回転後の座標となる
            //if (ABS(mdy) > ABS(mdx)/2) { //上下ブレ補正
                //ZY平面での、カメラ→視点ベクトルの移動前移動後のベクトルのなす角
//                t_ZY_CAM_UP_ += UTIL::getAngDiff(rz1, rz2);
//                t_ZY_CAM_UP_ = UTIL::simplifyAng(t_ZY_CAM_UP_);
            //}
//            t_x_CAM_ = Q._x + t_x_VP_;
//            t_y_CAM_ = Q._y + t_y_VP_;
//            t_z_CAM_ = Q._z + t_z_VP_;
            slideMvCamTo(Q._x + t_x_VP_, Q._y + t_y_VP_, Q._z + t_z_VP_, 60);

//            //UP
//            pCam->_pVecCamUp->x;
//            GgafDxQuaternion Q2(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
//            Q2.mul(0,pCam->_pVecCamUp->x,
//                     pCam->_pVecCamUp->y,
//                     pCam->_pVecCamUp->z);//R*P
//            Q2.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
//            t_x_up_CAM_ = Q2._x;
//            t_y_up_CAM_ = Q2._y;
//            t_z_up_CAM_ = Q2._z;
        }
        //カメラを中心に視点が回転移動
        if (GgafDxInput::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            //カメラ→視点 の方向ベクトル(x,y,z)
            double x = t_x_VP_ - t_x_CAM_;
            double y = t_y_VP_ - t_y_CAM_;
            double z = t_z_VP_ - t_z_CAM_;
//            angle rz1 = UTIL::getAngle2D(z, y);
            //回転させたい角度
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
//            angle rz2 = UTIL::getAngle2D(Q._z,Q._y);
            //if (ABS(mdy) > ABS(mdx)/2) { //上下ブレ補正
            //ZY平面での、カメラ→視点ベクトルの移動前移動後のベクトルのなす角でUPの回転角とする
//                t_ZY_CAM_UP_ += UTIL::getAngDiff(rz1, rz2);
//                t_ZY_CAM_UP_ = UTIL::simplifyAng(t_ZY_CAM_UP_);
            //}
            //Q.x_, Q.y_, Q.z_ が回転後の座標となる
//            t_x_VP_ = Q._x + t_x_CAM_;
//            t_y_VP_ = Q._y + t_y_CAM_;
//            t_z_VP_ = Q._z + t_z_CAM_;

            slideMvVpTo(Q._x + t_x_CAM_, Q._y + t_y_CAM_, Q._z + t_z_CAM_, 60);

//            pCam->_pVecCamUp->x;
//            GgafDxQuaternion Q2(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
//            Q2.mul(0,pCam->_pVecCamUp->x,
//                     pCam->_pVecCamUp->y,
//                     pCam->_pVecCamUp->z);//R*P
//            Q2.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
//            t_x_up_CAM_ = Q2._x;
//            t_y_up_CAM_ = Q2._y;
//            t_z_up_CAM_ = Q2._z;
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

//            t_x_CAM_ += (Q._x*r);
//            t_y_CAM_ += (Q._y*r);
//            t_z_CAM_ += (Q._z*r);
//
//            t_x_VP_ += (Q._x*r);
//            t_y_VP_ += (Q._y*r);
//            t_z_VP_ += (Q._z*r);


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
//            if (!pCam->_pKuroko->hlprA()->isSlidingMv()) {
//                t_x_CAM_ = pCam->_x;
//                t_y_CAM_ = pCam->_y;
//                t_z_CAM_ = pCam->_z;
//            }
//            if (!pVP->_pKuroko->hlprA()->isSlidingMv()) {
//                pVP->_x = DX_C(pCam->_pVecCamLookatPoint->x);
//                pVP->_y = DX_C(pCam->_pVecCamLookatPoint->y);
//                pVP->_z = DX_C(pCam->_pVecCamLookatPoint->z);
//                t_x_VP_ = pVP->_x;
//                t_y_VP_ = pVP->_y;
//                t_z_VP_ = pVP->_z;
//            }
//            cam_x_ = pCam->_x;
//            cam_y_ = pCam->_y;
//            cam_z_ = pCam->_z;
//            vp_x_ = pVP->_x;
//            vp_y_ = pVP->_y;
//            vp_z_ = pVP->_z;
            //カメラ → 視点 の方向ベクトル
            double vx = pVp_->_x - pCam_->_x;
            double vy = pVp_->_y - pCam_->_y;
            double vz = pVp_->_z - pCam_->_z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            mdz_vx_ = t * vx;
            mdz_vy_ = t * vy;
            mdz_vz_ = t * vz;
        }
//        mdz_total_ += mdz; //連続ホイール回転時、加算
//        double r = (mdz_total_*PX_UNIT*LEN_UNIT/10.0);
//        t_x_CAM_ = cam_x_ + mdz_vx_*r;
//        t_y_CAM_ = cam_y_ + mdz_vy_*r;
//        t_z_CAM_ = cam_z_ + mdz_vz_*r;
//        t_x_VP_  = vp_x_ + mdz_vx_*r;
//        t_y_VP_  = vp_y_ + mdz_vy_*r;
//        t_z_VP_  = vp_z_ + mdz_vz_*r;
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
            r = ((1.0*mdy/cd_) * PROPERTY::GAME_BUFFER_WIDTH*2)*LEN_UNIT;
        }
//        t_x_CAM_ += mdz_vx_*r;
//        t_y_CAM_ += mdz_vy_*r;
//        t_z_CAM_ += mdz_vz_*r;
//        t_x_VP_  += mdz_vx_*r;
//        t_y_VP_  += mdz_vy_*r;
//        t_z_VP_  += mdz_vz_*r;

        if (mdx != 0 || mdy != 0 || mdz != 0) {
            slideMvCamTo(t_x_CAM_ + mdz_vx_*r,
                               t_y_CAM_ + mdz_vy_*r,
                               t_z_CAM_ + mdz_vz_*r , 60);
            slideMvVpTo(t_x_VP_  + mdz_vx_*r,
                                 t_y_VP_  + mdz_vy_*r,
                                 t_z_VP_  + mdz_vz_*r , 60);
        }
        mdz_flg_ = true;
    } else {
        mdz_flg_ = false;
    }

//    if (ABS(t_x_CAM_ - pCam->_x) < 20 && ABS(t_y_CAM_ - pCam->_y) < 20 && ABS(t_z_CAM_ - pCam->_z) < 20) {
//        //OK
//    } else {
//        pCam->_pKuroko->setMvAngTwd(t_x_CAM_, t_y_CAM_, t_z_CAM_);
//        int td1 = UTIL::getDistance(pCam->_x, pCam->_y, pCam->_z,
//                                    t_x_CAM_, t_y_CAM_, t_z_CAM_);
//        if (ABS(td1) > 20  ) {
//            if (pCam->_pKuroko->hlprA()->isSlidingMv() && pCam->_pKuroko->hlprA()->_smthMv._prm._progress == 1) {
//
//            } else {
//                pCam->_pKuroko->hlprA()->slideMvByDt(td1, 20, 0.4, 0.6, 0, true);
//            }
//        }
//    }
//    if (ABS(t_x_VP_ - pVP->_x) < 20 && ABS(t_y_VP_ - pVP->_y) < 20 && ABS(t_z_VP_ - pVP->_z) < 20) {
//        //OK
//    } else {
//        pVP->_pKuroko->setMvAngTwd(t_x_VP_, t_y_VP_, t_z_VP_);
//        int td2 = UTIL::getDistance(pVP->_x, pVP->_y, pVP->_z,
//                                    t_x_VP_, t_y_VP_, t_z_VP_);
//        if (ABS(td2) > 20) {
//            if (pVP->_pKuroko->hlprA()->isSlidingMv() && pVP->_pKuroko->hlprA()->_smthMv._prm._progress == 1) {
//
//            } else {
//                pVP->_pKuroko->hlprA()->slideMvByDt(td2, 20, 0.4, 0.6, 0, true);
//            }
//        }
//    }

//    pCam->_pVecCamUp->x = t_x_up_CAM_;
//    pCam->_pVecCamUp->y = t_y_up_CAM_;
//    pCam->_pVecCamUp->z = t_z_up_CAM_;
//    //カメラのUPを計算
//    angvelo angvelo_cam_up = 30000 / 20;
//    if (angXY_nowCamUp_ != t_ZY_CAM_UP_) {
//        angle da = UTIL::getAngDiff(angXY_nowCamUp_, t_ZY_CAM_UP_);
//        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
//            angXY_nowCamUp_ = t_ZY_CAM_UP_;
//        } else {
//            angXY_nowCamUp_ += (angvelo_cam_up * SGN(da));
//        }
//        angXY_nowCamUp_ = UTIL::simplifyAng(angXY_nowCamUp_);
//        pCam->_pVecCamUp->x = 0.0f;
//        pCam->_pVecCamUp->y = ANG_SIN(angXY_nowCamUp_);
//        pCam->_pVecCamUp->z = ANG_COS(angXY_nowCamUp_);
//    }


    CameraWorker::processBehavior();
}

PauseCamWorker::~PauseCamWorker() {
}
