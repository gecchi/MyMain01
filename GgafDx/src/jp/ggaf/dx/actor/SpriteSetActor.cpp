#include "jp/ggaf/dx/actor/SpriteSetActor.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/effect/SpriteSetEffect.h"
#include "jp/ggaf/dx/model/SpriteSetModel.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/Util.h"


using namespace GgafDx;

SpriteSetActor::SpriteSetActor(const char* prm_name,
                               const char* prm_model,
                               const char* prm_effect_id,
                               const char* prm_technique) :

                                   FigureActor(prm_name,
                                               prm_model,
                                               TYPE_SPRITESET_MODEL,
                                               prm_effect_id,
                                               TYPE_SPRITESET_EFFECT,
                                               prm_technique),
_pSpriteSetModel((SpriteSetModel*)_pModel),
_pSpriteSetEffect((SpriteSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_SpriteSetActor;
    _class_name = "SpriteSetActor";
    _pUvFlipper->locatePatternNo(_pSpriteSetModel);
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
}

void SpriteSetActor::processDraw() {
    int draw_set_num = 0; //SpriteSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    SpriteSetEffect* const pSpriteSetEffect = _pSpriteSetEffect;
    ID3DXEffect* const pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;

    FigureActor* pDrawActor = this;
    SpriteSetActor* pSpriteSetActor = nullptr;
    const int model_draw_set_num = _pSpriteSetModel->_draw_set_num;
    float u,v;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSpriteSetActor = (SpriteSetActor*)pDrawActor;
            hr = pID3DXEffect->SetMatrix(pSpriteSetEffect->_ah_matWorld[draw_set_num], &(pSpriteSetActor->_matWorld) );
            checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) に失敗しました。");
            pSpriteSetActor->_pUvFlipper->getUV(u,v);
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_alpha[draw_set_num], pSpriteSetActor->getAlpha());
            checkDxException(hr, D3D_OK, "SetFloat(_alpha) に失敗しました。");

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
        } else {
            break;
        }
    }
    _pSpriteSetModel->SpriteSetModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

//void SpriteSetActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void SpriteSetActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void SpriteSetActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

void SpriteSetActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pSpriteSetModel = (SpriteSetModel*)_pModel;
}

SpriteSetActor::~SpriteSetActor() {
    delete _pUvFlipper;
}
