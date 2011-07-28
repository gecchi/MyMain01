#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9BoardSetActor::GgafDx9BoardSetActor(const char* prm_name,
                                           const char* prm_model_id,
                                           const char* prm_effect_id,
                                           const char* prm_technique) :
                                               GgafDx9DrawableActor(prm_name,
                                                                    prm_model_id,
                                                                    "b",
                                                                    prm_effect_id,
                                                                    "b",
                                                                    prm_technique,
                                                                    NULL) {
    _obj_class |= Obj_GgafDx9BoardSetActor;
    _class_name = "GgafDx9BoardSetActor";

    _pBoardSetModel = (GgafDx9BoardSetModel*)_pModel;
    _pBoardSetEffect = (GgafDx9BoardSetEffect*)_pEffect;
//    _pUvFlipper = NEW GgafDx9UvFlipper(this);
//    _pUvFlipper->forcePtnNoRange(0, _pBoardSetModel->_pattno_max);
//    _pUvFlipper->setActivePtnNo(0);
//    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pUvFlipper = NEW GgafDx9UvFlipper(_pBoardSetModel->_papTextureCon[0]->refer());
    _pUvFlipper->setRotation(_pBoardSetModel->_col_texture_split,
                             _pBoardSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);


    _fAlpha = 1.0f;

    _is2DActor = true;
    _pFunc_calcRotMvWorldMatrix = NULL;

    _Z = 0;
}

void GgafDx9BoardSetActor::processDraw() {
    _draw_set_num = 0; //GgafDx9BoardSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;
    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9BoardSetActor* pBoardSetActor = NULL;
    float u,v;
//    GgafDx9RectUV* pRectUV_Active;
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pBoardSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pBoardSetActor = (GgafDx9BoardSetActor*)pDrawActor;

                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[_draw_set_num], float(App2Pix(_X)));
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[_draw_set_num], float(App2Pix(_Y)));
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[_draw_set_num], float(App2Pix(_Z)));
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[_draw_set_num], pDrawActor->_fAlpha);
                checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) に失敗しました。");

//                pRectUV_Active = _pBoardSetModel->_paRectUV + (((GgafDx9BoardSetActor*)(pDrawActor))->_pUvFlipper->_pattno_uvflip_now);
                pBoardSetActor->_pUvFlipper->getUV(u,v);
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");

                _draw_set_num++;
                if (_draw_set_num >= _pBoardSetModel->_set_num) {
                    break;
                }
                pDrawActor = pDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    GgafDx9Universe::_pActor_DrawActive = pBoardSetActor; //描画セットの最後アクターをセット
    _pBoardSetModel->draw(this, _draw_set_num);
}


GgafDx9BoardSetActor::~GgafDx9BoardSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
