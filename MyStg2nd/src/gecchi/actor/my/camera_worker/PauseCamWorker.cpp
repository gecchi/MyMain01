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
}
void PauseCamWorker::initialize() {
    _pVPGuide = NEW ViewPointGuide("VPGuide");
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


    if ((GgafDx9Input::isBeingPressedMouseButton(0) || GgafDx9Input::isBeingPressedMouseButton(1) || GgafDx9Input::isBeingPressedMouseButton(2))) {

        if (GgafDx9Input::isPushedDownMouseButton(0) || GgafDx9Input::isPushedDownMouseButton(1) || GgafDx9Input::isPushedDownMouseButton(2)) {
            RECT cRect; // クライアント領域の矩形
            int cw, ch; // クライアント領域の幅、高さ
            // クライアント領域の幅・高さを計算
            GetClientRect(GgafDx9God::_hWnd, &cRect);
            cw = cRect.right - cRect.left;
            ch = cRect.bottom - cRect.top;
            if (cw > ch) {
                _cd = ch;
            } else {
                _cd = cw;
            }

            _move_target_X_CAM = pCam->_X;
            _move_target_Y_CAM = pCam->_Y;
            _move_target_Z_CAM = pCam->_Z;
            //正確なVPに再設定
            pVP->_X = pCam->_pVecCamLookatPoint->x*PX_UNIT*LEN_UNIT;
            pVP->_Y = pCam->_pVecCamLookatPoint->y*PX_UNIT*LEN_UNIT;
            pVP->_Z = pCam->_pVecCamLookatPoint->z*PX_UNIT*LEN_UNIT;
            _move_target_X_VP = pVP->_X;
            _move_target_Y_VP = pVP->_Y;
            _move_target_Z_VP = pVP->_Z;
        }

    //計算

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
        D3DXMatrixInverse( &InvView, NULL, &pCam->_vMatrixView );
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
            _stop_renge = 60000;
            //視点→カメラ の方向ベクトル(x,y,z)
            double x = _move_target_X_CAM - _move_target_X_VP;
            double y = _move_target_Y_CAM - _move_target_Y_VP;
            double z = _move_target_Z_CAM - _move_target_Z_VP;

            angle rz1 = GgafDx9Util::getAngle2D(x, y);

            //回転させたい角度
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);

            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = GgafDx9Util::getAngle2D(Q._x,Q._y);

            //Q._x, Q._y, Q._z が回転後の座標となる
            if (abs(mdy) > abs(mdx)) {
                _move_target_XY_CAM_UP += GgafDx9Util::getAngDiff(rz1, rz2);
                _move_target_XY_CAM_UP = GgafDx9Util::simplifyAng(_move_target_XY_CAM_UP);
            }
            _move_target_X_CAM = Q._x + _move_target_X_VP;
            _move_target_Y_CAM = Q._y + _move_target_Y_VP;
            _move_target_Z_CAM = Q._z + _move_target_Z_VP;
        }
        //カメラを中心に視点が回転移動
        if (GgafDx9Input::isBeingPressedMouseButton(1) && (mdx != 0 || mdy != 0)) {
            _stop_renge = 60000;
            //カメラ→視点 の方向ベクトル(x,y,z)
            double x = _move_target_X_VP - _move_target_X_CAM;
            double y = _move_target_Y_VP - _move_target_Y_CAM;
            double z = _move_target_Z_VP - _move_target_Z_CAM;
            angle rz1 = GgafDx9Util::getAngle2D(x, y);
            //回転させたい角度
            double ang = (PI) * (d/_cd);
            double sinHalf = sin(ang/2);
            double cosHalf = cos(ang/2);
            GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
            Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
            Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
            angle rz2 = GgafDx9Util::getAngle2D(Q._x,Q._y);
            if (abs(mdy) > abs(mdx)) {
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

            double r = ((d/_cd)*GgafDx9Properties::GAME_BUFFER_WIDTH*2)*LEN_UNIT;

            _move_target_X_CAM += (Q._x*r);
            _move_target_Y_CAM += (Q._y*r);
            _move_target_Z_CAM += (Q._z*r);

            _move_target_X_VP += (Q._x*r);
            _move_target_Y_VP += (Q._y*r);
            _move_target_Z_VP += (Q._z*r);
        }
    } else {
    }


    //マウスホイール回転時
    if (mdz != 0) {
        _stop_renge = 60000;
        if (_mdz_flg == false) {
            _mdz_total = 0;
            _move_target_X_CAM = pCam->_X;
            _move_target_Y_CAM = pCam->_Y;
            _move_target_Z_CAM = pCam->_Z;
            //正確なVPに再設定
            pVP->_X = pCam->_pVecCamLookatPoint->x*PX_UNIT*LEN_UNIT;
            pVP->_Y = pCam->_pVecCamLookatPoint->y*PX_UNIT*LEN_UNIT;
            pVP->_Z = pCam->_pVecCamLookatPoint->z*PX_UNIT*LEN_UNIT;
            _move_target_X_VP = pVP->_X;
            _move_target_Y_VP = pVP->_Y;
            _move_target_Z_VP = pVP->_Z;

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
        double r = (mdz*PX_UNIT*LEN_UNIT/10.0);
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


//    //マウスホイール回転時
//    if (mdz != 0) {
//        _stop_renge = 60000;
//        if (_mdz_flg == false) {
//            _mdz_total = 0;
//            _move_target_X_CAM = pCam->_X;
//            _move_target_Y_CAM = pCam->_Y;
//            _move_target_Z_CAM = pCam->_Z;
//            //正確なVPに再設定
//            pVP->_X = pCam->_pVecCamLookatPoint->x*PX_UNIT*LEN_UNIT;
//            pVP->_Y = pCam->_pVecCamLookatPoint->y*PX_UNIT*LEN_UNIT;
//            pVP->_Z = pCam->_pVecCamLookatPoint->z*PX_UNIT*LEN_UNIT;
//            _move_target_X_VP = pVP->_X;
//            _move_target_Y_VP = pVP->_Y;
//            _move_target_Z_VP = pVP->_Z;
////
////            _cam_X = pCam->_X;
////            _cam_Y = pCam->_Y;
////            _cam_Z = pCam->_Z;
////            _vp_X = pVP->_X;
////            _vp_Y = pVP->_Y;
////            _vp_Z = pVP->_Z;
//            //カメラ → 視点 の方向ベクトル
//            if (mdz > 0) {
//                pCam->_pKuroko->setMvAng(pVP->_X - pCam->_X,
//                                         pVP->_Y - pCam->_Y,
//                                         pVP->_Z - pCam->_Z);
//                pVP->_pKuroko->setMvAng(pVP->_X - pCam->_X,
//                                        pVP->_Y - pCam->_Y,
//                                        pVP->_Z - pCam->_Z);
//            } else if (mdz < 0) {
//                pCam->_pKuroko->setMvAng(-(pVP->_X - pCam->_X),
//                                         -(pVP->_Y - pCam->_Y),
//                                         -(pVP->_Z - pCam->_Z));
//                pVP->_pKuroko->setMvAng(-(pVP->_X - pCam->_X),
//                                        -(pVP->_Y - pCam->_Y),
//                                        -(pVP->_Z - pCam->_Z));
//            }
//            pCam->_pKuroko->forceMvVeloRange(0,_cam_velo_renge);
//            pVP->_pKuroko->forceMvVeloRange(0,_cam_velo_renge);
//            pCam->_pKuroko->setMvAcce(-100);
//            pVP->_pKuroko->setMvAcce(-100);
//
////
////            double t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
////            _mdz_vx = t * vx;
////            _mdz_vy = t * vy;
////            _mdz_vz = t * vz;
//        }
//        _mdz_total = mdz; //連続ホイール回転時、加算
//        int r = (_mdz_total*LEN_UNIT*10);
//        pCam->_pKuroko->addMvVelo(r);
//        pVP->_pKuroko->addMvVelo(r);
//
////
////        _move_target_X_CAM = _cam_X + _mdz_vx*r;
////        _move_target_Y_CAM = _cam_Y + _mdz_vy*r;
////        _move_target_Z_CAM = _cam_Z + _mdz_vz*r;
////        _move_target_X_VP  = _vp_X  + _mdz_vx*r;
////        _move_target_Y_VP  = _vp_Y  + _mdz_vy*r;
////        _move_target_Z_VP  = _vp_Z  + _mdz_vz*r;
//        _mdz_flg = true;
//    } else {
////        pCam->_pKuroko->setMvVelo(0);
////        pVP->_pKuroko->setMvVelo(0);
//       // pCam->_pKuroko->setMvAcce(0);
//       // pVP->_pKuroko->setMvAcce(0);
//        _mdz_flg = false;
//    }


    //コマ送り
    if (VB_UI->isPushedDown(VB_BUTTON7)) {
        P_GAME_SCENE->_is_frame_advance = true;
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
        if (!_pVPGuide->isActiveActor()) {
            _pVPGuide->activate();
        }
    } else {
        if (_pVPGuide->isActiveActor()) {
            _pVPGuide->inactivate();
        }
    }

    if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
        //V＋方向で注視点操作
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            pVP->_Y += 5000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            pVP->_Y -= 5000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            pVP->_X += 5000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            pVP->_X -= 5000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            pVP->_Z += 5000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            pVP->_Z -= 5000;
        } else {
        }
    } else if (GgafDx9Input::isBeingPressedKey(DIK_C)) {
        //C＋方向でカメラ操作
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            P_CAM->_Y += 5000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            P_CAM->_Y -= 5000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            P_CAM->_X += 5000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            P_CAM->_X -= 5000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            P_CAM->_Z += 5000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            P_CAM->_Z -= 5000;
        } else {
        }
    } else {
    }


    //DefaultCameraWorker::processBehavior();

    //初期カメラ移動範囲制限
//    float revise = 0.7; //斜めから見るので補正値を掛ける。1.0の場合は原点からでドンピシャ。これは微調整を繰り返した
//    GgafDx9Camera* pCam = P_CAM;
//    GgafDx9GeometricActor* pVP = pCam->_pViewPoint;

    int cam_velo_renge = _cam_velo_renge;  //カメラの移動速度の最大、最小敷居値
    //カメラの移動速度の最大、最小制限を設定
    pCam->_pKuroko->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKuroko->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pCam->_pKuroko->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKuroko->forceVxMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKuroko->forceVyMvVeloRange(-cam_velo_renge, cam_velo_renge);
    pVP->_pKuroko->forceVzMvVeloRange(-cam_velo_renge, cam_velo_renge);

    //カメラ、及びビューポイントの移動速度を求める。

    //カメラの目標座標までの各軸の距離（座標差分）
    int dX_CAM = _move_target_X_CAM - pCam->_X;
    int dY_CAM = _move_target_Y_CAM - pCam->_Y;
    int dZ_CAM = _move_target_Z_CAM - pCam->_Z;
    if ( _pLockOnTarget) {
        _move_target_X_VP = _pLockOnTarget->_X;
        _move_target_Y_VP = _pLockOnTarget->_Y;
        _move_target_Z_VP = _pLockOnTarget->_Z;
    }
    //ビューポイントの目標座標までの各軸の距離（座標差分）
    int dX_VP = _move_target_X_VP - pVP->_X;
    int dY_VP = _move_target_Y_VP - pVP->_Y;
    int dZ_VP = _move_target_Z_VP - pVP->_Z;
    velo veloVxRenge = 4000;
    velo veloVyRenge = 4000;
    velo veloVzRenge = 4000;

    velo last_CAM_veloVxMv = pCam->_pKuroko->_veloVxMv;
    velo  new_CAM_veloVxMv = _burenai_speed*(dX_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVxMv-veloVxRenge <= new_CAM_veloVxMv && new_CAM_veloVxMv <= last_CAM_veloVxMv+veloVxRenge) {
        pCam->_pKuroko->setVxMvVelo(new_CAM_veloVxMv);
    } else {
        if (last_CAM_veloVxMv-veloVxRenge > new_CAM_veloVxMv) {
            pCam->_pKuroko->setVxMvVelo(last_CAM_veloVxMv-veloVxRenge);
        } else if (new_CAM_veloVxMv > last_CAM_veloVxMv+veloVxRenge) {
            pCam->_pKuroko->setVxMvVelo(last_CAM_veloVxMv+veloVxRenge);
        }
    }
    velo last_VP_veloVxMv = pVP->_pKuroko->_veloVxMv;
    velo  new_VP_veloVxMv = _burenai_speed*(dX_VP*1.0 / _stop_renge);
    if (last_VP_veloVxMv-veloVxRenge <= new_VP_veloVxMv && new_VP_veloVxMv <= last_VP_veloVxMv+veloVxRenge) {
        pVP->_pKuroko->setVxMvVelo(new_VP_veloVxMv);
    } else {
        if (last_VP_veloVxMv-veloVxRenge > new_VP_veloVxMv) {
            pVP->_pKuroko->setVxMvVelo(last_VP_veloVxMv-veloVxRenge);
        } else if (new_VP_veloVxMv > last_VP_veloVxMv+veloVxRenge) {
            pVP->_pKuroko->setVxMvVelo(last_VP_veloVxMv+veloVxRenge);
        }
    }

    velo last_CAM_veloVyMv = pCam->_pKuroko->_veloVyMv;
    velo  new_CAM_veloVyMv = _burenai_speed*(dY_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVyMv-veloVyRenge <= new_CAM_veloVyMv && new_CAM_veloVyMv <= last_CAM_veloVyMv+veloVyRenge) {
        pCam->_pKuroko->setVyMvVelo(new_CAM_veloVyMv);
    } else {
        if (last_CAM_veloVyMv-veloVyRenge > new_CAM_veloVyMv) {
            pCam->_pKuroko->setVyMvVelo(last_CAM_veloVyMv-veloVyRenge);
        } else if (new_CAM_veloVyMv > last_CAM_veloVyMv+veloVyRenge) {
            pCam->_pKuroko->setVyMvVelo(last_CAM_veloVyMv+veloVyRenge);
        }
    }
    velo last_VP_veloVyMv = pVP->_pKuroko->_veloVyMv;
    velo  new_VP_veloVyMv = _burenai_speed*(dY_VP*1.0 / _stop_renge);
    if (last_VP_veloVyMv-veloVyRenge <= new_VP_veloVyMv && new_VP_veloVyMv <= last_VP_veloVyMv+veloVyRenge) {
        pVP->_pKuroko->setVyMvVelo(new_VP_veloVyMv);
    } else {
        if (last_VP_veloVyMv-veloVyRenge > new_VP_veloVyMv) {
            pVP->_pKuroko->setVyMvVelo(last_VP_veloVyMv-veloVyRenge);
        } else if (new_VP_veloVyMv > last_VP_veloVyMv+veloVyRenge) {
            pVP->_pKuroko->setVyMvVelo(last_VP_veloVyMv+veloVyRenge);
        }
    }

    velo last_CAM_veloVzMv = pCam->_pKuroko->_veloVzMv;
    velo  new_CAM_veloVzMv = _burenai_speed*(dZ_CAM*1.0 / _stop_renge);
    if (last_CAM_veloVzMv-veloVzRenge <= new_CAM_veloVzMv && new_CAM_veloVzMv <= last_CAM_veloVzMv+veloVzRenge) {
        pCam->_pKuroko->setVzMvVelo(new_CAM_veloVzMv);
    } else {
        if (last_CAM_veloVzMv-veloVzRenge > new_CAM_veloVzMv) {
            pCam->_pKuroko->setVzMvVelo(last_CAM_veloVzMv-veloVzRenge);
        } else if (new_CAM_veloVzMv > last_CAM_veloVzMv+veloVzRenge) {
            pCam->_pKuroko->setVzMvVelo(last_CAM_veloVzMv+veloVzRenge);
        }
    }
    velo last_VP_veloVzMv = pVP->_pKuroko->_veloVzMv;
    velo  new_VP_veloVzMv = _burenai_speed*(dZ_VP*1.0 / _stop_renge);
    if (last_VP_veloVzMv-veloVzRenge <= new_VP_veloVzMv && new_VP_veloVzMv <= last_VP_veloVzMv+veloVzRenge) {
        pVP->_pKuroko->setVzMvVelo(new_VP_veloVzMv);
    } else {
        if (last_VP_veloVzMv-veloVzRenge > new_VP_veloVzMv) {
            pVP->_pKuroko->setVzMvVelo(last_VP_veloVzMv-veloVzRenge);
        } else if (new_VP_veloVzMv > last_VP_veloVzMv+veloVzRenge) {
            pVP->_pKuroko->setVzMvVelo(last_VP_veloVzMv+veloVzRenge);
        }
    }

    //カメラのUPを計算
    angvelo angvelo_cam_up = cam_velo_renge/20;

    if (_angXY_nowCamUp != _move_target_XY_CAM_UP) {
        angle da = GgafDx9Util::getAngDiff(_angXY_nowCamUp, _move_target_XY_CAM_UP);
        if (-angvelo_cam_up < da && da < angvelo_cam_up) {
            _angXY_nowCamUp = _move_target_XY_CAM_UP;
        } else {
            _angXY_nowCamUp += (angvelo_cam_up * sgn(da));
        }
        _angXY_nowCamUp = GgafDx9Util::simplifyAng(_angXY_nowCamUp);
        pCam->_pVecCamUp->x = GgafDx9Util::COS[_angXY_nowCamUp/ANGLE_RATE];
        pCam->_pVecCamUp->y = GgafDx9Util::SIN[_angXY_nowCamUp/ANGLE_RATE];
        pCam->_pVecCamUp->z = 0.0f;
    }


    pCam->_pKuroko->setVxMvVelo(pCam->_pKuroko->_veloVxMv*GgafUtil::abs(_mdz_vx));
    pCam->_pKuroko->setVyMvVelo(pCam->_pKuroko->_veloVyMv*GgafUtil::abs(_mdz_vy));
    pCam->_pKuroko->setVzMvVelo(pCam->_pKuroko->_veloVzMv*GgafUtil::abs(_mdz_vz));
    pVP->_pKuroko->setVxMvVelo(pVP->_pKuroko->_veloVxMv*GgafUtil::abs(_mdz_vx));
    pVP->_pKuroko->setVyMvVelo(pVP->_pKuroko->_veloVyMv*GgafUtil::abs(_mdz_vy));
    pVP->_pKuroko->setVzMvVelo(pVP->_pKuroko->_veloVzMv*GgafUtil::abs(_mdz_vz));


    pCam->_pKuroko->behave();
    pVP->_pKuroko->behave();
//    CameraWorker::processBehavior();
//
//    //マウスホイール回転時
//    if (mdz != 0) {
//        pCam->_pKuroko->setVxMvVelo(pCam->_pKuroko->_veloVxMv*_mdz_vx);
//        pCam->_pKuroko->setVyMvVelo(pCam->_pKuroko->_veloVyMv*_mdz_vy);
//        pCam->_pKuroko->setVzMvVelo(pCam->_pKuroko->_veloVzMv*_mdz_vz);
//        pVP->_pKuroko->setVxMvVelo(pVP->_pKuroko->_veloVxMv*_mdz_vx);
//        pVP->_pKuroko->setVyMvVelo(pVP->_pKuroko->_veloVyMv*_mdz_vy);
//        pVP->_pKuroko->setVzMvVelo(pVP->_pKuroko->_veloVzMv*_mdz_vz);
//    }

    //TODO:
    //orderSmoothMvVeloSequence3 を使え！！
}
PauseCamWorker::~PauseCamWorker() {
}
