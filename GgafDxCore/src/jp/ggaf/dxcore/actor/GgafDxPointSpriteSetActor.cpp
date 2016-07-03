#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteSetActor.h"

#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/effect/GgafDxPointSpriteSetEffect.h"
#include "jp/ggaf/dxcore/model/GgafDxPointSpriteSetModel.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureConnection.h"

using namespace GgafCore;
using namespace GgafDxCore;

GgafDxPointSpriteSetActor::GgafDxPointSpriteSetActor(const char* prm_name,
                                                     const char* prm_model_id,
                                                     const char* prm_effect_id,
                                                     const char* prm_technique,
                                                     GgafStatus* prm_pStat,
                                                     GgafDxChecker* prm_pChecker) :

                                                         GgafDxFigureActor(prm_name,
                                                                           prm_model_id,
                                                                           "o",
                                                                           prm_effect_id,
                                                                           "o",
                                                                           prm_technique,
                                                                           prm_pStat,
                                                                           prm_pChecker),
_pPointSpriteSetModel((GgafDxPointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((GgafDxPointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {
    _obj_class |= Obj_GgafDxPointSpriteSetActor;
    _class_name = "GgafDxPointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pUvFlipper->setRotation(_pPointSpriteSetModel->_texture_split_rowcol,
                             _pPointSpriteSetModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

GgafDxPointSpriteSetActor::GgafDxPointSpriteSetActor(const char* prm_name,
                                                     const char* prm_model_id,
                                                     const char* prm_model_type,
                                                     const char* prm_effect_id,
                                                     const char* prm_effect_type,
                                                     const char* prm_technique,
                                                     GgafStatus* prm_pStat,
                                                     GgafDxChecker* prm_pChecker) :

                                                         GgafDxFigureActor(prm_name,
                                                                           prm_model_id,
                                                                           prm_model_type,
                                                                           prm_effect_id,
                                                                           prm_effect_type,
                                                                           prm_technique,
                                                                           prm_pStat,
                                                                           prm_pChecker),
_pPointSpriteSetModel((GgafDxPointSpriteSetModel*)_pModel),
_pPointSpriteSetEffect((GgafDxPointSpriteSetEffect*)_pEffect),
_pUvFlipper(NEW GgafDxUvFlipper(getModel()->getDefaultTextureConnection()->peek())) {

    _obj_class |= Obj_GgafDxPointSpriteSetActor;
    _class_name = "GgafDxPointSpriteSetActor";
    defineRotMvWorldMatrix(UTIL::setWorldMatrix_RxRzRyMv); //デフォルトの回転×移動の変換行列
    _pUvFlipper->setRotation(_pPointSpriteSetModel->_texture_split_rowcol,
                             _pPointSpriteSetModel->_texture_split_rowcol );
    _pUvFlipper->setActivePtn(0);
    _pUvFlipper->exec(NOT_ANIMATED, 1);
    setZEnableDraw(false);
    setZWriteEnable(false);
}

void GgafDxPointSpriteSetActor::processDraw() {
    int draw_set_num = 0; //GgafDxPointSpriteSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* const pID3DXEffect = _pPointSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDxFigureActor* pDrawActor = this;
    GgafDxPointSpriteSetActor* pPointSpriteSetActor = nullptr;
    const int model_set_num = _pPointSpriteSetModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pPointSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pPointSpriteSetActor = (GgafDxPointSpriteSetActor*)pDrawActor;
            pPointSpriteSetActor->_matWorld._14 = pPointSpriteSetActor->_pUvFlipper->_pattno_uvflip_now;//UVのアクティブパターン番号をワールド変換行列のmatWorld._14 に埋め込む
            hr = pID3DXEffect->SetMatrix(_pPointSpriteSetEffect->_ah_matWorld[draw_set_num], &(pPointSpriteSetActor->_matWorld));
            checkDxException(hr, D3D_OK, "SetMatrix(g_matWorld) に失敗しました。");
            hr = pID3DXEffect->SetValue(_pPointSpriteSetEffect->_ah_colMaterialDiffuse[draw_set_num], &(pPointSpriteSetActor->_paMaterial[0].Diffuse), sizeof(D3DCOLORVALUE) );
            checkDxException(hr, D3D_OK, "SetValue(g_colMaterialDiffuse) に失敗しました。");
            draw_set_num++;
            if (draw_set_num >= model_set_num) {
                break;
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    GgafDxSpacetime::_pActor_draw_active = pPointSpriteSetActor; //描画セットの最後アクターをセット

    //ポイントスプライトON
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
    ((GgafDxPointSpriteSetModel*)_pPointSpriteSetModel)->GgafDxPointSpriteSetModel::draw(this, draw_set_num);
    //ポイントスプライトOFF
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

GgafDxPointSpriteSetActor::~GgafDxPointSpriteSetActor() {
    delete _pUvFlipper;
}
