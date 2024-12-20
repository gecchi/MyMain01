#include "jp/ggaf/dx/actor/SpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/SpriteEffect.h"
#include "jp/ggaf/dx/model/SpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"

using namespace GgafDx;

SpriteActor::SpriteActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect_id,
                         const char* prm_technique) :

                             FigureActor(prm_name,
                                         prm_model,
                                         TYPE_SPRITE_MODEL,
                                         prm_effect_id,
                                         TYPE_SPRITE_EFFECT,
                                         prm_technique),
                             IAlignAbleActor(),
_pSpriteModel( (SpriteModel*)_pModel),
_pSpriteEffect( (SpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_SpriteActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "SpriteActor";
    _pUvFlipper->locatePatternNo(_pSpriteModel->_col_texture_split,
                                 _pSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void SpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) に失敗しました。");
    hr = pID3DXEffect->SetValue(_pSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) に失敗しました。");
    _pSpriteModel->SpriteModel::draw(this);
}

void SpriteActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pSpriteModel = (SpriteModel*)_pModel;
}

SpriteActor::~SpriteActor() {
    delete _pUvFlipper;
}
