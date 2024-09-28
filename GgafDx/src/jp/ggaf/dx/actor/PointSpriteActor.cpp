#include "jp/ggaf/dx/actor/PointSpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/PointSpriteEffect.h"
#include "jp/ggaf/dx/model/PointSpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"


using namespace GgafDx;

PointSpriteActor::PointSpriteActor(const char* prm_name,
                                   const char* prm_model,
                                   const char* prm_effect_id,
                                   const char* prm_technique) :

                                       FigureActor(prm_name,
                                                   prm_model,
                                                   TYPE_POINTSPRITE_MODEL,
                                                   prm_effect_id,
                                                   TYPE_POINTSPRITE_EFFECT,
                                                   prm_technique),
_pPointSpriteModel((PointSpriteModel*)_pModel),
_pPointSpriteEffect((PointSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_PointSpriteActor;
    _class_name = "PointSpriteActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pUvFlipper->locatePatternNo(_pPointSpriteModel->_texture_split_rowcol,
                                 _pPointSpriteModel->_texture_split_rowcol );
    setZEnableDraw(false);
    setZWriteEnable(false);
}

PointSpriteActor::PointSpriteActor(const char* prm_name,
                                   const char* prm_model,
                                   const char prm_model_type,
                                   const char* prm_effect_id,
                                   const char prm_effect_type,
                                   const char* prm_technique) :

                                       FigureActor(prm_name,
                                                   prm_model,
                                                   prm_model_type,
                                                   prm_effect_id,
                                                   prm_effect_type,
                                                   prm_technique),
_pPointSpriteModel((PointSpriteModel*)_pModel),
_pPointSpriteEffect((PointSpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_PointSpriteActor;
    _class_name = "PointSpriteActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pUvFlipper->locatePatternNo(_pPointSpriteModel->_texture_split_rowcol,
                                 _pPointSpriteModel->_texture_split_rowcol );
    setZEnableDraw(false);
    setZWriteEnable(false);
}
void PointSpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pPointSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pPointSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
    //hr = pID3DXEffect->SetFloat(_pPointSpriteEffect->_h_dist_VpInfrontPlane, -_dest_from_vppln_infront);
    //checkDxException(hr, D3D_OK, "SetFloat(g_h_dist_VpInfrontPlane) に失敗しました。");
    hr = pID3DXEffect->SetInt(_pPointSpriteEffect->_hUvFlipPtnNo, _pUvFlipper->_pattno_uvflip_now);
    checkDxException(hr, D3D_OK, "SetInt(_hUvFlipPtnNo) に失敗しました。");
    //ポイントスプライトON
    pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    //スケールはシェーダー内で独自計算
    _pPointSpriteModel->PointSpriteModel::draw(this);
    //ポイントスプライトOFF
    pCARETAKER->_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

void PointSpriteActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pPointSpriteModel = (PointSpriteModel*)_pModel;
}

PointSpriteActor::~PointSpriteActor() {
    delete _pUvFlipper;
}
