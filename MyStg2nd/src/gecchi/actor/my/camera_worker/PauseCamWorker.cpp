#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

PauseCamWorker::PauseCamWorker(const char* prm_name) : CameraWorker(prm_name) {
    _class_name = "PauseCamWorker";
    _cd = 0;
}
void PauseCamWorker::initialize() {
}

void PauseCamWorker::onSwitchedCameraWork() {

    setMoveTargetCamBy(P_CAM);
    setMoveTargetCamVpBy(P_CAM->_pViewPoint);
}

void PauseCamWorker::processBehavior() {
    GgafDx9Camera* pCam = P_CAM;
    GgafDx9CameraViewPoint* pVP = P_CAM->_pViewPoint;
    GgafDx9Input::updateMouseState();

    long mx,my,mz,mdx,mdy,mdz;
    GgafDx9Input::getMousePointer(&mx, &my, &mz);
    GgafDx9Input::getMousePointer_REL(&mdx, &mdy, &mdz);
    mdy = -mdy; //Yはインバーズ
    if (GgafDx9Input::isBeingPressedMouseButton(0)) {
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
    }


    if (GgafDx9Input::isBeingPressedMouseButton(0) && (mdx != 0 || mdy != 0)) {
//    _TRACE_(GgafDx9Input::isPushedDownMouseButton(0) << GgafDx9Input::isBeingPressedMouseButton(0) << GgafDx9Input::isPushedDownMouseButton(1) << GgafDx9Input::isBeingPressedMouseButton(1));
//    _TRACE_(mx<<","<<my<<","<<mz<<" ("<<mdx<<","<<mdy<<","<<mdz<<")");
    //計算

    //
        //平面回転軸(vx,vy)を求める
        //double a = asin(1.0*dx/dy); //a XY平面のなす角 90度回転 x→y y→-x
        double vx = mdy;
        double vy = -mdx;
        double vz = 0;
//        _TRACE_("v="<<vx<<","<<vy<<","<<vz<<"");
        double d = sqrt(vx * vx + vy * vy);
//        _TRACE_("d="<<d);
        double t = 1.0 / d;
//        _TRACE_("t="<<t);
        vx = t * vx;
        vy = t * vy;
        vz = 0;
//        _TRACE_("v="<<vx<<","<<vy<<","<<vz<<"");
        //平面回転軸(vx,vy)をVPのワールド空間軸に変換
        //VP→CAMのワールド空間方向ベクトルを法線とする平面上に回転軸ベクトルは存在する

        D3DXMATRIX InvView;
        D3DXMatrixInverse( &InvView, NULL, &pCam->_vMatrixView );
        //(vx,vy,vz) * InvView
//        _11 _12 _13 _14
//        _21 _22 _23 _24
//        _31 _32 _33 _34
//        vx*_11 + vy*_21 + vz*_31 + _41  vx*_12 + vy*_22 + vz*_32 + _42  vx*_13 + vy*_23 + vz*_33 + _43  vx*_14 + vy*_24 + vz*_34 + _44
        //方向ベクトル(0,0,0)->(x,y,z)                                                     (0,0,0)変換分
        double vX_axis = vx*InvView._11 + vy*InvView._21 + vz*InvView._31 + InvView._41  - InvView._41;
        double vY_axis = vx*InvView._12 + vy*InvView._22 + vz*InvView._32 + InvView._42  - InvView._42;
        double vZ_axis = vx*InvView._13 + vy*InvView._23 + vz*InvView._33 + InvView._43  - InvView._43;



//        _TRACE_("axis<<"<<vX_axis<<","<<vY_axis<<","<<vZ_axis<<"");
        //正規化
        double d2 = sqrt(vX_axis * vX_axis + vY_axis * vY_axis + vZ_axis * vZ_axis);
        double t2 = 1.0 / d2;
        vX_axis = t2 * vX_axis;
        vY_axis = t2 * vY_axis;
        vZ_axis = t2 * vZ_axis;
//        _TRACE_("正規化axis<<"<<vX_axis<<","<<vY_axis<<","<<vZ_axis<<"");
        //端から端までつまむと９０度動くことにする。


        double ang = (2.0*PI) * (d2/_cd);
//        //カメラとVPの距離
//        int d_cam_vp = GgafDx9Util::getDistance(
//                _move_target_X_CAM,
//                _move_target_Y_CAM,
//                _move_target_Z_CAM,
//                _move_target_X_VP,
//                _move_target_Y_VP,
//                _move_target_Z_VP
//                );



        //ある座標(x, y, z)において、回転の軸が(α, β, γ)で、θ回す回転
        //P = (0; x, y, z)
        //Q = (cos(θ/2); α sin(θ/2), β sin(θ/2), γ sin(θ/2))
        //R = (cos(θ/2); -α sin(θ/2), -β sin(θ/2), -γ sin(θ/2))
        //
        //R P Q = (0; 答え)

        //(x, y, z) カメラ座標 ー 視点座標
        //(α, β, γ) = (vX_axis,vY_axis,vY_axis);

        double x = _move_target_X_CAM - _move_target_X_VP;
        double y = _move_target_Y_CAM - _move_target_Y_VP;
        double z = _move_target_Z_CAM - _move_target_Z_VP;
        double sinHalf = sin(ang); //回転させたい角度
        double cosHalf = cos(ang);

        GgafDx9Quaternion Q(cosHalf, -vX_axis*sinHalf, -vY_axis*sinHalf, -vZ_axis*sinHalf);  //R
        Q.mul(0,x,y,z);//R*P 回転軸が現在の進行方向ベクトルとなる
        Q.mul(cosHalf, vX_axis*sinHalf, vY_axis*sinHalf, vZ_axis*sinHalf); //R*P*Q
        //Q._x, Q._y, Q._z が回転後の座標となる

        //Z軸回転、Y軸回転角度を計算
       // GgafDx9Util::getRzRyAng(
       //     Q._x, Q._y, Q._z,
       //     _RZ, _RY
       //  );


        _move_target_X_CAM = Q._x + _move_target_X_VP;
        _move_target_Y_CAM = Q._y + _move_target_Y_VP;
        _move_target_Z_CAM = Q._z + _move_target_Z_VP;
    }

    if (mdz != 0) {
        double vx, vy, vz, t;
        vx = (double)(_move_target_X_VP - _move_target_X_CAM);
        vy = (double)(_move_target_Y_VP - _move_target_Y_CAM);
        vz = (double)(_move_target_Z_VP - _move_target_Z_CAM);
        t = 1.0 / sqrt(vx * vx + vy * vy + vz * vz);
        vx = t * vx;
        vy = t * vy;
        vz = t * vz;

        _move_target_X_CAM += (vx*mdz*PX_UNIT*LEN_UNIT/10.0);
        _move_target_Y_CAM += (vy*mdz*PX_UNIT*LEN_UNIT/10.0);
        _move_target_Z_CAM += (vz*mdz*PX_UNIT*LEN_UNIT/10.0);
        _move_target_X_VP += (vx*mdz*PX_UNIT*LEN_UNIT/10.0);
        _move_target_Y_VP += (vy*mdz*PX_UNIT*LEN_UNIT/10.0);
        _move_target_Z_VP += (vz*mdz*PX_UNIT*LEN_UNIT/10.0);

    }





    //コマ送り
    if (VB_UI->isPushedDown(VB_BUTTON7)) {
        P_GAME_SCENE->_is_frame_advance = true;
    }

    //一時停止してい状態

    if (GgafDx9Input::isBeingPressedKey(DIK_V)) {
        //V＋方向で注視点操作
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            pVP->_Y += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            pVP->_Y -= 8000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            pVP->_X += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            pVP->_X -= 8000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            pVP->_Z += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            pVP->_Z -= 8000;
        } else {
        }
    } else if (GgafDx9Input::isBeingPressedKey(DIK_C)) {
        //C＋方向でカメラ操作
        if (GgafDx9Input::isBeingPressedKey(DIK_UP)) {
            P_CAM->_Y += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_DOWN)) {
            P_CAM->_Y -= 8000;
        } else {

        }

        if (GgafDx9Input::isBeingPressedKey(DIK_RIGHT)) {
            P_CAM->_X += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_LEFT)) {
            P_CAM->_X -= 8000;
        } else {
        }

        if (GgafDx9Input::isBeingPressedKey(DIK_PGUP)) {
            P_CAM->_Z += 8000;
        } else if (GgafDx9Input::isBeingPressedKey(DIK_PGDN)) {
            P_CAM->_Z -= 8000;
        } else {
        }
    }
    CameraWorker::processBehavior();
}
PauseCamWorker::~PauseCamWorker() {
}
