#include "stdafx.h"
#include "HoshiBoshi.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteEffect.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


HoshiBoshi::HoshiBoshi(const char* prm_name, const char* prm_model_id) :
        GgafDxPointSpriteActor(prm_name,
                               prm_model_id,
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               nullptr,
                               nullptr ) {
    _class_name = "HoshiBoshi";
    h_fX_MyShip_  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_fX_MyShip" );
    h_fY_MyShip_  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_fY_MyShip" );
    h_fZ_MyShip_  = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_fZ_MyShip" );
    h_far_rate_   = _pPointSpriteEffect->_pID3DXEffect->GetParameterByName( nullptr, "g_far_rate" );
    effectBlendOne(); //加算合成
    setHitAble(false);
    CAM_ZF_ = ABS(DX_C(P_CAM->_zf));
    _TRACE_("HoshiBoshi::HoshiBoshi CAM_ZF_="<<CAM_ZF_);
    //独自ワールド変換
    defineRotMvWorldMatrix(HoshiBoshi::setWorldMatrix_HoshiBoshi);
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_HOSHIBOSHI);
    //星々はDIRECTX距離-1.0～1.0（-10px～10px)に収まっている前提で、
    //現空間の大きさに散らばらせる
    far_rate_ = 30.0f;
    _sx = _sy = _sz =  (P_CAM->_zf*LEN_UNIT)*far_rate_;
}

int HoshiBoshi::isOutOfView() {
    //画面外判定無し
    return 0;
}

bool HoshiBoshi::isOutOfUniverse() {
    //ゲーム座標範囲外判定無し
    return false;
}
void HoshiBoshi::initialize() {

}

void HoshiBoshi::onActive() {
    getUvFlipper()->exec(FLIP_ORDER_LOOP, 6);
}

void HoshiBoshi::processBehavior() {
    if (_x < -CAM_ZF_*far_rate_) {
        _x += (CAM_ZF_*far_rate_*2);
    } else {
        _x -= 1000*far_rate_;
    }
    getUvFlipper()->behave();
}

void HoshiBoshi::processSettlementBehavior() {
    //画面外判定無しに伴ない処理簡略化
    //GgafDxGeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    (*_pFunc_calcRotMvWorldMatrix)(this, _matWorld); //ワールド変換
}

void HoshiBoshi::processJudgement() {
}

void HoshiBoshi::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(h_fX_MyShip_, P_MYSHIP->_fX);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fX_MyShip_) に失敗しました。");
    hr = pID3DXEffect->SetFloat(h_fY_MyShip_, P_MYSHIP->_fY);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fY_MyShip_) に失敗しました。");
    hr = pID3DXEffect->SetFloat(h_fZ_MyShip_, P_MYSHIP->_fZ);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fZ_MyShip_) に失敗しました。");
    hr = pID3DXEffect->SetFloat(h_far_rate_, far_rate_);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_far_rate_) に失敗しました。");
    GgafDxPointSpriteActor::processDraw();
}


void HoshiBoshi::drawHitArea() {
}

HoshiBoshi::~HoshiBoshi() {
}

void HoshiBoshi::setWorldMatrix_HoshiBoshi(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    float sinRx = ANG_SIN(prm_pActor->_rx);
    float cosRx = ANG_COS(prm_pActor->_rx);
    float sinRy = ANG_SIN(prm_pActor->_ry);
    float cosRy = ANG_COS(prm_pActor->_ry);
    float sinRz = ANG_SIN(prm_pActor->_rz);
    float cosRz = ANG_COS(prm_pActor->_rz);
    float sx = SC_R(prm_pActor->_sx);
    float sy = SC_R(prm_pActor->_sy);
    float sz = SC_R(prm_pActor->_sz);

    out_matWorld._11 = sx * cosRz *cosRy;
    out_matWorld._12 = sx * sinRz;
    out_matWorld._13 = sx * cosRz * -sinRy;
    out_matWorld._14 = 0.0f;

    out_matWorld._21 = (sy * cosRx * -sinRz *  cosRy) + (sy * sinRx * sinRy);
    out_matWorld._22 = sy * cosRx *  cosRz;
    out_matWorld._23 = (sy * cosRx * -sinRz * -sinRy) + (sy * sinRx * cosRy);
    out_matWorld._24 = 0.0f;

    out_matWorld._31 = (sz * -sinRx * -sinRz *  cosRy) + (sz * cosRx * sinRy);
    out_matWorld._32 = sz * -sinRx *  cosRz;
    out_matWorld._33 = (sz * -sinRx * -sinRz * -sinRy) + (sz * cosRx * cosRy);
    out_matWorld._34 = 0.0f;

    out_matWorld._41 = prm_pActor->_fX;
    out_matWorld._42 = prm_pActor->_fY;
    out_matWorld._43 = prm_pActor->_fZ;
    out_matWorld._44 = 1.0f;
}
