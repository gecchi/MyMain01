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
                               const char* prm_technique,
                               CollisionChecker* prm_pChecker) :

                                   FigureActor(prm_name,
                                               prm_model,
                                               TYPE_SPRITESET_MODEL,
                                               prm_effect_id,
                                               TYPE_SPRITESET_EFFECT,
                                               prm_technique,
                                               prm_pChecker) ,
_pSpriteSetModel((SpriteSetModel*)_pModel),
_pSpriteSetEffect((SpriteSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDx_SpriteSetActor;
    _class_name = "SpriteSetActor";
    _pUvFlipper->locatePatternNo(_pSpriteSetModel->_col_texture_split,
                             _pSpriteSetModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

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
//            if (_align == ALIGN_CENTER) {
//                //do nothing
//            } else if (_align == ALIGN_LEFT) {
//                pSpriteSetActor->_matWorld._41 += PX_DX(_pSpriteSetModel->_model_width_px/2);
//            } else {
//                //ALIGN_RIGHT
//                pSpriteSetActor->_matWorld._41 -= PX_DX(_pSpriteSetModel->_model_width_px/2);
//            }
//            if (_valign == VALIGN_MIDDLE) {
//                //do nothing
//            } else if (_valign == VALIGN_TOP) {
//                pSpriteSetActor->_matWorld._42 -= PX_DX(_pSpriteSetModel->_model_height_px/2);
//            } else {
//                //VALIGN_BOTTOM
//                pSpriteSetActor->_matWorld._42 += PX_DX(_pSpriteSetModel->_model_height_px/2);
//            }
            hr = pID3DXEffect->SetMatrix(pSpriteSetEffect->_ah_matWorld[draw_set_num], &(pSpriteSetActor->_matWorld) );
            checkDxException(hr, D3D_OK, "SetMatrix(_h_matWorld) に失敗しました。");
            pSpriteSetActor->_pUvFlipper->getUV(u,v);
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_alpha[draw_set_num], pSpriteSetActor->_alpha);
            checkDxException(hr, D3D_OK, "SetFloat(_alpha) に失敗しました。");

            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    Spacetime::_pActor_draw_active = pSpriteSetActor; //描画セットの最後アクターをセット
    _pSpriteSetModel->SpriteSetModel::draw(this, draw_set_num);
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

SpriteSetActor::~SpriteSetActor() {
    delete _pUvFlipper;
}
