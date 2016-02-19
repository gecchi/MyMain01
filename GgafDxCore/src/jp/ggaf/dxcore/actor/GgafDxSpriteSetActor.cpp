#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxSpriteSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxSpriteSetModel.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxSpriteSetActor::GgafDxSpriteSetActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique,
                                           GgafStatus* prm_pStat,
                                           GgafDxChecker* prm_pChecker) :

                                               GgafDxFigureActor(prm_name,
                                                                   prm_model_id,
                                                                   "s",
                                                                   prm_effect_id,
                                                                   "s",
                                                                   prm_technique,
                                                                   prm_pStat,
                                                                   prm_pChecker) ,
_pSpriteSetModel((GgafDxSpriteSetModel*)_pModel),
_pSpriteSetEffect((GgafDxSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxSpriteSetActor;
    _class_name = "GgafDxSpriteSetActor";
    _pUvFlipper->setRotation(_pSpriteSetModel->_col_texture_split,
                             _pSpriteSetModel->_row_texture_split );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);

    _pFunc_calc_rot_mv_world_matrix = UTIL::setWorldMatrix_RxRzRyMv;
    (*_pFunc_calc_rot_mv_world_matrix)(this, _matWorldRotMv);
    _align = ALIGN_CENTER;
    _valign = VALIGN_MIDDLE;
}

void GgafDxSpriteSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxSpriteSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxSpriteSetEffect* const pSpriteSetEffect = _pSpriteSetEffect;
    ID3DXEffect* const pID3DXEffect = pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;

    GgafDxFigureActor* pDrawActor = this;
    GgafDxSpriteSetActor* pSpriteSetActor = nullptr;
    const int model_set_num = _pSpriteSetModel->_set_num;
    float u,v;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pSpriteSetActor = (GgafDxSpriteSetActor*)pDrawActor;
            if (_align == ALIGN_CENTER) {
                //do nothing
            } else if (_align == ALIGN_LEFT) {
                pSpriteSetActor->_matWorld._41 += PX_C(_pSpriteSetModel->_model_width_px/2);
            } else {
                //ALIGN_RIGHT
                pSpriteSetActor->_matWorld._41 -= PX_C(_pSpriteSetModel->_model_width_px/2);
            }
            if (_valign == VALIGN_MIDDLE) {
                //do nothing
            } else if (_valign == VALIGN_TOP) {
                pSpriteSetActor->_matWorld._42 -= PX_C(_pSpriteSetModel->_model_height_px/2);
            } else {
                //VALIGN_BOTTOM
                pSpriteSetActor->_matWorld._42 += PX_C(_pSpriteSetModel->_model_height_px/2);
            }
            hr = pID3DXEffect->SetMatrix(pSpriteSetEffect->_ah_matWorld[draw_set_num], &(pSpriteSetActor->_matWorld) );
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetMatrix(_h_matWorld) に失敗しました。");
            pSpriteSetActor->_pUvFlipper->getUV(u,v);
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw() SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw() SetFloat(_h_offset_v) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pSpriteSetEffect->_ah_alpha[draw_set_num], pSpriteSetActor->_alpha);
            checkDxException(hr, D3D_OK, "GgafDxSpriteSetActor::processDraw SetFloat(_alpha) に失敗しました。");

            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pSpriteSetActor; //描画セットの最後アクターをセット
    _pSpriteSetModel->GgafDxSpriteSetModel::draw(this, draw_set_num);
}

void GgafDxSpriteSetActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    _align = prm_align;
    _valign = prm_valign;
}

void GgafDxSpriteSetActor::setAlign(GgafDxAlign prm_align) {
    _align = prm_align;
}

void GgafDxSpriteSetActor::setValign(GgafDxValign prm_valign) {
    _valign = prm_valign;
}

GgafDxSpriteSetActor::~GgafDxSpriteSetActor() {
    delete _pUvFlipper;
}
