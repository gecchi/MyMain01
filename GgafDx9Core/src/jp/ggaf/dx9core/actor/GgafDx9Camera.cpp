#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Camera::GgafDx9Camera(const char* prm_name, float prm_rad_fovX) : GgafDx9GeometricActor(prm_name, NULL) {
    _class_name = "GgafDx9Camera";
    _pMover = NEW GgafDx9GeometryMover(this);
    //全ての基準はfovXから考える
    _rad_fovX = prm_rad_fovX;
    //半分を保持
    _rad_half_fovX = _rad_fovX / 2.0;
    //画面アスペクト比(w/h)
    _screen_aspect = (FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));
    //fovXとアスペクト比からfovYを計算して求める
    double xzRatio = tan( _rad_fovX/2 );
    double yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2.0;
    //半分を保持
    _rad_half_fovY = _rad_fovY / 2.0;
    //tan値も保持
    _tan_half_fovY = tan(_rad_fovY/2.0);
    _tan_half_fovX = tan(_rad_fovX/2.0);
    //初期カメラ位置は視点(0,0,Z)、注視点(0,0,0)
    //Zは、キャラがZ=0のXY平面で丁度キャラが値ピクセル幅と一致するような所にカメラを引く
    _cameraZ = -1.0 * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("カメラの位置(0,0,"<<_cameraZ<<")");
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ); //位置
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //注視する方向
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //上方向

    // VIEW変換行列作成
    D3DXMatrixLookAtLH(
       &_vMatrixView,         // pOut [in, out] 演算結果である D3DXMATRIX 構造体へのポインタ。
        _pVecCamFromPoint,    // pEye [in] 視点を定義する D3DXVECTOR3 構造体へのポインタ。この値は、平行移動に使用される。
        _pVecCamLookatPoint,  // pAt  [in] カメラの注視対象を定義する D3DXVECTOR3 構造体へのポインタ。
        _pVecCamUp            // pUp  [in] カレント ワールドの上方、一般には [0, 1, 0] を定義する D3DXVECTOR3 構造体へのポインタ。
    );

    // 射影変換行列作成（３Ｄ→平面）
    D3DXMatrixPerspectiveFovLH(
            &_vMatrixProj,
            _rad_fovY, //y方向視野角ラディアン(0～π)
            _screen_aspect, //アスペクト比  640×480 の場合  640/480
            1.0, //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            500.0 //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
            //(FLOAT)(-1.0*dCam*4)
            //(-1.0*fCam)-30,
            //(-1.0*fCam)+30
    );
    /*
     //左手座標系正射影
     D3DXMatrixOrthoLH(
     &_vMatrixProj,
     GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH),
     GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT),
     1.0f,
     GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)
     );
     */


    _gazeX = _pVecCamLookatPoint->x * LEN_UNIT * PX_UNIT;
    _gazeY = _pVecCamLookatPoint->y * LEN_UNIT * PX_UNIT;
    _gazeZ = _pVecCamLookatPoint->z * LEN_UNIT * PX_UNIT;
    _X = _pVecCamFromPoint->x * LEN_UNIT * PX_UNIT;
    _Y = _pVecCamFromPoint->y * LEN_UNIT * PX_UNIT;
    _Z = _pVecCamFromPoint->z * LEN_UNIT * PX_UNIT;

    _pMover->setMoveAngle(0,0,0);
    _pMover->setMoveVelocity(0);
    _pMover->setRzMoveAngleVelocity(0);
    _pMover->setRyMoveAngleVelocity(0);
    _pMover->_move_angle_rz_target_flg = true;
    _pMover->_move_angle_ry_target_flg = true;


    setBumpable(false);
}

void GgafDx9Camera::initialize() {

}




void GgafDx9Camera::processBehavior() {

    HRESULT hr;
    D3DVIEWPORT9 viewport;       //クライアント領域全体の保持
    //スクリーン全体のクライアント領域を保持。
    hr = GgafDx9God::_pID3DDevice9->GetViewport(&viewport);

    // viewport.MinZ / MaxZ は、通常それぞれ 0 / 1
     float x1 = (float)viewport.X;
     float y1 = (float)viewport.Y;
     float x2 = (float)viewport.X + (float)viewport.Width;
     float y2 = (float)viewport.Y + (float)viewport.Height;

     // 視錐台の８点が格納されるインスタンス
     _vecNear[0] = D3DXVECTOR3( x1, y1, viewport.MinZ ); // 左下 (変換後)
     _vecNear[1] = D3DXVECTOR3( x2, y1, viewport.MinZ ); // 右下 (変換後)
     _vecNear[2] = D3DXVECTOR3( x1, y2, viewport.MinZ ); // 左上 (変換後)
     _vecNear[3] = D3DXVECTOR3( x2, y2, viewport.MinZ ); // 右上 (変換後)

     _vecFar[0]  = D3DXVECTOR3( x1, y1, viewport.MaxZ ); // 左下 (変換後)
     _vecFar[1]  = D3DXVECTOR3( x2, y1, viewport.MaxZ ); // 右下 (変換後)
     _vecFar[2]  = D3DXVECTOR3( x1, y2, viewport.MaxZ ); // 左上 (変換後)
     _vecFar[3]  = D3DXVECTOR3( x2, y2, viewport.MaxZ ); // 右上 (変換後)

     // 視錐台の８点の計算
     D3DXMATRIX mat_world;
     D3DXMatrixIdentity( &mat_world );
     D3DVIEWPORT9 *pViewport = const_cast<D3DVIEWPORT9*>(&viewport);
     // ワールド → ビュー → 射影 → スクリーン変換 の逆を行う
     for( int i = 0; i < 4; ++i )
     {
         D3DXVec3Unproject(
             &_vecNear[i],   //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
             &_vecNear[i],   //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。
             pViewport,      //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
             &_vMatrixProj,  //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
             &_vMatrixView,  //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
             &mat_world      //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
         );
         D3DXVec3Unproject(
             &_vecFar[i],
             &_vecFar[i],
             pViewport,
             &_vMatrixProj,
             &_vMatrixView,
             &mat_world
         );
     }
     //-------------------------------------------------
     //  平面方程式：ax+by+cz+d
     //  平面の法線ベクトル：n = (a, b, c)
     //  平面上の1点を、p = (x0, y0, z0) とすると、
     //  平面の法線ベクトルと平面状の1点の内積：d = n*p
     //
     //  表裏判定をするときは、点 p = (x0, y0, z0)を、
     //  p = (x0, y0, z0, 1) とみなし、
     //  平面との内積：a*x0 + b*y0 + c*z0 + d*1 = ans
     //  ans > 0 なら表、ans < 0 なら裏、ans == 0 なら面上、となる。
     //  DXPlaneDotCoord() は、この処理を行っている
     //
     //  また、p = (x0, y0, z0, 0) とみなして内積の計算を行うと、
     //  角度の関係を調べることができる。
     //  → D3DXPlaneDotNormal()
     //-------------------------------------------------


     // 上 ( F左上、N左上、N右上 )
    D3DXPlaneNormalize(
        &_plnTop,
        D3DXPlaneFromPoints(&_plnTop, &(_vecFar[2]), &(_vecNear[2]), &(_vecNear[3]))
    );
    // 下 ( F左下、N右下、N左下 )
    D3DXPlaneNormalize(
        &_plnBottom,
        D3DXPlaneFromPoints(&_plnBottom, &(_vecFar[0]), &(_vecNear[1]), &(_vecNear[0]))
    );
    // 左 ( F左下、N左下、N左上 )
    D3DXPlaneNormalize(
        &_plnLeft,
        D3DXPlaneFromPoints(&_plnLeft, &(_vecFar[0]), &(_vecNear[0]), &(_vecNear[2]))
    );
    // 右 ( F右下、N右上、N右下 )
    D3DXPlaneNormalize(
        &_plnRight,
        D3DXPlaneFromPoints(&_plnRight, &(_vecFar[1]), &(_vecNear[3]), &(_vecNear[1]))
    );
    // 手前 ( N左上、N左下、N右上)
    D3DXPlaneNormalize(
        &_plnFront,
        D3DXPlaneFromPoints(&_plnFront, &(_vecNear[2]), &(_vecNear[0]), &(_vecNear[3]))
    );
    // 奥 ( F右上、F左下、F左上)
    D3DXPlaneNormalize(
        &_plnBack,
        D3DXPlaneFromPoints(&_plnBack, &(_vecFar[3]), &(_vecFar[0]), &(_vecFar[2]))
    );

}



void GgafDx9Camera::processJudgement() {
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    _pVecCamLookatPoint->x = (1.0 * _gazeX) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->y = (1.0 * _gazeY) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->z = (1.0 * _gazeZ) / LEN_UNIT / PX_UNIT;
    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}


GgafDx9Camera::~GgafDx9Camera() {
    //いろいろ解放
    DELETE_IMPOSSIBLE_NULL(_pMover);
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

}
