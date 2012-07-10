#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;

VvvCamWorker::VvvCamWorker(const char* prm_name) : DefaultGeometricActor(prm_name) {
    _class_name = "VvvCamWorker";
    cd_ = 0;
    mdz_flg_ = false;
    mdz_vx_ = mdz_vy_ = mdz_vz_ = mdz_t_ = 0.0;
    move_target_XY_CAM_UP_ = D90ANG;
    angXY_nowCamUp_ = D90ANG;
    stop_renge_ = 60000;
    move_target_X_CAM_ = 0;
    move_target_Y_CAM_ = 0;
    move_target_Z_CAM_ = 0;
    move_target_X_VP_ =  0;
    move_target_Y_VP_ =  0;
    move_target_Z_VP_ =  0;

    X_CAM_clicked_ = 0;
    Y_CAM_clicked_ = 0;
    Z_CAM_clicked_ = 0;
    X_VP_clicked_ = 0;
    Y_VP_clicked_ = 0;
    Z_VP_clicked_ = 0;
    XY_CAM_UP_clicked_ = D90ANG;
    mx_clicked_ = my_clicked_ = mz_clicked_ = 0;
}

void VvvCamWorker::initialize() {
    GgafDxCamera* pCam = P_CAM;
    move_target_X_CAM_ = pCam->_X;
    move_target_Y_CAM_ = pCam->_Y;
    move_target_Z_CAM_ = pCam->_Z;
    GgafDxInput::updateMouseState();
    GgafDxInput::updateMouseState();
}

void VvvCamWorker::processBehavior() {

    GgafDxCamera* pCam = P_CAM;
    GgafDxGeometricActor* pVP = P_CAM->_pViewPoint;
    GgafDxInput::updateMouseState();

    long mx,my,mz,mdx,mdy,mdz;
    GgafDxInput::getMousePointer(&mx, &my, &mz);
    GgafDxInput::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Yはインバーズ

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
        if (!pCam->_pKurokoA->isRunnigSmoothMvSequence()) {
            move_target_X_CAM_ = pCam->_X;
            move_target_Y_CAM_ = pCam->_Y;
            move_target_Z_CAM_ = pCam->_Z;
        }
        if (!pVP->_pKurokoA->isRunnigSmoothMvSequence()) {
            //正確なVPに再設定
            pVP->_X = DX_C(pCam->_pVecCamLookatPoint->x);
            pVP->_Y = DX_C(pCam->_pVecCamLookatPoint->y);
            pVP->_Z = DX_C(pCam->_pVecCamLookatPoint->z);
            move_target_X_VP_ = pVP->_X;
            move_target_Y_VP_ = pVP->_Y;
            move_target_Z_VP_ = pVP->_Z;
        }

        mx_clicked_ = mx;
        my_clicked_ = my;
        mz_clicked_ = mz;
        X_CAM_clicked_ = pCam->_X;
        Y_CAM_clicked_ = pCam->_Y;
        Z_CAM_clicked_ = pCam->_Z;
        X_VP_clicked_ = pVP->_X;
        Y_VP_clicked_ = pVP->_Y;
        Z_VP_clicked_ = pVP->_Z;
        XY_CAM_UP_clicked_ = angXY_nowCamUp_;
        D3DXMatrixInverse( &InvView_clicked_, NULL, &pCam->_matView);
    }

    if ( (mdy != 0 || mdx != 0) &&
         !(GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1)) &&
         (GgafDxInput::isBeingPressedMouseButton(0) || GgafDxInput::isBeingPressedMouseButton(1) || GgafDxInput::isBeingPressedMouseButton(2))
    ) {

        //視点を中心にカメラが回転移動
        //カメラを中心に視点が回転移動
        //カメラをと視点が平行移動
        //共通の計算

        //ワールド回転軸方向ベクトル、(vX_axis, vY_axis, vZ_axis) を計算 begin =======>

        //平面回転軸(vx,vy)を求める
        //double a = asin(1.0*dx/dy); //a XY平面のなす角 90度回転 x→y y→-x
        _TRACE_("移動量("<<mdx<<","<<mdy<<")");
        double vx = (my - my_clicked_);
        double vy = -(mx - mx_clicked_);
        double vz = 0;
        double d = sqrt(vx * vx + vy * vy); //ポインタ移動ピクセル距離
        _TRACE_("移動距離d="<<d<<"");
        double t = 1.0 / d;
        vx = ABS(t * vx);
        vy = ABS(t * vy);
        vz = 0;
        _TRACE_("平面回転軸("<<vx<<","<<vy<<")");

        //平面回転軸(vx,vy)をVPのワールド空間軸に変換
        //VP→CAMのワールド空間方向ベクトルを法線とする平面上に回転軸ベクトルは存在する

//        D3DXMATRIX InvView;
//        D3DXMatrixInverse( &InvView, NULL, &pCam->_matView);
        //(vx,vy,vz) * InvView
        // 11_, 12_, 13_, 14_
        // 21_, 22_, 23_, 24_
        // 31_, 32_, 33_, 34_
        // vx*11_ + vy*21_ + vz*31_ + 41_, vx*12_ + vy*22_ + vz*32_ + 42_, vx*13_ + vy*23_ + vz*33_ + 43_, vx*14_ + vy*24_ + vz*34_ + 44_
        //方向ベクトル(0,0,0)->(vx,vy,vz) を逆ビュー変換
        //変換後方向ベクトル = (vx,vy,vz)変換後座標 - (0,0,0)変換後座標
        //               <------------  (vx,vy,vz)変換後座標-------------------------->    <-- (0,0,0)変換後座標 -->
        double vX_axis = vx*InvView_clicked_._11 + vy*InvView_clicked_._21 + vz*InvView_clicked_._31 + InvView_clicked_._41  -    InvView_clicked_._41;
        double vY_axis = vx*InvView_clicked_._12 + vy*InvView_clicked_._22 + vz*InvView_clicked_._32 + InvView_clicked_._42  -    InvView_clicked_._42;
        double vZ_axis = vx*InvView_clicked_._13 + vy*InvView_clicked_._23 + vz*InvView_clicked_._33 + InvView_clicked_._43  -    InvView_clicked_._43;
        //正規化
        double d2 = sqrt(vX_axis * vX_axis + vY_axis * vY_axis + vZ_axis * vZ_axis);
        double t2 = 1.0 / d2;
        vX_axis = t2 * vX_axis;
        vY_axis = t2 * vY_axis;
        vZ_axis = t2 * vZ_axis;
        _TRACE_("回転軸("<<vX_axis<<","<<vY_axis<<","<<vZ_axis<<")");
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
            //クリック時視点→カメラ の方向ベクトル(x,y,z)
            double x = X_CAM_clicked_ - X_VP_clicked_;
            double y = Y_CAM_clicked_ - Y_VP_clicked_;
            double z = Z_CAM_clicked_ - Z_VP_clicked_;

            angle rz1 = UTIL::getAngle2D(x, y);

            //回転させたい角度
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = UTIL::getAngle2D(Q._x,Q._y);

            //Q.x_, Q.y_, Q.z_ が回転後の座標となる
            if (ABS(mdy) > ABS(mdx)/2) { //上下ブレ補正
                move_target_XY_CAM_UP_ = XY_CAM_UP_clicked_ + UTIL::getAngDiff(rz1, rz2);
                move_target_XY_CAM_UP_ = UTIL::simplifyAng(move_target_XY_CAM_UP_);
            }
            move_target_X_CAM_ = Q._x + X_VP_clicked_;
            move_target_Y_CAM_ = Q._y + Y_VP_clicked_;
            move_target_Z_CAM_ = Q._z + Z_VP_clicked_;
        }
        //カメラを中心に視点が回転移動
        if (GgafDxInput::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            //カメラ→視点 の方向ベクトル(x,y,z)
            double x = X_VP_clicked_ - X_CAM_clicked_;
            double y = Y_VP_clicked_ - Y_CAM_clicked_;
            double z = Z_VP_clicked_ - Z_CAM_clicked_;
            angle rz1 = UTIL::getAngle2D(x, y);
            //回転させたい角度
            double ang = (PI) * (d/cd_);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = UTIL::getAngle2D(Q._x,Q._y);
            if (ABS(mdy) > ABS(mdx)/2) { //上下ブレ補正
                move_target_XY_CAM_UP_ = XY_CAM_UP_clicked_ + UTIL::getAngDiff(rz1, rz2);
                move_target_XY_CAM_UP_ = UTIL::simplifyAng(move_target_XY_CAM_UP_);
            }
            //Q.x_, Q.y_, Q.z_ が回転後の座標となる
            move_target_X_VP_ = Q._x + X_CAM_clicked_;
            move_target_Y_VP_ = Q._y + Y_CAM_clicked_;
            move_target_Z_VP_ = Q._z + Z_CAM_clicked_;
        }
        //カメラをと視点が平行移動
        if (GgafDxInput::isBeingPressedMouseButton(2) && (mdx != 0 || mdy != 0)) {
            stop_renge_ = 60000;
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //回転させたい角度
            double cosHalf = cos(ang/2);

            double x = move_target_X_VP_ - move_target_X_CAM_;
            double y = move_target_Y_VP_ - move_target_Y_CAM_;
            double z = move_target_Z_VP_ - move_target_Z_CAM_;

            //正規化
            double d3 = sqrt(x * x + y * y + z * z);
            double t3 = 1.0 / d3;
            x = t3 * x;
            y = t3 * y;
            z = t3 * z;

            GgafDxQuaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q

            double r = ((d/cd_) * PX_C(GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2));

            move_target_X_CAM_ += (Q._x*r);
            move_target_Y_CAM_ += (Q._y*r);
            move_target_Z_CAM_ += (Q._z*r);

            move_target_X_VP_ += (Q._x*r);
            move_target_Y_VP_ += (Q._y*r);
            move_target_Z_VP_ += (Q._z*r);
        }

    } else if (mdz != 0 || (GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
        stop_renge_ = 60000;
        if (mdz_flg_ == false) {
            mdz_total_ = 0;
            if (!pCam->_pKurokoA->isRunnigSmoothMvSequence()) {
                move_target_X_CAM_ = pCam->_X;
                move_target_Y_CAM_ = pCam->_Y;
                move_target_Z_CAM_ = pCam->_Z;
            }
            if (!pVP->_pKurokoA->isRunnigSmoothMvSequence()) {
                pVP->_X = DX_C(pCam->_pVecCamLookatPoint->x);
                pVP->_Y = DX_C(pCam->_pVecCamLookatPoint->y);
                pVP->_Z = DX_C(pCam->_pVecCamLookatPoint->z);
                move_target_X_VP_ = pVP->_X;
                move_target_Y_VP_ = pVP->_Y;
                move_target_Z_VP_ = pVP->_Z;
            }
            cam_X_ = pCam->_X;
            cam_Y_ = pCam->_Y;
            cam_Z_ = pCam->_Z;
            vp_X_ = pVP->_X;
            vp_Y_ = pVP->_Y;
            vp_Z_ = pVP->_Z;
            //カメラ → 視点 の方向ベクトル
            double vx = pVP->_X - pCam->_X;
            double vy = pVP->_Y - pCam->_Y;
            double vz = pVP->_Z - pCam->_Z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            mdz_vx_ = t * vx;
            mdz_vy_ = t * vy;
            mdz_vz_ = t * vz;
        }
//        mdz_total_ += mdz; //連続ホイール回転時、加算
//        double r = (mdz_total_*PX_UNIT*LEN_UNIT/10.0);
//        move_target_X_CAM_ = cam_X_ + mdz_vx_*r;
//        move_target_Y_CAM_ = cam_Y_ + mdz_vy_*r;
//        move_target_Z_CAM_ = cam_Z_ + mdz_vz_*r;
//        move_target_X_VP_  = vp_X_ + mdz_vx_*r;
//        move_target_Y_VP_  = vp_Y_ + mdz_vy_*r;
//        move_target_Z_VP_  = vp_Z_ + mdz_vz_*r;
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/20.0); //20.0 を大きくすると、ホイールで進む距離が減る。
        } else if ((GgafDxInput::isBeingPressedMouseButton(0) && GgafDxInput::isBeingPressedMouseButton(1))) {
            r = ((1.0*mdy/cd_) * GGAF_PROPERTY(GAME_BUFFER_WIDTH)*2)*LEN_UNIT;
        }
        move_target_X_CAM_ += mdz_vx_*r;
        move_target_Y_CAM_ += mdz_vy_*r;
        move_target_Z_CAM_ += mdz_vz_*r;
        move_target_X_VP_  += mdz_vx_*r;
        move_target_Y_VP_  += mdz_vy_*r;
        move_target_Z_VP_  += mdz_vz_*r;
        mdz_flg_ = true;
    } else {
        mdz_flg_ = false;
    }

    if (ABS(move_target_X_CAM_ - pCam->_X) < 10 && ABS(move_target_Y_CAM_ - pCam->_Y) < 10 && ABS(move_target_Z_CAM_ - pCam->_Z) < 10) {
        //OK
    } else {
        pCam->_pKurokoA->setMvAng(move_target_X_CAM_, move_target_Y_CAM_, move_target_Z_CAM_);

        int td1 = UTIL::getDistance(pCam->_X, pCam->_Y, pCam->_Z,
                                           move_target_X_CAM_, move_target_Y_CAM_, move_target_Z_CAM_);
        if (ABS(td1) > 10) {
            pCam->_pKurokoA->execSmoothMvSequence(0, td1, 20, 0.4, 0.6);
        }
    }
    if (ABS(move_target_X_VP_ - pVP->_X) < 10 && ABS(move_target_Y_VP_ - pVP->_Y) < 10 && ABS(move_target_Z_VP_ - pVP->_Z) < 10) {
        //OK
    } else {
        pVP->_pKurokoA->setMvAng(move_target_X_VP_, move_target_Y_VP_, move_target_Z_VP_);
        int td2 = UTIL::getDistance(pVP->_X, pVP->_Y, pVP->_Z,
                                           move_target_X_VP_, move_target_Y_VP_, move_target_Z_VP_);
        if (ABS(td2) > 10) {
            pVP->_pKurokoA->execSmoothMvSequence(0, td2, 20, 0.4, 0.6);
        }
    }

    //カメラのUPを計算
    angvelo angvelo_cam_up = 30000 / 20;
    if (angXY_nowCamUp_ != move_target_XY_CAM_UP_) {
        angle da = UTIL::getAngDiff(angXY_nowCamUp_, move_target_XY_CAM_UP_);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            angXY_nowCamUp_ = move_target_XY_CAM_UP_;
        } else {
            angXY_nowCamUp_ += (angvelo_cam_up * SGN(da));
        }
        angXY_nowCamUp_ = UTIL::simplifyAng(angXY_nowCamUp_);
        pCam->_pVecCamUp->x = UTIL::COS[angXY_nowCamUp_ / SANG_RATE];
        pCam->_pVecCamUp->y = UTIL::SIN[angXY_nowCamUp_ / SANG_RATE];
        pCam->_pVecCamUp->z = 0.0f;
    }

    pCam->_pKurokoA->behave();
    pVP->_pKurokoA->behave();

}

VvvCamWorker::~VvvCamWorker() {
}
