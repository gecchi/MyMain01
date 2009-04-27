#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9Camera::GgafDx9Camera(const char* prm_name) : GgafDx9UntransformedActor(prm_name, NEW GgafDx9GeometryMover(this), NULL) {
    _class_name = "GgafDx9Camera";

//    D3DXVECTOR3* GgafDx9God::_pVecCamFromPoint = NULL;
//    D3DXVECTOR3* GgafDx9God::_pVecCamLookatPoint = NULL;
//    D3DXVECTOR3* GgafDx9God::_pVecCamUp = NULL;
//    D3DXMATRIX GgafDx9God::_vMatrixView;
//    D3DXMATRIX GgafDx9God::_vMatrixProj;
//    D3DXMATRIX GgafDx9God::_vMatrixOrthoProj;


    _rad_fovY = PI / 6;


    _tan_half_fovY = tan(_rad_fovY/2);
    _cameraZ = -1.0 * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0) / _tan_half_fovY;
    _cameraZ_org = _cameraZ;

    //_iPxDep = abs(_cameraZ_org * PX_UNIT * 2);

    _TRACE_("カメラの位置(0,0,"<<_cameraZ<<")");

    _screen_aspect = (FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT));

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
            _rad_fovY, //y方向視野角ラディアン(0〜π)
            _screen_aspect, //アスペクト比  640×480 の場合  640/480
            1.0, //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            2000.0 //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
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

    _pGeoMover->setMoveAngle(0,0,0);
    _pGeoMover->setMoveVelocity(0);
    _pGeoMover->setRzMoveAngleVelocity(0);
    _pGeoMover->setRyMoveAngleVelocity(0);
    _pGeoMover->_auto_move_angle_rz_target_flg = true;
    _pGeoMover->_auto_move_angle_ry_target_flg = true;

    setBumpable(false);
}

void GgafDx9Camera::initialize() {

}




void GgafDx9Camera::processBehavior() {
    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
    _pGeoMover->behave();
//    D3DXMatrixOrthoLH(
//        &_vMatrixOrthoProj,
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)) ,    //w ビュー ボリュームの幅
//        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) ,   //h ビュー ボリュームの高さ
//        1.0,    //zn ビュー ボリュームの最小 z 値 (z 近ともいう)
//        2000.0  //zf ビュー ボリュームの最大 z 値 (z 遠ともいう)
//    );

}

void GgafDx9Camera::processDrawPrior() {
    _pVecCamFromPoint->x = (1.0 * _X) / LEN_UNIT / PX_UNIT;
    _pVecCamFromPoint->y = (1.0 * _Y) / LEN_UNIT / PX_UNIT;
    _pVecCamFromPoint->z = (1.0 * _Z) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->x = (1.0 * _gazeX) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->y = (1.0 * _gazeY) / LEN_UNIT / PX_UNIT;
    _pVecCamLookatPoint->z = (1.0 * _gazeZ) / LEN_UNIT / PX_UNIT;
}

GgafDx9Camera::~GgafDx9Camera() {
    //いろいろ解放
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

}
