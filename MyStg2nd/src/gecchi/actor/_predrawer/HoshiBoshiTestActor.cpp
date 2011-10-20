#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace MyStg2nd;



HoshiBoshiTestActor::HoshiBoshiTestActor(const char* prm_name) :
        GgafDxPointSpriteActor(prm_name,
                               "_chk_HoshiBoshiTestModel",
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               NULL,
                               NULL ) {
    _class_name = "HoshiBoshiTestActor";
    _h_fX_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fX_MyShip" );
    _h_fY_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fY_MyShip" );
    _h_fZ_MyShip  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( NULL, "g_fZ_MyShip" );

    changeEffectTechnique("DestBlendOne"); //加算合成
    setHitAble(false);
    _CAM_ZF = abs(P_CAM->_zf * PX_UNIT * LEN_UNIT);
    _TRACE_("HoshiBoshiTestActor::HoshiBoshiTestActor _CAM_ZF="<<_CAM_ZF);
    //独自ワールド変換
    defineRotMvWorldMatrix(HoshiBoshiTestActor::setWorldMatrix_HoshiBoshiTestActor);
    setSpecialDrawDepth(MAX_DRAW_DEPTH_LEVEL-10);//最深部の次くらいに・・
    //星はDIRECTX距離-1.0～1.0に収まっている前提で、
    //現空間の大きさに散らばらせる
    _SX = _SY = _SZ =  P_CAM->_zf*1000;
}

int HoshiBoshiTestActor::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool HoshiBoshiTestActor::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}
void HoshiBoshiTestActor::initialize() {

}

void HoshiBoshiTestActor::onActive() {
    _pUvFlipper->setFlipMethod(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshiTestActor::processBehavior() {
    if (_X < -_CAM_ZF) {
        _X += (_CAM_ZF*2);
    } else {
        _X -= 1000;
    }
    _pUvFlipper->behave();
}

void HoshiBoshiTestActor::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = CO2DX(_X);
    _fY = CO2DX(_Y);
    _fZ = CO2DX(_Z);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //ワールド変換
}

void HoshiBoshiTestActor::processJudgement() {
}

void HoshiBoshiTestActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(_h_fX_MyShip, P_MYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(_h_fX_MyShip) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_fY_MyShip, P_MYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(_h_fY_MyShip) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_fZ_MyShip, P_MYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(_h_fZ_MyShip) に失敗しました。");
    GgafDxPointSpriteActor::processDraw();
}


void HoshiBoshiTestActor::drawHitArea() {
}

HoshiBoshiTestActor::~HoshiBoshiTestActor() {
}

void HoshiBoshiTestActor::setWorldMatrix_HoshiBoshiTestActor(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    float sinRx = ANG2SIN(prm_pActor->_RX);
    float cosRx = ANG2COS(prm_pActor->_RX);
    float sinRy = ANG2SIN(prm_pActor->_RY);
    float cosRy = ANG2COS(prm_pActor->_RY);
    float sinRz = ANG2SIN(prm_pActor->_RZ);
    float cosRz = ANG2COS(prm_pActor->_RZ);
    float Sx = SC2R(prm_pActor->_SX);
    float Sy = SC2R(prm_pActor->_SY);
    float Sz = SC2R(prm_pActor->_SZ);

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
