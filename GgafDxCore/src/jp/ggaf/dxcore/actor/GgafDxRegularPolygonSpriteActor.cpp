#include "jp/ggaf/dxcore/actor/GgafDxRegularPolygonSpriteActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxRegularPolygonSpriteEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxRegularPolygonSpriteModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxRegularPolygonSpriteActor::GgafDxRegularPolygonSpriteActor(const char* prm_name,
                                     const char* prm_model_id,
                                     const char* prm_effect_id,
                                     const char* prm_technique,
                                     GgafStatus* prm_pStat,
                                     GgafDxChecker* prm_pChecker) :

                                         GgafDxFigureActor(prm_name,
                                                           prm_model_id,
                                                           TYPE_REGULAR_POLYGON_SPRITE_MODEL,
                                                           prm_effect_id,
                                                           TYPE_REGULAR_POLYGON_SPRITE_EFFECT,
                                                           prm_technique,
                                                           prm_pStat,
                                                           prm_pChecker),
_pRegularPolygonSpriteModel( (GgafDxRegularPolygonSpriteModel*)_pModel),
_pRegularPolygonSpriteEffect( (GgafDxRegularPolygonSpriteEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxRegularPolygonSpriteActor;
    _class_name = "GgafDxRegularPolygonSpriteActor";
    _pUvFlipper->setRotation(_pRegularPolygonSpriteModel->_col_texture_split,
                             _pRegularPolygonSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _far_rate = -1.0f;

    _draw_fan_num = _pRegularPolygonSpriteModel->_angle_num;
    _cull_mode = _pRegularPolygonSpriteModel->_drawing_order == 1 ?  D3DCULL_CCW : D3DCULL_CW;

    _circumference_begin_position = 0;
}

void GgafDxRegularPolygonSpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pRegularPolygonSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    angle a = UTIL::simplifyAng(_circumference_begin_position);
    float sin_rz = ANG_SIN(a);
    float cos_rz = ANG_COS(a);
    hr = pID3DXEffect->SetMatrix(_pRegularPolygonSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pRegularPolygonSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_sin_rz, sin_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_sin_rz) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_cos_rz, cos_rz);
    checkDxException(hr, D3D_OK, "SetFloat(_h_cos_rz) に失敗しました。");
    //今回描画のUV
    float u,v;
    _pUvFlipper->getUV(u,v);
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pRegularPolygonSpriteEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
    _pRegularPolygonSpriteModel->GgafDxRegularPolygonSpriteModel::draw(this);
}


GgafDxRegularPolygonSpriteActor::~GgafDxRegularPolygonSpriteActor() {
    delete _pUvFlipper;
}
