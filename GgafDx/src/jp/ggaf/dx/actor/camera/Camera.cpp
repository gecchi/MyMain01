#include "jp/ggaf/dx/actor/camera/Camera.h"

#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/camera/CameraViewPoint.h"
#include "jp/ggaf/dx/actor/camera/CameraUpVector.h"
#include "jp/ggaf/dx/Caretaker.h"


using namespace GgafDx;

Camera::Camera(const char* prm_name, double prm_rad_fovX, double prm_dep) :
        GeometricActor(prm_name, nullptr),
_rad_fovX(prm_rad_fovX),      //全ての基準はfovXから考える
_dep(prm_dep),
_rad_half_fovX(_rad_fovX / 2.0),
_screen_aspect(1.0 * (CONFIG::GAME_BUFFER_WIDTH) / (CONFIG::GAME_BUFFER_HEIGHT)),
_rad_fovY(atan( ( (tan(_rad_fovX/2.0)) / _screen_aspect) )*2.0),
_rad_half_fovY(_rad_fovY / 2.0),
_tan_half_fovX(tan(_rad_fovX/2.0)),
_tan_half_fovY(tan(_rad_fovY/2.0)),
_cameraZ_org(-1.0 * ((1.0 * (CONFIG::GAME_BUFFER_HEIGHT) / PX_UNIT) / 2.0) / _tan_half_fovY),
_zn(0.1f),
_zf(-_cameraZ_org*(_dep+1.0)-_zn),
_x_buffer_left(PX_C(CONFIG::GAME_BUFFER_WIDTH) / -2),
_x_buffer_right(PX_C(CONFIG::GAME_BUFFER_WIDTH) / 2),
_y_buffer_top(PX_C(CONFIG::GAME_BUFFER_HEIGHT) / 2),
_y_buffer_bottom(PX_C(CONFIG::GAME_BUFFER_HEIGHT) / -2)
{
    _class_name = "Camera";
    //fovXとアスペクト比からfovYを計算して求める
    _TRACE_(FUNC_NAME<<" 画面アスペクト："<<_screen_aspect);
    _TRACE_(FUNC_NAME<<" FovX="<<prm_rad_fovX<<" FovY="<<_rad_fovY);


    //初期カメラ位置は視点(0,0,Z)、注視点(0,0,0)
    //Zは、キャラがZ=0のXY平面で丁度キャラが値ピクセル幅と一致するような所にカメラを引く
    _TRACE_(FUNC_NAME<<" カメラの位置(0,0,"<<_cameraZ_org<<") dxcoord");
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ_org); //位置
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //注視する方向
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //上方向

    // VIEW変換行列作成
    D3DXMatrixLookAtLH(
       &_matView,             // pOut [in, out] 演算結果である D3DXMATRIX 構造体へのポインタ。
        _pVecCamFromPoint,    // pEye [in] 視点を定義する D3DXVECTOR3 構造体へのポインタ。この値は、平行移動に使用される。
        _pVecCamLookatPoint,  // pAt  [in] カメラの注視対象を定義する D3DXVECTOR3 構造体へのポインタ。
        _pVecCamUp            // pUp  [in] カレント ワールドの上方、一般には [0, 1, 0] を定義する D3DXVECTOR3 構造体へのポインタ。
    );

    // 射影変換行列作成
    _TRACE_(FUNC_NAME<<" _cameraZ_org="<<_cameraZ_org<<" dxcoord");
    _TRACE_(FUNC_NAME<<" _dep="<<_dep<<"");
    _TRACE_(FUNC_NAME<<" _zn=" << _zn << " dxcoord");
    _TRACE_(FUNC_NAME<<" _zf=("<<-_cameraZ_org<<"*("<<_dep<<"+1.0)-"<<_zn<<")=" << _zf << " dxcoord");
    _TRACE_(FUNC_NAME<<" カメラの表示距離範囲 ["<<_zn<<" ~ "<<_zf<<"] dxcoord");

    //正射影
    D3DXMatrixOrthoLH(
        &_matOrthoProj,
        PX_DX(CONFIG::GAME_BUFFER_WIDTH),
        PX_DX(CONFIG::GAME_BUFFER_HEIGHT),
        _zn,
        _zf
    );

    if (CONFIG::PRJ_2D_MODE) {
        //2Dモード正射影
        D3DXMatrixOrthoLH(
            &_matProj,
            PX_DX(CONFIG::GAME_BUFFER_WIDTH),
            PX_DX(CONFIG::GAME_BUFFER_HEIGHT),
            _zn,
            _zf
        );
    } else {
        //3Dモード通常射影
        D3DXMatrixPerspectiveFovLH(
            &_matProj,
            _rad_fovY,       //y方向視野角ラディアン(0～π)
            _screen_aspect,  //アスペクト比  640×480 の場合  640/480
            _zn,             //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            _zf              //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
        );
    }

    setPosition(0, 0, DX_C(_cameraZ_org));
    setFaceAngTwd(0,0,0);
    getVecVehicle()->setMvAngTwd(0,0,0);
    setHitAble(false);

    pCARETAKER->_pID3DDevice9->GetViewport(&_viewport);
    _TRACE_("_viewport.X="<<_viewport.X);
    _TRACE_("_viewport.Y="<<_viewport.Y);
    _TRACE_("_viewport.Width="<<_viewport.Width);
    _TRACE_("_viewport.Height="<<_viewport.Height);
    _TRACE_("_viewport.MinZ="<<_viewport.MinZ);
    _TRACE_("_viewport.MaxZ="<<_viewport.MaxZ);
    _x_prev = 0;
    _y_prev = 0;
    _z_prev = 0;

    _pCameraViewPoint = nullptr;
    _pCameraUpVector = nullptr;


    //ビューポート行列
    // | W/2,    0, 0, 0 |
    // |   0, -H/2, 0, 0 |
    // |   0,    0, 1, 0 |
    // | W/2,  H/2, 0, 1 |
    //
    //W :スクリーン幅(ピクセル)
    //H :スクリーン高さ(ピクセル)

}

void Camera::initialize() {
    getCameraViewPoint();
    getCameraUpVector();
}

void Camera::processBehavior() {

    // _viewport.MinZ / MaxZ は、通常それぞれ 0 / 1
    const dxcoord x1 = dxcoord(_viewport.X);
    const dxcoord y1 = dxcoord(_viewport.Y);
    const dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
    const dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);

    //(x1,y1)   -------->
    //    +--------------------+
    //  | |                    |
    //  | |                    |
    //  | |                    |
    //  | |                    |
    //  | |                    |
    //  v |                    |
    //    +--------------------+
    //                         (x2,y2)
    //※y 軸が逆
    // 視錐台の８点が格納されるインスタンス
    _vecNear[0].x = x1;  _vecNear[0].y = y1;  _vecNear[0].z = _viewport.MinZ;   // 左下 (変換後)
    _vecNear[1].x = x2;  _vecNear[1].y = y1;  _vecNear[1].z = _viewport.MinZ;   // 右下 (変換後)
    _vecNear[2].x = x1;  _vecNear[2].y = y2;  _vecNear[2].z = _viewport.MinZ;   // 左上 (変換後)
    _vecNear[3].x = x2;  _vecNear[3].y = y2;  _vecNear[3].z = _viewport.MinZ;   // 右上 (変換後)

    _vecFar[0].x  = x1;  _vecFar[0].y  = y1;  _vecFar[0].z  = _viewport.MaxZ;   // 左下 (変換後)
    _vecFar[1].x  = x2;  _vecFar[1].y  = y1;  _vecFar[1].z  = _viewport.MaxZ;   // 右下 (変換後)
    _vecFar[2].x  = x1;  _vecFar[2].y  = y2;  _vecFar[2].z  = _viewport.MaxZ;   // 左上 (変換後)
    _vecFar[3].x  = x2;  _vecFar[3].y  = y2;  _vecFar[3].z  = _viewport.MaxZ;   // 右上 (変換後)

    // 視錐台の８点の計算
    const D3DXMATRIX mat_world = D3DXMATRIX(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );
    // ワールド → ビュー → 射影 → スクリーン変換 の逆を行う
    for ( int i = 0; i < 4; i++ ) {
        D3DXVec3Unproject(
            &_vecNear[i], //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
            &_vecNear[i], //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。
            &_viewport,   //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
            &_matProj,    //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
            &_matView,    //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
            &mat_world    //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
        );
        D3DXVec3Unproject(
            &_vecFar[i],
            &_vecFar[i],
            &_viewport,
            &_matProj,
            &_matView,
            &mat_world
        );
    }

    // 視錐台の面
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
        &_plnInfront,
        D3DXPlaneFromPoints(&_plnInfront, &(_vecNear[2]), &(_vecNear[0]), &(_vecNear[3]))
    );
    // 奥 ( F右上、F左下、F左上)
    D3DXPlaneNormalize(
        &_plnBack,
        D3DXPlaneFromPoints(&_plnBack, &(_vecFar[3]), &(_vecFar[0]), &(_vecFar[2]))
    );

    // 中心垂直面 （ボリュームパンで使用）
    _vecVerticalCenter[0].x = (_vecFar[1].x + _vecFar[0].x)*0.5f;
    _vecVerticalCenter[0].y = (_vecFar[1].y + _vecFar[0].y)*0.5f;
    _vecVerticalCenter[0].z = (_vecFar[1].z + _vecFar[0].z)*0.5f;

    _vecVerticalCenter[1].x = (_vecNear[3].x + _vecNear[2].x)*0.5f;
    _vecVerticalCenter[1].y = (_vecNear[3].y + _vecNear[2].y)*0.5f;
    _vecVerticalCenter[1].z = (_vecNear[3].z + _vecNear[2].z)*0.5f;

    _vecVerticalCenter[2].x = (_vecNear[1].x + _vecNear[0].x)*0.5f;
    _vecVerticalCenter[2].y = (_vecNear[1].y + _vecNear[0].y)*0.5f;
    _vecVerticalCenter[2].z = (_vecNear[1].z + _vecNear[0].z)*0.5f;

    D3DXPlaneNormalize(
        &_plnVerticalCenter,
        D3DXPlaneFromPoints(&_plnVerticalCenter, &(_vecVerticalCenter[0]),
                                                 &(_vecVerticalCenter[1]),
                                                 &(_vecVerticalCenter[2])
                            )
    );

}

void Camera::processSettlementBehavior() {
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);

    _x_prev = _x;
    _y_prev = _y;
    _z_prev = _z;
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    CameraViewPoint* pVp = getCameraViewPoint();
    _pVecCamLookatPoint->x = pVp->_fX;
    _pVecCamLookatPoint->y = pVp->_fY;
    _pVecCamLookatPoint->z = pVp->_fZ;
    CameraUpVector* pUpv = getCameraUpVector();
    _pVecCamUp->x = pUpv->_fX;
    _pVecCamUp->y = pUpv->_fY;
    _pVecCamUp->z = pUpv->_fZ;
    D3DXMatrixLookAtLH(&_matView,
                       _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}

CameraViewPoint* Camera::getCameraViewPoint() {
    if (_pCameraViewPoint) {
        return _pCameraViewPoint;
    } else {
        _pCameraViewPoint = createCameraViewPoint();
        _pCameraViewPoint->setPosition(0, 0, 0);
        appendGroupChild(_pCameraViewPoint);
        return _pCameraViewPoint;
    }
}

CameraUpVector* Camera::getCameraUpVector() {
    if (_pCameraUpVector) {
        return _pCameraUpVector;
    } else {
        _pCameraUpVector = createCameraUpVector();
        _pCameraUpVector->setPosition(0, DX_C(1), 0);
        appendGroupChild(_pCameraUpVector);
        return _pCameraUpVector;
    }
}

void Camera::setDefaultPosition() {
    _x = 0;
    _y = 0;
    _z = DX_C(_cameraZ_org);
    CameraViewPoint* pVp = getCameraViewPoint();
    pVp->setPosition(0, 0, 0);
    CameraUpVector* pUpv = getCameraUpVector();
    pUpv->setPosition(0, DX_C(1), 0);
}

bool Camera::isMoving() {
    if (_x_prev == _x && _y_prev == _y && _z_prev == _z) {
        return false;
    } else {
        return true;
    }
}

Camera::~Camera() {
    GGAF_DELETE(_pVecCamFromPoint);
    GGAF_DELETE(_pVecCamLookatPoint);
    GGAF_DELETE(_pVecCamUp);
}
