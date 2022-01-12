#include "jp/ggaf/dx/actor/SpriteActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/God.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/effect/SpriteEffect.h"
#include "jp/ggaf/dx/model/SpriteModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"

using namespace GgafDx;

SpriteActor::SpriteActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         Checker* prm_pChecker) :

                             FigureActor(prm_name,
                                         prm_model,
                                         TYPE_ACTOR_DEFINE,
                                         prm_effect_id,
                                         TYPE_SPRITE_EFFECT,
                                         prm_technique,
                                         prm_pChecker),
_pSpriteModel( (SpriteModel*)_pModel),
_pSpriteEffect( (SpriteEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDx_SpriteActor;
    _class_name = "SpriteActor";
    _pUvFlipper->locatePatternNo(_pSpriteModel->_col_texture_split,
                             _pSpriteModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //�f�t�H���g�̉�]�~�ړ��̕ϊ��s��
    _far_rate = -1.0f;

    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void SpriteActor::processDraw() {
    ID3DXEffect* const pID3DXEffect = _pSpriteEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteEffect->_h_matWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetValue(_pSpriteEffect->_h_colMaterialDiffuse, &(_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
    checkDxException(hr, D3D_OK, "SetValue(_h_colMaterialDiffuse) �Ɏ��s���܂����B");
    hr = pID3DXEffect->SetFloat(_pSpriteEffect->_h_far_rate, _far_rate );
    checkDxException(hr, D3D_OK, "SetFloat(_h_far_rate) �Ɏ��s���܂����B");
    _pSpriteModel->SpriteModel::draw(this);
}

SpriteActor::~SpriteActor() {
    delete _pUvFlipper;
}
