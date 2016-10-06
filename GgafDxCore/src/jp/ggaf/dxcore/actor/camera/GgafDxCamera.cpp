#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"

#include "jp/ggaf/dxcore/GgafDxProperties.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxKuroko.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraUpVector.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxCamera::GgafDxCamera(const char* prm_name, double prm_rad_fovX, double prm_dep) :
        GgafDxGeometricActor(prm_name, nullptr, nullptr),
_rad_fovX(prm_rad_fovX),      //全ての基準はfovXから考える
_dep(prm_dep),
_rad_half_fovX(_rad_fovX / 2.0),
_screen_aspect(1.0 * (PROPERTY::GAME_BUFFER_WIDTH) / (PROPERTY::GAME_BUFFER_HEIGHT)),
_rad_fovY(atan( ( (tan(_rad_fovX/2.0)) / _screen_aspect) )*2.0),
_rad_half_fovY(_rad_fovY / 2.0),
_tan_half_fovX(tan(_rad_fovX/2.0)),
_tan_half_fovY(tan(_rad_fovY/2.0)),
_cameraZ_org(-1.0 * ((1.0 * (PROPERTY::GAME_BUFFER_HEIGHT) / PX_UNIT) / 2.0) / _tan_half_fovY),
_zn(0.1f),
_zf(-_cameraZ_org*(_dep+1.0)),
_x_buffer_left(PX_C(PROPERTY::GAME_BUFFER_WIDTH) / -2),
_x_buffer_right(PX_C(PROPERTY::GAME_BUFFER_WIDTH) / 2),
_y_buffer_top(PX_C(PROPERTY::GAME_BUFFER_HEIGHT) / 2),
_y_buffer_bottom(PX_C(PROPERTY::GAME_BUFFER_HEIGHT) / -2)
{
    _class_name = "GgafDxCamera";
    //fovXとアスペクト比からfovYを計算して求める
    _TRACE_(FUNC_NAME<<" 画面アスペクト："<<_screen_aspect);
    _TRACE_(FUNC_NAME<<" FovX="<<prm_rad_fovX<<" FovY="<<_rad_fovY);


    //初期カメラ位置は視点(0,0,Z)、注視点(0,0,0)
    //Zは、キャラがZ=0のXY平面で丁度キャラが値ピクセル幅と一致するような所にカメラを引く
    _TRACE_(FUNC_NAME<<" カメラの位置(0,0,"<<_cameraZ_org<<")");
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


    _TRACE_(FUNC_NAME<<" 範囲 ["<<_zn<<" ~ "<<_zf<<"]");
    if (PROPERTY::PRJ_2D_MODE) {
        //2Dモード正射影
        D3DXMatrixOrthoLH(
            &_matProj,
            PX_DX(PROPERTY::GAME_BUFFER_WIDTH),
            PX_DX(PROPERTY::GAME_BUFFER_HEIGHT),
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

    locate(0, 0, DX_C(_cameraZ_org));
    setFaceAngTwd(0,0,0);
    getKuroko()->setMvAngTwd(0,0,0);
    setHitAble(false);

    GgafDxGod::_pID3DDevice9->GetViewport(&_viewport);

    _x_prev = 0;
    _y_prev = 0;
    _z_prev = 0;

    _pCameraViewPoint = nullptr;
    _pCameraUpVector = nullptr;
}

void GgafDxCamera::initialize() {
    getCameraViewPoint();
    getCameraUpVector();
}

void GgafDxCamera::processBehavior() {
    //if (isMoving() || _pCameraViewPoint->isMoving()) {
        //if (_frame_of_behaving % 2 == 0) { //10フレームに１回だけ計算
        //スクリーン全体のクライアント領域を保持。

        // _viewport.MinZ / MaxZ は、通常それぞれ 0 / 1
        const dxcoord x1 = dxcoord(_viewport.X);
        const dxcoord y1 = dxcoord(_viewport.Y);
        const dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
        const dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);

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
        for( int i = 0; i < 4; i++ ) {
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
    //}

}

void GgafDxCamera::processJudgement() {
    _x_prev = _x;
    _y_prev = _y;
    _z_prev = _z;

    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    GgafDxCameraViewPoint* pVp = getCameraViewPoint();
    _pVecCamLookatPoint->x = pVp->_fX;
    _pVecCamLookatPoint->y = pVp->_fY;
    _pVecCamLookatPoint->z = pVp->_fZ;
    GgafDxCameraUpVector* pUpv = getCameraUpVector();
    _pVecCamUp->x = pUpv->_fX;
    _pVecCamUp->y = pUpv->_fY;
    _pVecCamUp->z = pUpv->_fZ;
    D3DXMatrixLookAtLH(&_matView,
                       _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}

GgafDxCameraViewPoint* GgafDxCamera::getCameraViewPoint() {
    if (_pCameraViewPoint) {
        return _pCameraViewPoint;
    } else {
        _pCameraViewPoint = createCameraViewPoint();
        _pCameraViewPoint->locate(0, 0, 0);
        addSubGroup(_pCameraViewPoint);
        return _pCameraViewPoint;
    }
}

GgafDxCameraUpVector* GgafDxCamera::getCameraUpVector() {
    if (_pCameraUpVector) {
        return _pCameraUpVector;
    } else {
        _pCameraUpVector = createCameraUpVector();
        _pCameraUpVector->locate(0, PX_C(1), 0);
        addSubGroup(_pCameraUpVector);
        return _pCameraUpVector;
    }
}

void GgafDxCamera::setDefaultPosition() {
    _x = 0;
    _y = 0;
    _z = DX_C(_cameraZ_org);
    GgafDxCameraViewPoint* pVp = getCameraViewPoint();
    pVp->locate(0, 0, 0);
    GgafDxCameraUpVector* pUpv = getCameraUpVector();
    pUpv->locate(0, PX_C(1), 0);
}

bool GgafDxCamera::isMoving() {
    if (_x_prev == _x && _y_prev == _y && _z_prev == _z) {
        return false;
    } else {
        return true;
    }
}

void GgafDxCamera::setCamUpVecByFaceNo(dir26 prm_face_no) {
    GgafDxCameraUpVector* pUpv = getCameraUpVector();
    pUpv->locateByFaceNo(prm_face_no);
}

GgafDxCamera::~GgafDxCamera() {
    GGAF_DELETE(_pVecCamFromPoint);
    GGAF_DELETE(_pVecCamLookatPoint);
    GGAF_DELETE(_pVecCamUp);
}
