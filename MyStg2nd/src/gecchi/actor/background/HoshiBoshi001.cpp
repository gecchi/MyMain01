#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;



HoshiBoshi001::HoshiBoshi001(const char* prm_name) :
        GgafDx9PointSpriteActor(prm_name,
                               "HoshiBoshi001",
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               NULL,
                               NULL ) {
    _class_name = "HoshiBoshi001";
    _h_fX_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fX_MyShip" );
    _h_fY_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fY_MyShip" );
    _h_fZ_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fZ_MyShip" );
    _h_far_rate   = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_far_rate" );
    changeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false);
    _CAM_ZF = abs(Dx2App(P_CAM->_zf));
    _TRACE_("HoshiBoshi001::HoshiBoshi001 _CAM_ZF="<<_CAM_ZF);
    //独自ワールド変換
    defineRotMvWorldMatrix(HoshiBoshi001::setWorldMatrix_HoshiBoshi001);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-3);//最深部
    //星はDIRECTX距離-1.0～1.0（-10px～10px)に収まっている前提で、
    //現空間の大きさに散らばらせる
    _far_rate = 30.0f;
    _SX = _SY = _SZ =  (P_CAM->_zf*LEN_UNIT)*_far_rate;
}

int HoshiBoshi001::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool HoshiBoshi001::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}
void HoshiBoshi001::initialize() {

}

void HoshiBoshi001::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshi001::processBehavior() {
    if (_X < -_CAM_ZF*_far_rate) {
        _X += (_CAM_ZF*_far_rate*2);
    } else {
        _X -= 1000*_far_rate;
    }
    _pUvFlipper->behave();
}

void HoshiBoshi001::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDx9GeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = App2Dx(_X);
    _fY = App2Dx(_Y);
    _fZ = App2Dx(_Z);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //ワールド変換
}

void HoshiBoshi001::processJudgement() {
}

void HoshiBoshi001::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_h_fX_MyShip, P_MYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_fX_MyShip) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_fY_MyShip, P_MYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_fY_MyShip) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_fZ_MyShip, P_MYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_fZ_MyShip) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_far_rate, _far_rate);
    checkDxException(hr, D3D_OK, "GgafDx9PointSpriteActor::processDraw() SetFloat(_h_far_rate) に失敗しました。");

    GgafDx9PointSpriteActor::processDraw();
}


void HoshiBoshi001::drawHitArea() {
}

HoshiBoshi001::~HoshiBoshi001() {
}

void HoshiBoshi001::setWorldMatrix_HoshiBoshi001(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    float sinRx = cnvAppang2Sin(prm_pActor->_RX);
    float cosRx = cnvAppang2Cos(prm_pActor->_RX);
    float sinRy = cnvAppang2Sin(prm_pActor->_RY);
    float cosRy = cnvAppang2Cos(prm_pActor->_RY);
    float sinRz = cnvAppang2Sin(prm_pActor->_RZ);
    float cosRz = cnvAppang2Cos(prm_pActor->_RZ);
    float Sx = cnvScaleApp2Rate(prm_pActor->_SX);
    float Sy = cnvScaleApp2Rate(prm_pActor->_SY);
    float Sz = cnvScaleApp2Rate(prm_pActor->_SZ);

    out_matWorld._11 = Sx * cosRz *cosRy;
    out_matWorld._12 = Sx * sinRz;
    out_matWorld._13 = Sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (Sy * cosRx * -sinRz *  cosRy) + (Sy * sinRx * sinRy);
    out_matWorld._22 = Sy * cosRx *  cosRz;
    out_matWorld._23 = (Sy * cosRx * -sinRz * -sinRy) + (Sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (Sz * -sinRx * -sinRz *  cosRy) + (Sz * cosRx * sinRy);
    out_matWorld._32 = Sz * -sinRx *  cosRz;
    out_matWorld._33 = (Sz * -sinRx * -sinRz * -sinRy) + (Sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
