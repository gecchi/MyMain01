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

D3DXHANDLE HoshiBoshi::h_fX_MyShip_;
D3DXHANDLE HoshiBoshi::h_fY_MyShip_;
D3DXHANDLE HoshiBoshi::h_fZ_MyShip_;
D3DXHANDLE HoshiBoshi::h_far_rate_;
coord HoshiBoshi::CAM_ZF_;
bool HoshiBoshi::is_init_ = false;


HoshiBoshi::HoshiBoshi(const char* prm_name, const char* prm_model_id) :
        GgafDxPointSpriteActor(prm_name,
                               prm_model_id,
                               "HoshiBoshiEffect",
                               "HoshiBoshiTechnique",
                               nullptr,
                               nullptr ) {
    _class_name = "HoshiBoshi";
    if (!HoshiBoshi::is_init_) {
        ID3DXEffect* pID3DXEffect = getEffect()->_pID3DXEffect;
        HoshiBoshi::h_fX_MyShip_ = pID3DXEffect->GetParameterByName( nullptr, "g_fX_MyShip" );
        HoshiBoshi::h_fY_MyShip_ = pID3DXEffect->GetParameterByName( nullptr, "g_fY_MyShip" );
        HoshiBoshi::h_fZ_MyShip_ = pID3DXEffect->GetParameterByName( nullptr, "g_fZ_MyShip" );
        HoshiBoshi::h_far_rate_  = pID3DXEffect->GetParameterByName( nullptr, "g_far_rate" );
        HoshiBoshi::CAM_ZF_ = ABS(DX_C(P_CAM->getZFar()));
        HoshiBoshi::is_init_ = true;
    }
    effectBlendOne(); //‰ÁZ‡¬
    setHitAble(false);

    //“Æ©ƒ[ƒ‹ƒh•ÏŠ·
    defineRotMvWorldMatrix(HoshiBoshi::setWorldMatrix_HoshiBoshi);
    setSpecialDrawDepth(DRAW_DEPTH_LEVEL_HOSHIBOSHI);
    pCriteria_ = P_CAM;
    setFarRate(1.0);
}
void HoshiBoshi::setFarRate(float prm_far_rate) {
    //¯X‚ÍDIRECTX‹——£-1.0`1.0i-10px`10px)‚Éû‚Ü‚Á‚Ä‚¢‚é‘O’ñ‚ÅA
    //Œ»‹óŠÔ‚Ì‘å‚«‚³‚ÉU‚ç‚Î‚ç‚¹‚é
    far_rate_ = prm_far_rate;
    space_distance_ = HoshiBoshi::CAM_ZF_*far_rate_;
    _sx = _sy = _sz =  (P_CAM->getZFar()*LEN_UNIT)*far_rate_;
}
int HoshiBoshi::isOutOfView() {
    //‰æ–ÊŠO”»’è–³‚µ
    return 0;
}

void HoshiBoshi::setCriteriaActor(GgafDxGeometricActor* prm_pCriteria) {
    pCriteria_ = prm_pCriteria;
}

bool HoshiBoshi::isOutOfUniverse() const {
    //ƒQ[ƒ€À•W”ÍˆÍŠO”»’è–³‚µ
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

    //‰æ–ÊŠO”»’è–³‚µ‚É”º‚È‚¢ˆ—ŠÈ—ª‰»
    //GgafDxGeometricActor::processSettlementBehavior() ‚Æ“¯Šú‚ğæ‚é–I
    _fX = C_DX(_x);
    _fY = C_DX(_y);
    _fZ = C_DX(_z);
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorld); //ƒ[ƒ‹ƒh•ÏŠ·
}

void HoshiBoshi::processJudgement() {
}

void HoshiBoshi::processDraw() {
    ID3DXEffect* pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetFloat(HoshiBoshi::h_fX_MyShip_, pCriteria_->_fX);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fX_MyShip_) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(HoshiBoshi::h_fY_MyShip_, pCriteria_->_fY);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fY_MyShip_) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(HoshiBoshi::h_fZ_MyShip_, pCriteria_->_fZ);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_fZ_MyShip_) ‚É¸”s‚µ‚Ü‚µ‚½B");
    hr = pID3DXEffect->SetFloat(HoshiBoshi::h_far_rate_, far_rate_);
    checkDxException(hr, D3D_OK, "GgafDxPointSpriteActor::processDraw() SetFloat(h_far_rate_) ‚É¸”s‚µ‚Ü‚µ‚½B");
    GgafDxPointSpriteActor::processDraw();
}


void HoshiBoshi::drawHitArea() {
}

HoshiBoshi::~HoshiBoshi() {
}

void HoshiBoshi::setWorldMatrix_HoshiBoshi(const GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld) {
    //World•ÏŠ·
    //Šg‘åk¬ ~ X²‰ñ“] ~ Z²‰ñ“] ~ Y²‰ñ“] ~ •½sˆÚ“® ‚Ì•ÏŠ·s—ñ‚ğİ’è<BR>
    //¦XYZ‚Ì‡‚Å‚È‚¢‚±‚Æ‚É’ˆÓ
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
