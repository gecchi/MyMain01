#include "jp/ggaf/dx/actor/BoardSetActor.h"

#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/TextureConnection.h"
#include "jp/ggaf/dx/model/BoardSetModel.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/util/GeoElem.h"


using namespace GgafDx;

BoardSetActor::BoardSetActor(const char* prm_name,
                             const char* prm_model,
                             const char* prm_effect_id,
                             const char* prm_technique,
                             CollisionChecker* prm_pChecker) :
                                 FigureActor(prm_name,
                                             prm_model,
                                             TYPE_BOARDSET_MODEL,
                                             prm_effect_id,
                                             TYPE_BOARDSET_EFFECT,
                                             prm_technique,
                                             prm_pChecker) ,
                                 IAlignAbleActor(),
_pBoardSetModel((BoardSetModel*)_pModel),
_pBoardSetEffect((BoardSetEffect*)_pEffect),
_pUvFlipper(NEW UvFlipper()) {

    _obj_class |= Obj_GgafDx_BoardSetActor | Obj_GgafDx_IAlignAbleActor;
    _class_name = "BoardSetActor";
    _pUvFlipper->locatePatternNo(_pBoardSetModel);
    _width_px = (int)(_pBoardSetModel->_model_width_px); //幅(px)
    _height_px = (int)(_pBoardSetModel->_model_height_px); //高さ(px)
    _harf_width_px = _width_px/2;
    _harf_height_px = _height_px/2;
    _align = ALIGN_LEFT;
    _valign = VALIGN_TOP;

    _is_fix_2D = true;
    _pFunc_calc_rot_mv_world_matrix = nullptr;
    setZEnableDraw(false);
    setZWriteEnable(false);
    setSpecialRenderDepthNear(0); //特別な最前面レンダリング（一番最後に描画）
}

void BoardSetActor::processDraw() {
    int draw_set_num = 0; //BoardSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    BoardSetEffect* pBoardSetEffect = _pBoardSetEffect;
    ID3DXEffect* pID3DXEffect = pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    FigureActor* pDrawActor = this;
    BoardSetActor* pBoardSetActor = nullptr;
    int model_draw_set_num = _pBoardSetModel->_draw_set_num;
    float u,v;
    while (pDrawActor) {
        if (pDrawActor->getModel() == _pBoardSetModel && pDrawActor->_hash_technique == _hash_technique) {
            pBoardSetActor = (BoardSetActor*)pDrawActor;

            if (_align == ALIGN_RIGHT) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x) - pBoardSetActor->_width_px);
            } else if (_align == ALIGN_CENTER) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x) - (pBoardSetActor->_harf_width_px));
            } else {
                //ALIGN_LEFT
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_x[draw_set_num], C_PX(pBoardSetActor->_x));
            }
            checkDxException(hr, D3D_OK, "SetFloat(_ah_transformed_x) に失敗しました。");
            if (_valign == VALIGN_BOTTOM) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y) - pBoardSetActor->_height_px);
            } else if (_valign == VALIGN_MIDDLE) {
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y) - (pBoardSetActor->_harf_height_px));
            } else {
                //VALIGN_TOP
                hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_transformed_y[draw_set_num], C_PX(pBoardSetActor->_y));
            }
            checkDxException(hr, D3D_OK, "SetFloat(_ah_transformed_y) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_depth_z[draw_set_num], C_PX(pBoardSetActor->_z));
            checkDxException(hr, D3D_OK, "SetFloat(_ah_depth_z) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_alpha[draw_set_num], pBoardSetActor->getAlpha());
            checkDxException(hr, D3D_OK, "SetFloat(_ah_alpha) に失敗しました。");
            pBoardSetActor->_pUvFlipper->getUV(u,v);
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_u[draw_set_num], u);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_u) に失敗しました。");
            hr = pID3DXEffect->SetFloat(pBoardSetEffect->_ah_offset_v[draw_set_num], v);
            checkDxException(hr, D3D_OK, "SetFloat(_h_offset_v) に失敗しました。");

            pDrawActor = pDrawActor->_pNextRenderActor;
            draw_set_num++;
            if (draw_set_num >= model_draw_set_num) {
                break;
            }
        } else {
            break;
        }
    }
    _pBoardSetModel->BoardSetModel::draw(this, draw_set_num);
    _pNextRenderActor = pDrawActor;
}

void BoardSetActor::setPositionAt(const GeometricActor* prm_pActor) {
    _x = prm_pActor->_x;
    _y = prm_pActor->_y;
}

void BoardSetActor::setPositionAt(const GeoElem* prm_pGeoElem) {
    _x = prm_pGeoElem->x;
    _y = prm_pGeoElem->y;
}

//void BoardSetActor::setAlign(Align prm_align, Valign prm_valign) {
//    _align = prm_align;
//    _valign = prm_valign;
//}
//
//void BoardSetActor::setAlign(Align prm_align) {
//    _align = prm_align;
//}
//
//void BoardSetActor::setValign(Valign prm_valign) {
//    _valign = prm_valign;
//}

//float BoardSetActor::getModelWidth() {
//    return _pBoardSetModel->_model_width_px;
//}
//
//float BoardSetActor::getModelHeight() {
//    return _pBoardSetModel->_model_height_px;
//}

void BoardSetActor::changeModelByIndex(int prm_model_index) {
    FigureActor::changeModelByIndex(prm_model_index);
    _pBoardSetModel = (BoardSetModel*)_pModel;
}

BoardSetActor::~BoardSetActor() {
    delete _pUvFlipper;
}
