#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PauseCamWorker::PauseCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "PauseCamWorker";
    _cd = 0;
    _mdz_flg = false;
    _pVPGuide = NULL;
    _mdz_vx = _mdz_vy = _mdz_vz = _mdz_t = 0.0;
    orderActorToFactory(GgafUtil::easy_hash("VPGuide"), ViewPointGuide, "VPGuide");
    _pVPGuide = (ViewPointGuide*)(obtainActorFromFactory(GgafUtil::easy_hash("VPGuide")));

}

void PauseCamWorker::initialize() {
    _pVPGuide->inactivateImmediately();
    P_WORLD->getLordActor()->addSubGroup(_pVPGuide);
}


void PauseCamWorker::processBehavior() {
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9GeometricActor* pVP = P_CAM->_pViewPoint;
    GgafDx9Input::updateMouseState();

    long mx,my,mz,mdx,mdy,mdz;
    GgafDx9Input::getMousePointer(&mx, &my, &mz);
    GgafDx9Input::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Yはインバーズ

//    if (GgafDx9Input::isPushedDownMouseButton(0) || GgafDx9Input::isPushedDownMouseButton(1) || GgafDx9Input::isPushedDownMouseButton(2)) {
//        _pVPGuide->activate(); //ガイドON
//    } else if(GgafDx9Input::isReleasedUpMouseButton(0) || GgafDx9Input::isReleasedUpMouseButton(1) || GgafDx9Input::isReleasedUpMouseButton(2)) {
//        _pVPGuide->inactivate(); //ガイドOFF
//    }

    if (GgafDx9Input::isPushedDownMouseButton(0) || GgafDx9Input::isPushedDownMouseButton(1) || GgafDx9Input::isPushedDownMouseButton(2)) {
        RECT cRect; // クライアント領域の矩形
        int cw, ch; // クライアント領域の幅、高さ
        // クライアント領域の幅・高さを計算
        GetClientRect(GgafDx9God::_pHWndPrimary, &cRect);
        cw = cRect.right - cRect.left;
        ch = cRect.bottom - cRect.top;
        if (cw > ch) {
            _cd = ch;
        } else {
            _cd = cw;
        }
        if (!pCam->_pKurokoA->isMoveingSmooth()) {
            _move_target_X_CAM = pCam->_X;
            _move_target_Y_CAM = pCam->_Y;
            _move_target_Z_CAM = pCam->_Z;
        }
        if (!pVP->_pKurokoA->isMoveingSmooth()) {
            //正確なVPに再設定
            pVP->_X = cnvCoordDx2App(pCam->_pVecCamLookatPoint->x);
            pVP->_Y = cnvCoordDx2App(pCam->_pVecCamLookatPoint->y);
            pVP->_Z = cnvCoordDx2App(pCam->_pVecCamLookatPoint->z);
            _move_target_X_VP = pVP->_X;
            _move_target_Y_VP = pVP->_Y;
            _move_target_Z_VP = pVP->_Z;
        }
    }

    if ( !(GgafDx9Input::isBeingPressedMouseButton(0) && GgafDx9Input::isBeingPressedMouseButton(1)) &&
         (GgafDx9Input::isBeingPressedMouseButton(0) || GgafDx9Input::isBeingPressedMouseButton(1) || GgafDx9Input::isBeingPressedMouseButton(2))
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
        D3DXMatrixInverse( &InvView, NULL, &pCam->_matView );
        //(vx,vy,vz) * InvView
        // _11, _12, _13, _14
        // _21, _22, _23, _24
        // _31, _32, _33, _34
        // vx*_11 + vy*_21 + vz*_31 + _41, vx*_12 + vy*_22 + vz*_32 + _42, vx*_13 + vy*_23 + vz*_33 + _43, vx*_14 + vy*_24 + vz*_34 + _44
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
        if (GgafDx9Input::isBeingPressedMouseButton(0) && (mdx != 0 || mdy != 0)) {
            //視点→カメラ の方向ベクトル(x,y,z)
            double x = _move_target_X_CAM - _move_target_X_VP;
            double y = _move_target_Y_CAM - _move_target_Y_VP;
            double z = _move_target_Z_CAM - _move_target_Z_VP;

            appangle rz1 = GgafDx9Util::getAngle2D(x, y);

            //回転させたい角度
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            appangle rz2 = GgafDx9Util::getAngle2D(Q._x,Q._y);

            //Q._x, Q._y, Q._z が回転後の座標となる
            if (abs(mdy) > abs(mdx)/2) { //上下ブレ補正
                _move_target_XY_CAM_UP += GgafDx9Util::getAngDiff(rz1, rz2);
                _move_target_XY_CAM_UP = GgafDx9Util::simplifyAng(_move_target_XY_CAM_UP);
            }
            _move_target_X_CAM = Q._x + _move_target_X_VP;
            _move_target_Y_CAM = Q._y + _move_target_Y_VP;
            _move_target_Z_CAM = Q._z + _move_target_Z_VP;
        }
        //カメラを中心に視点が回転移動
        if (GgafDx9Input::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            //カメラ→視点 の方向ベクトル(x,y,z)
            double x = _move_target_X_VP - _move_target_X_CAM;
            double y = _move_target_Y_VP - _move_target_Y_CAM;
            double z = _move_target_Z_VP - _move_target_Z_CAM;
            appangle rz1 = GgafDx9Util::getAngle2D(x, y);
            //回転させたい角度
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            appangle rz2 = GgafDx9Util::getAngle2D(Q._x,Q._y);
            if (abs(mdy) > abs(mdx)/2) { //上下ブレ補正
                _move_target_XY_CAM_UP += GgafDx9Util::getAngDiff(rz1, rz2);
                _move_target_XY_CAM_UP = GgafDx9Util::simplifyAng(_move_target_XY_CAM_UP);
            }
            //Q._x, Q._y, Q._z が回転後の座標となる
            _move_target_X_VP = Q._x + _move_target_X_CAM;
            _move_target_Y_VP = Q._y + _move_target_Y_CAM;
            _move_target_Z_VP = Q._z + _move_target_Z_CAM;
        }
        //カメラをと視点が平行移動
        if (GgafDx9Input::isBeingPressedMouseButton(2) && (mdx != 0 || mdy != 0)) {
            _stop_renge = 60000;
            double ang = -PI/2.0;
            double sinHalf = sin(ang/2); //回転させたい角度
            double cosHalf = cos(ang/2);

            double x = _move_target_X_VP - _move_target_X_CAM;
            double y = _move_target_Y_VP - _move_target_Y_CAM;
            double z = _move_target_Z_VP - _move_target_Z_CAM;

            //正規化
            double d3 = sqrt(x * x + y * y + z * z);
            double t3 = 1.0 / d3;
            x = t3 * x;
            y = t3 * y;
            z = t3 * z;

            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q

            double r = ((d/_cd) * cnvCoordPix2App(CFG_PROPERTY(GAME_BUFFER_WIDTH)*2));

            _move_target_X_CAM += (Q._x*r);
            _move_target_Y_CAM += (Q._y*r);
            _move_target_Z_CAM += (Q._z*r);

            _move_target_X_VP += (Q._x*r);
            _move_target_Y_VP += (Q._y*r);
            _move_target_Z_VP += (Q._z*r);
        }

    } else if (mdz != 0 || (GgafDx9Input::isBeingPressedMouseButton(0) && GgafDx9Input::isBeingPressedMouseButton(1))) {
        _stop_renge = 60000;
        if (_mdz_flg == false) {
            _mdz_total = 0;
            if (!pCam->_pKurokoA->isMoveingSmooth()) {
                _move_target_X_CAM = pCam->_X;
                _move_target_Y_CAM = pCam->_Y;
                _move_target_Z_CAM = pCam->_Z;
            }
            if (!pVP->_pKurokoA->isMoveingSmooth()) {
                pVP->_X = cnvCoordDx2App(pCam->_pVecCamLookatPoint->x);
                pVP->_Y = cnvCoordDx2App(pCam->_pVecCamLookatPoint->y);
                pVP->_Z = cnvCoordDx2App(pCam->_pVecCamLookatPoint->z);
                _move_target_X_VP = pVP->_X;
                _move_target_Y_VP = pVP->_Y;
                _move_target_Z_VP = pVP->_Z;
            }
            _cam_X = pCam->_X;
            _cam_Y = pCam->_Y;
            _cam_Z = pCam->_Z;
            _vp_X = pVP->_X;
            _vp_Y = pVP->_Y;
            _vp_Z = pVP->_Z;
            //カメラ → 視点 の方向ベクトル
            double vx = pVP->_X - pCam->_X;
            double vy = pVP->_Y - pCam->_Y;
            double vz = pVP->_Z - pCam->_Z;
            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
            _mdz_vx = t * vx;
            _mdz_vy = t * vy;
            _mdz_vz = t * vz;
        }
//        _mdz_total += mdz; //連続ホイール回転時、加算
//        double r = (_mdz_total*PX_UNIT*LEN_UNIT/10.0);
//        _move_target_X_CAM = _cam_X + _mdz_vx*r;
//        _move_target_Y_CAM = _cam_Y + _mdz_vy*r;
//        _move_target_Z_CAM = _cam_Z + _mdz_vz*r;
//        _move_target_X_VP  = _vp_X + _mdz_vx*r;
//        _move_target_Y_VP  = _vp_Y + _mdz_vy*r;
//        _move_target_Z_VP  = _vp_Z + _mdz_vz*r;
        double r = 0.0;
        if (mdz != 0) {
            r = (mdz*PX_UNIT*LEN_UNIT/10.0);
        } else if ((GgafDx9Input::isBeingPressedMouseButton(0) && GgafDx9Input::isBeingPressedMouseButton(1))) {
            r = ((1.0*mdy/_cd) * CFG_PROPERTY(GAME_BUFFER_WIDTH)*2)*LEN_UNIT;
        }
        _move_target_X_CAM += _mdz_vx*r;
        _move_target_Y_CAM += _mdz_vy*r;
        _move_target_Z_CAM += _mdz_vz*r;
        _move_target_X_VP  += _mdz_vx*r;
        _move_target_Y_VP  += _mdz_vy*r;
        _move_target_Z_VP  += _mdz_vz*r;
        _mdz_flg = true;
    } else {
        _mdz_flg = false;
    }

    if (abs(_move_target_X_CAM - pCam->_X) < 10 && abs(_move_target_Y_CAM - pCam->_Y) < 10 && abs(_move_target_Z_CAM - pCam->_Z) < 10) {
        //OK
    } else {
        pCam->_pKurokoA->setMvAng(_move_target_X_CAM, _move_target_Y_CAM, _move_target_Z_CAM);

        int td1 = GgafDx9Util::getDistance(pCam->_X, pCam->_Y, pCam->_Z,
                                           _move_target_X_CAM, _move_target_Y_CAM, _move_target_Z_CAM);
        if (MyStgUtil::abs(td1) > 10) {
            pCam->_pKurokoA->execSmoothMvVeloSequence(0, td1, 20, 0.4, 0.6);
        }
    }
    if (abs(_move_target_X_VP - pVP->_X) < 10 && abs(_move_target_Y_VP - pVP->_Y) < 10 && abs(_move_target_Z_VP - pVP->_Z) < 10) {
        //OK
    } else {
        pVP->_pKurokoA->setMvAng(_move_target_X_VP, _move_target_Y_VP, _move_target_Z_VP);
        int td2 = GgafDx9Util::getDistance(pVP->_X, pVP->_Y, pVP->_Z,
                                           _move_target_X_VP, _move_target_Y_VP, _move_target_Z_VP);
        if (MyStgUtil::abs(td2) > 10) {
            pVP->_pKurokoA->execSmoothMvVeloSequence(0, td2, 20, 0.4, 0.6);
        }
    }


    //カメラのUPを計算
    angvelo angvelo_cam_up = 30000 / 20;
    if (_angXY_nowCamUp != _move_target_XY_CAM_UP) {
        appangle da = GgafDx9Util::getAngDiff(_angXY_nowCamUp, _move_target_XY_CAM_UP);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            _angXY_nowCamUp = _move_target_XY_CAM_UP;
        } else {
            _angXY_nowCamUp += (angvelo_cam_up * sgn(da));
        }
        _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
        pCam->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp / ANGLE_RATE];
        pCam->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp / ANGLE_RATE];
        pCam->_pVecCamUp->z = 0.0f;
    }


    pCam->_pKurokoA->behave();
    pVP->_pKurokoA->behave();

}

PauseCamWorker::~PauseCamWorker() {
}
