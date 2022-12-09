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

    if (CONFIG::PRJ_2D_MODE) {
        //2Dモード：正射影変換
        D3DXMatrixOrthoLH(
            &_matProj,
            PX_DX(CONFIG::GAME_BUFFER_WIDTH),
            PX_DX(CONFIG::GAME_BUFFER_HEIGHT),
            _zn,
            _zf
        );
    } else {
        //3Dモード：通常の射影変換
        D3DXMatrixPerspectiveFovLH(
            &_matProj,
            _rad_fovY,       //y方向視野角ラディアン(0～π)
            _screen_aspect,  //アスペクト比  640×480 の場合  640/480
            _zn,             //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            _zf              //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
        );
    }
    //射影変換逆行列
    D3DXMatrixInverse(&_matInvProj, nullptr, &_matProj);

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
    //ビューポート行列
    // |   W/2,     0,         0, 0 |
    // |     0,  -H/2,         0, 0 |
    // |     0,     0, MaxZ-MinZ, 0 |
    // | X+W/2, H/2+Y,      MinZ, 1 |
    D3DXMatrixIdentity(&_matViewPort);
    _matViewPort._11 =  _viewport.Width  / 2.0f;
    _matViewPort._22 = -1 * (_viewport.Height / 2.0f);
    _matViewPort._33 = _viewport.MaxZ - _viewport.MinZ;
    _matViewPort._41 = _viewport.X + (_viewport.Width / 2.0f);
    _matViewPort._42 = (_viewport.Height / 2.0f) + _viewport.Y;
    _matViewPort._43 = _viewport.MinZ;
    _matViewPort._44 = 1.0f;
    //ビューポート逆行列
    D3DXMatrixInverse(&_matInvViewPort, nullptr, &_matViewPort);

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
    const dxcoord x1 = dxcoord(_viewport.X);
    const dxcoord y1 = dxcoord(_viewport.Y);
    const dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
    const dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);
    // _viewport.MinZ / MaxZ は、通常それぞれ 0 / 1
    const float MinZ = 0;
    const float MaxZ = 1;
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
    // _11,  _12,  _13,  _14,   // → 左上座標
    // _21,  _22,  _23,  _24,   // → 右上座標
    // _31,  _32,  _33,  _34,   // → 左下座標
    // _41,  _42,  _43,  _44    // → 右下座標
    // を代入して、４点一度に
    //ワールド → ビュー → 射影 → スクリーン変換 の逆を行う

    //視錐台手前４頂点を求める
    D3DXMATRIX matScreenNear = D3DXMATRIX(
        x1, y1, MinZ, 1.0f,  // 手前左上スクリーン座標
        x2, y1, MinZ, 1.0f,  // 手前右上スクリーン座標
        x1, y2, MinZ, 1.0f,  // 手前左下スクリーン座標
        x2, y2, MinZ, 1.0f   // 手前右下スクリーン座標
    );
    D3DXMATRIX matNear = matScreenNear * _matInvViewPort_Proj_View;
    const float near0_W = matNear._14;
    const float near1_W = matNear._24;
    const float near2_W = matNear._34;
    const float near3_W = matNear._44;
    D3DXVECTOR3 vecNear0 = D3DXVECTOR3(matNear._11/near0_W, matNear._12/near0_W, matNear._13/near0_W); //手前左上ワールド座標
    D3DXVECTOR3 vecNear1 = D3DXVECTOR3(matNear._21/near1_W, matNear._22/near1_W, matNear._23/near1_W); //手前右上ワールド座標
    D3DXVECTOR3 vecNear2 = D3DXVECTOR3(matNear._31/near2_W, matNear._32/near2_W, matNear._33/near2_W); //手前左下ワールド座標
    D3DXVECTOR3 vecNear3 = D3DXVECTOR3(matNear._41/near3_W, matNear._42/near3_W, matNear._43/near3_W); //手前右下ワールド座標

    //視錐台奥４頂点を求める
    D3DXMATRIX matScreeFar = D3DXMATRIX(
        x1, y1, MaxZ, 1.0f,  // 左上スクリーン座標
        x2, y1, MaxZ, 1.0f,  // 右上スクリーン座標
        x1, y2, MaxZ, 1.0f,  // 左下スクリーン座標
        x2, y2, MaxZ, 1.0f   // 右下スクリーン座標
    );
    D3DXMATRIX matFar = matScreeFar * _matInvViewPort_Proj_View;
    const float far0_W = matFar._14;
    const float far1_W = matFar._24;
    const float far2_W = matFar._34;
    const float far3_W = matFar._44;
    D3DXVECTOR3 vecFar0 = D3DXVECTOR3(matFar._11/far0_W, matFar._12/far0_W, matFar._13/far0_W);  //奥左上ワールド座標
    D3DXVECTOR3 vecFar1 = D3DXVECTOR3(matFar._21/far1_W, matFar._22/far1_W, matFar._23/far1_W);  //奥右上ワールド座標
    D3DXVECTOR3 vecFar2 = D3DXVECTOR3(matFar._31/far2_W, matFar._32/far2_W, matFar._33/far2_W);  //奥左下ワールド座標
    D3DXVECTOR3 vecFar3 = D3DXVECTOR3(matFar._41/far3_W, matFar._42/far3_W, matFar._43/far3_W);  //奥右下ワールド座標

    // 視錐台の面を法線正規化して設定
    // 上 ( F左上、N右上、N左上 )
    D3DXPlaneNormalize(
        &_plnTop,
        D3DXPlaneFromPoints(&_plnTop, &(vecFar0), &(vecNear1), &(vecNear0))
    );

    // 下 ( F左下、N左下、N右下 )
   D3DXPlaneNormalize(
       &_plnBottom,
       D3DXPlaneFromPoints(&_plnBottom, &(vecFar2), &(vecNear2), &(vecNear3))
   );

   // 左 ( F左上、N左上、N左下 )
   D3DXPlaneNormalize(
       &_plnLeft,
       D3DXPlaneFromPoints(&_plnLeft, &(vecFar0), &(vecNear0), &(vecNear2))
   );
   // 右 ( F右上、N右下、N右上 )
   D3DXPlaneNormalize(
       &_plnRight,
       D3DXPlaneFromPoints(&_plnRight, &(vecFar1), &(vecNear3), &(vecNear1))
   );
   // 手前 ( N左下、N左上、N右下)
   D3DXPlaneNormalize(
       &_plnInfront,
       D3DXPlaneFromPoints(&_plnInfront, &(vecNear2), &(vecNear0), &(vecNear3))
   );
   // 奥 ( F右下、F左上、F左下)
   D3DXPlaneNormalize(
       &_plnBack,
       D3DXPlaneFromPoints(&_plnBack, &(vecFar3), &(vecFar0), &(vecFar2))
   );

   // 中心垂直面 （ボリュームパンで使用）
   D3DXVECTOR3 vecVerticalCenter0 =
           D3DXVECTOR3(
               (vecFar1.x + vecFar0.x)*0.5f,
               (vecFar1.y + vecFar0.y)*0.5f,
               (vecFar1.z + vecFar0.z)*0.5f
           );
   D3DXVECTOR3 vecVerticalCenter1 =
           D3DXVECTOR3(
               (vecNear3.x + vecNear2.x)*0.5f,
               (vecNear3.y + vecNear2.y)*0.5f,
               (vecNear3.z + vecNear2.z)*0.5f
           );
   D3DXVECTOR3 vecVerticalCenter2 =
           D3DXVECTOR3(
               (vecNear1.x + vecNear0.x)*0.5f,
               (vecNear1.y + vecNear0.y)*0.5f,
               (vecNear1.z + vecNear0.z)*0.5f
           );
    D3DXPlaneNormalize(
        &_plnVerticalCenter,
        D3DXPlaneFromPoints(&_plnVerticalCenter, &(vecVerticalCenter0),
                                                 &(vecVerticalCenter1),
                                                 &(vecVerticalCenter2)
                            )
    );

    //昔のやり方メモ
    //    _vecNear[0].x = x1;  _vecNear[0].y = y1;  _vecNear[0].z = _viewport.MinZ;   // 左下 (変換後)
    //    _vecNear[1].x = x2;  _vecNear[1].y = y1;  _vecNear[1].z = _viewport.MinZ;   // 右下 (変換後)
    //    _vecNear[2].x = x1;  _vecNear[2].y = y2;  _vecNear[2].z = _viewport.MinZ;   // 左上 (変換後)
    //    _vecNear[3].x = x2;  _vecNear[3].y = y2;  _vecNear[3].z = _viewport.MinZ;   // 右上 (変換後)
    //
    //    _vecFar[0].x  = x1;  _vecFar[0].y  = y1;  _vecFar[0].z  = _viewport.MaxZ;   // 左下 (変換後)
    //    _vecFar[1].x  = x2;  _vecFar[1].y  = y1;  _vecFar[1].z  = _viewport.MaxZ;   // 右下 (変換後)
    //    _vecFar[2].x  = x1;  _vecFar[2].y  = y2;  _vecFar[2].z  = _viewport.MaxZ;   // 左上 (変換後)
    //    _vecFar[3].x  = x2;  _vecFar[3].y  = y2;  _vecFar[3].z  = _viewport.MaxZ;   // 右上 (変換後)
    //
    //    // 視錐台の８点の計算
    //    const D3DXMATRIX mat_world = D3DXMATRIX(
    //        1.0f,  0.0f,  0.0f,  0.0f,
    //        0.0f,  1.0f,  0.0f,  0.0f,
    //        0.0f,  0.0f,  1.0f,  0.0f,
    //        0.0f,  0.0f,  0.0f,  1.0f
    //    );
    //    // ワールド → ビュー → 射影 → スクリーン変換 の逆を行う
    //    for ( int i = 0; i < 4; i++ ) {
    //        D3DXVec3Unproject(
    //            &_vecNear[i], //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
    //            &_vecNear[i], //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。
    //            &_viewport,   //CONST D3DVIEWPORT9 *pViewport,  [in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
    //            &_matProj,    //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
    //            &_matView,    //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
    //            &mat_world    //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
    //        );
    //        D3DXVec3Unproject(
    //            &_vecFar[i],
    //            &_vecFar[i],
    //            &_viewport,
    //            &_matProj,
    //            &_matView,
    //            &mat_world
    //        );
    //    }
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
    // VIEW変換行列更新
    D3DXMatrixLookAtLH(&_matView,
                       _pVecCamFromPoint,
                       _pVecCamLookatPoint,
                       _pVecCamUp);
    D3DXMatrixInverse(&_matInvView, nullptr, &_matView);
    _matInvViewPort_Proj_View = _matInvViewPort * _matInvProj * _matInvView;

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
