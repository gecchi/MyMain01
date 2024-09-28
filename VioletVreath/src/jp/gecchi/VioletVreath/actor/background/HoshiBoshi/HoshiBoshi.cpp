#include "HoshiBoshi.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/gecchi/VioletVreath/effect/HoshiboshiEffect.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

coord HoshiBoshi::CAM_ZF_;

HoshiBoshi::HoshiBoshi(const char* prm_name, const char* prm_model) :

                                        GgafDx::PointSpriteActor(prm_name,
                                                               prm_model,
                                                               TYPE_POINTSPRITE_MODEL,
                                                               "HoshiBoshiEffect",
                                                               TYPE_HOSHIBOSHI_EFFECT,
                                                               "HoshiBoshiTechnique") {
    _class_name = "HoshiBoshi";
    effectBlendOne(); //加算合成
    setHitAble(false);

    //独自ワールド変換
    defineRotMvWorldMatrix(HoshiBoshi::setWorldMatrix_HoshiBoshi);
    setSpecialRenderDepthFar(-1); //setSpecialRenderDepthFar(0) は WorldBoundActor
    pCriteria_ = pCARETAKER->getSpacetime()->getCamera();
    setFarRate(1.0);
    static volatile bool is_init = HoshiBoshi::initStatic(this); //静的メンバ初期化
    (void)is_init;
}

bool HoshiBoshi::initStatic(HoshiBoshi* prm_pHoshiBoshi) {
    HoshiBoshi::CAM_ZF_ = ABS(DX_C(pCARETAKER->getSpacetime()->getCamera()->getZFar()));
    return true;
}

void HoshiBoshi::setFarRate(float prm_far_rate) {
    //星々はDIRECTX距離-1.0～1.0（-10px～10px)に収まっている前提で、
    //現空間の大きさに散らばらせる
    far_rate_ = prm_far_rate;
    space_distance_ = HoshiBoshi::CAM_ZF_*far_rate_;
    _sx = _sy = _sz =  (pCARETAKER->getSpacetime()->getCamera()->getZFar()*LEN_UNIT)*far_rate_;
}
int HoshiBoshi::isOutOfView() {
    //画面外判定無し
    return 0;
}

void HoshiBoshi::setCriteriaActor(GgafDx::GeometricActor* prm_pCriteria) {
    pCriteria_ = prm_pCriteria;
}

bool HoshiBoshi::isOutOfSpacetime() const {
    //ゲーム座標範囲外判定無し
    return false;
}

void HoshiBoshi::initialize() {

}

void HoshiBoshi::processSettlementBehavior() {
    if (_x > space_distance_) {
        _x -= (space_distance_*2);
    } else if (_x < -space_distance_) {
        _x += (space_distance_*2);
    }

    if (_y > space_distance_) {
        _y -= (space_distance_*2);
    } else if (_y < -space_distance_) {
        _y += (space_distance_*2);
    }

    if (_z > space_distance_) {
        _z -= (space_distance_*2);
    } else if (_z < -space_distance_) {
        _z += (space_distance_*2);
    }

    //画面外判定無しに伴ない処理簡略化
    //GeometricActor::processSettlementBehavior() と同期を取る事！
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorld); //ワールド変換
}

void HoshiBoshi::processJudgement() {
}

void HoshiBoshi::processDraw() {
    HoshiboshiEffect* pHoshiboshiEffect = (HoshiboshiEffect*)_pPointSpriteEffect;
    ID3DXEffect* const pID3DXEffect = pHoshiboshiEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_fX_MyShip_, pCriteria_->_fX);
    checkDxException(hr, D3D_OK, "SetFloat(h_fX_MyShip_) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_fY_MyShip_, pCriteria_->_fY);
    checkDxException(hr, D3D_OK, "SetFloat(h_fY_MyShip_) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_fZ_MyShip_, pCriteria_->_fZ);
    checkDxException(hr, D3D_OK, "SetFloat(h_fZ_MyShip_) に失敗しました。");
    hr = pID3DXEffect->SetFloat(pHoshiboshiEffect->h_far_rate_, far_rate_);
    checkDxException(hr, D3D_OK, "SetFloat(h_far_rate_) に失敗しました。");
    GgafDx::PointSpriteActor::processDraw();
}


void HoshiBoshi::drawHitArea() {
}

HoshiBoshi::~HoshiBoshi() {
}

void HoshiBoshi::setWorldMatrix_HoshiBoshi(const GgafDx::GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World変換
    //拡大縮小 × X軸回転 × Z軸回転 × Y軸回転 × 平行移動 の変換行列を設定<BR>
    //※XYZの順でないことに注意
    float sinRx = (float)ANG_SIN(prm_pActor->_rx);
    float cosRx = (float)ANG_COS(prm_pActor->_rx);
    float sinRy = (float)ANG_SIN(prm_pActor->_ry);
    float cosRy = (float)ANG_COS(prm_pActor->_ry);
    float sinRz = (float)ANG_SIN(prm_pActor->_rz);
    float cosRz = (float)ANG_COS(prm_pActor->_rz);
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
