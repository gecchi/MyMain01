#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

int GgafDxCamera::_X_ScreenLeft   = 0;
int GgafDxCamera::_X_ScreenRight  = 0;
int GgafDxCamera::_Y_ScreenTop    = 0;
int GgafDxCamera::_Y_ScreenBottom = 0;



GgafDxCamera::GgafDxCamera(const char* prm_name, float prm_rad_fovX, float prm_dep) : GgafDxGeometricActor(prm_name, NULL, NULL) {
    _class_name = "GgafDxCamera";

    //全ての基準はfovXから考える
    _rad_fovX = prm_rad_fovX;
    //半分を保持
    _rad_half_fovX = _rad_fovX / 2.0f;
    //画面アスペクト比(w/h)
    _screen_aspect = (FLOAT)(1.0f * CFG_PROPERTY(GAME_BUFFER_WIDTH) / CFG_PROPERTY(GAME_BUFFER_HEIGHT));
    //fovXとアスペクト比からfovYを計算して求める
    float xzRatio = tan( _rad_fovX/2 );
    float yRatio = xzRatio / _screen_aspect;
    _rad_fovY = atan( yRatio )*2.0f;
    _TRACE_("GgafDxCamera::GgafDxCamera 画面アスペクト："<<_screen_aspect);
    _TRACE_("GgafDxCamera::GgafDxCamera FovX="<<prm_rad_fovX<<" FovY="<<_rad_fovY);

    //半分を保持
    _rad_half_fovY = _rad_fovY / 2.0f;
    //tan値も保持
    _tan_half_fovY = tan(_rad_fovY/2.0);
    _tan_half_fovX = tan(_rad_fovX/2.0);
    //初期カメラ位置は視点(0,0,Z)、注視点(0,0,0)
    //Zは、キャラがZ=0のXY平面で丁度キャラが値ピクセル幅と一致するような所にカメラを引く
    _cameraZ = -1.0f * ((CFG_PROPERTY(GAME_BUFFER_HEIGHT) / PX_UNIT) / 2.0f) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;
    _TRACE_("GgafDxCamera::GgafDxCamera カメラの位置(0,0,"<<_cameraZ<<")");
    _pVecCamFromPoint   = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_cameraZ); //位置
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //注視する方向
    _pVecCamUp          = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //上方向

    // VIEW変換行列作成
    D3DXMatrixLookAtLH(
       &_matView,         // pOut [in, out] 演算結果である D3DXMATRIX 構造体へのポインタ。
        _pVecCamFromPoint,    // pEye [in] 視点を定義する D3DXVECTOR3 構造体へのポインタ。この値は、平行移動に使用される。
        _pVecCamLookatPoint,  // pAt  [in] カメラの注視対象を定義する D3DXVECTOR3 構造体へのポインタ。
        _pVecCamUp            // pUp  [in] カレント ワールドの上方、一般には [0, 1, 0] を定義する D3DXVECTOR3 構造体へのポインタ。
    );

    // 射影変換行列作成（３Ｄ→平面）
    _dep = prm_dep;
    _zn = 0.1f;
    _zf = -_cameraZ_org*(_dep+1.0f);
    _TRACE_("GgafDxCamera::GgafDxCamera 範囲 ["<<_zn<<" ~ "<<_zf<<"]");
    D3DXMatrixPerspectiveFovLH(
            &_matProj,
            _rad_fovY,        //y方向視野角ラディアン(0～π)
            _screen_aspect,   //アスペクト比  640×480 の場合  640/480
            _zn,             //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            _zf              //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
            //(FLOAT)(-1.0f*dCam*4)
            //(-1.0f*fCam)-30,
            //(-1.0f*fCam)+30
    );
    /*
     //左手座標系正射影
     D3DXMatrixOrthoLH(
     &_matProj,
     CFG_PROPERTY(GAME_BUFFER_WIDTH),
     CFG_PROPERTY(GAME_BUFFER_HEIGHT),
     1.0f,
     CFG_PROPERTY(GAME_BUFFER_HEIGHT)
     );
     */
    locate(0, 0, Dx2Co(_cameraZ));
    _pKurokoA->setMvAng(0,0,0);
    _pKurokoA->setMvVelo(0);
    _pKurokoA->setRzMvAngVelo(0);
    _pKurokoA->setRyMvAngVelo(0);
    _pKurokoA->_mv_ang_rz_target_flg = true;
    _pKurokoA->_mv_ang_ry_target_flg = true;
    setHitAble(false);

    _pViewPoint = NEW GgafDxCameraViewPoint();
    _pViewPoint->locate(0, 0, 0);

    _X_ScreenLeft   = Px2Co(CFG_PROPERTY(GAME_BUFFER_WIDTH)) / -2;
    _X_ScreenRight  = Px2Co(CFG_PROPERTY(GAME_BUFFER_WIDTH)) / 2;
    _Y_ScreenTop    = Px2Co(CFG_PROPERTY(GAME_BUFFER_HEIGHT)) / 2;
    _Y_ScreenBottom = Px2Co(CFG_PROPERTY(GAME_BUFFER_HEIGHT)) / -2;
    GgafDxGod::_pID3DDevice9->GetViewport(&_viewport);
}

void GgafDxCamera::initialize() {
    addSubLast(_pViewPoint);
}

void GgafDxCamera::processBehavior() {
    //if (_frame_of_behaving % 2 == 0) { //10フレームに１回だけ計算
    //スクリーン全体のクライアント領域を保持。

    // _viewport.MinZ / MaxZ は、通常それぞれ 0 / 1
    dxcoord x1 = dxcoord(_viewport.X);
    dxcoord y1 = dxcoord(_viewport.Y);
    dxcoord x2 = dxcoord(_viewport.X + _viewport.Width);
    dxcoord y2 = dxcoord(_viewport.Y + _viewport.Height);

    // 視錐台の８点が格納されるインスタンス
    _vecNear[0] = D3DXVECTOR3( x1, y1, _viewport.MinZ ); // 左下 (変換後)
    _vecNear[1] = D3DXVECTOR3( x2, y1, _viewport.MinZ ); // 右下 (変換後)
    _vecNear[2] = D3DXVECTOR3( x1, y2, _viewport.MinZ ); // 左上 (変換後)
    _vecNear[3] = D3DXVECTOR3( x2, y2, _viewport.MinZ ); // 右上 (変換後)

    _vecFar[0]  = D3DXVECTOR3( x1, y1, _viewport.MaxZ ); // 左下 (変換後)
    _vecFar[1]  = D3DXVECTOR3( x2, y1, _viewport.MaxZ ); // 右下 (変換後)
    _vecFar[2]  = D3DXVECTOR3( x1, y2, _viewport.MaxZ ); // 左上 (変換後)
    _vecFar[3]  = D3DXVECTOR3( x2, y2, _viewport.MaxZ ); // 右上 (変換後)

    // 視錐台の８点の計算
    static D3DXMATRIX mat_world;
    D3DXMatrixIdentity( &mat_world );
    // ワールド → ビュー → 射影 → スクリーン変換 の逆を行う
    for( int i = 0; i < 4; ++i ) {
        D3DXVec3Unproject(
            &_vecNear[i],   //D3DXVECTOR3 *pOut,              [in, out] 演算結果である D3DXVECTOR3 構造体へのポインタ。
            &_vecNear[i],   //CONST D3DXVECTOR3 *pV,          [in] 処理の基になる D3DXVECTOR3 構造体へのポインタ。
            &_viewport,      //CONST D3DVIEWPORT9 *pViewport,[in] ビューポートを表す D3DVIEWPORT9 構造体へのポインタ。
            &_matProj,  //CONST D3DXMATRIX *pProjection,  [in] 射影行列を表す D3DXMATRIX 構造体へのポインタ。
            &_matView,  //CONST D3DXMATRIX *pView,        [in] ビュー行列を表す D3DXMATRIX 構造体へのポインタ。
            &mat_world      //CONST D3DXMATRIX *pWorld        [in] ワールド行列を表す D3DXMATRIX 構造体へのポインタ。
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

    // 中心垂直面 （ボリュームパンで使用）
    _vecVerticalCenter[0] = D3DXVECTOR3( (_vecFar[1].x + _vecFar[0].x)/2.0,
                                         (_vecFar[1].y + _vecFar[0].y)/2.0,
                                         (_vecFar[1].z + _vecFar[0].z)/2.0
                                       );
    _vecVerticalCenter[1] = D3DXVECTOR3( (_vecNear[3].x + _vecNear[2].x)/2.0,
                                         (_vecNear[3].y + _vecNear[2].y)/2.0,
                                         (_vecNear[3].z + _vecNear[2].z)/2.0
                                       );
    _vecVerticalCenter[2] = D3DXVECTOR3( (_vecNear[1].x + _vecNear[0].x)/2.0,
                                         (_vecNear[1].y + _vecNear[0].y)/2.0,
                                         (_vecNear[1].z + _vecNear[0].z)/2.0
                                       );
    D3DXPlaneNormalize(
        &_plnVerticalCenter,
        D3DXPlaneFromPoints(&_plnVerticalCenter, &(_vecVerticalCenter[0]),
                                                 &(_vecVerticalCenter[1]),
                                                 &(_vecVerticalCenter[2])
                            )
    );

    //}

//    xaxis.x           yaxis.x           zaxis.x          0
//    xaxis.y           yaxis.y           zaxis.y          0
//    xaxis.z           yaxis.z           zaxis.z          0
//   -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1


    //_TRACE_(_matView._14<<","<<_matView._24<<","<<_matView._34);

}



void GgafDxCamera::processJudgement() {
    _pVecCamFromPoint->x = _fX;
    _pVecCamFromPoint->y = _fY;
    _pVecCamFromPoint->z = _fZ;
    _pVecCamLookatPoint->x = Co2Dx(_pViewPoint->_X);
    _pVecCamLookatPoint->y = Co2Dx(_pViewPoint->_Y);
    _pVecCamLookatPoint->z = Co2Dx(_pViewPoint->_Z);
    D3DXMatrixLookAtLH(&_matView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
}

void GgafDxCamera::setViewPoint(coord prm_tX, coord prm_tY, coord prm_tZ) {
    _pViewPoint->_X = prm_tX;
    _pViewPoint->_Y = prm_tY;
    _pViewPoint->_Z = prm_tZ;
}

void GgafDxCamera::setViewPoint(GgafDxGeometricActor* prm_pActor) {
    _pViewPoint->locateAs(prm_pActor);
}


void GgafDxCamera::setDefaultPosition() {
    _X = 0;
    _Y = 0;
    _Z = Dx2Co(_cameraZ_org);
    _pViewPoint->_X = 0;
    _pViewPoint->_Y = 0;
    _pViewPoint->_Z = 0;
    _pVecCamUp->x = 0.0f;
    _pVecCamUp->y = 1.0f;
    _pVecCamUp->z = 0.0f;
}


GgafDxCamera::~GgafDxCamera() {
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);
}
