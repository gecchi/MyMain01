#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteActor::GgafDxSpriteActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_effect_id,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                         GgafDxDrawableActor(prm_name,
                                                             prm_model_id,
                                                             "S",
                                                             prm_effect_id,
                                                             "S",
                                                             prm_technique,
                                                             prm_pStat,
                                                             prm_pChecker) {
    _obj_class |= Obj_GgafDxSpriteActor;
    _class_name = "GgafDxSpriteActor";

    _pSpriteModel = (GgafDxSpriteModel*)_pModel;
    _pSpriteEffect = (GgafDxSpriteEffect*)_pEffect;
//    _pUvFlipper = NEW GgafDxUvFlipper(this);
//    _pUvFlipper->forcePtnNoRange(0, _pSpriteModel->_pattno_uvflip_Max);
//    _pUvFlipper->setActivePtnNo(0);
//    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    GgafDxTexture* pTexture = _pSpriteModel->_papTextureCon[0]->use();
    _pUvFlipper = NEW GgafDxUvFlipper(pTexture);
    _pUvFlipper->setRotation(_pSpriteModel->_col_texture_split,
                             _pSpriteModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pFunc_calcRotMvWorldMatrix = GgafDxUtil::setWorldMatrix_RxRzRyMv;
    _far_rate = -1.0f;
}

void GgafDxSpriteActor::processDraw() {
    ID3DXEffect* pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matView, &P_CAM->_matView );
//    checkDxException(hr, D3D_OK, "GgafDxMeshActor::GgafDxMeshEffect SetMatrix(g_matView) に失敗しました。");
    //(*_pFunc_calcRotMvWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDxSpriteActor::processDraw SetMatrix(_h_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_hAlpha, _fAlpha);
    checkDxException(hr, D3D_OK, "GgafDxSpriteActor::processDraw SetFloat(_fAlpha) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "GgafDxMeshActor::processDraw() SetFloat(_h_far_rate) に失敗しました。");
    _pSpriteModel->draw(this);
}

void GgafDxSpriteActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _fAlpha;
    _paMaterial[0].Diffuse.a = _fAlpha;
}

void GgafDxSpriteActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _fAlpha;
    _paMaterial[0].Diffuse.a = _fAlpha;
}


GgafDxSpriteActor::~GgafDxSpriteActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
