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

    _class_name = "GgafDx9BoardSetActor";

    _pBoardSetModel = (GgafDx9BoardSetModel*)_pGgafDx9Model;
    _pBoardSetEffect = (GgafDx9BoardSetEffect*)_pGgafDx9Effect;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forceUvFlipPtnRange(0, _pBoardSetModel->_pattno_max);
    _pUvFlipper->setUvFlipPtnNo(0);
    _pUvFlipper->setUvFlipMethod(NOT_ANIMATED, 1);
    _fAlpha = 1.0f;

//    _pattno_top = 0;
//    _pattno_bottom = _pBoardSetModel->_pattno_max;
//    _patteno_now = 0;

    _isTransformed = true;
    _pFunc_calcWorldMatrix = NULL;
}

void GgafDx9BoardSetActor::processDraw() {
    _draw_set_num = 1; //同一描画深度に、GgafDx9BoardSetActorの同じモデルが連続しているカウント数
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pBoardSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pBoardSetModel->_set_num) {
                    _draw_set_num = _pBoardSetModel->_set_num;
                    break;
                }
                _pNextDrawActor = _pNextDrawActor->_pNext_TheSameDrawDepthLevel;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pBoardSetEffect->_pID3DXEffect;
    HRESULT hr;

    GgafDx9DrawableActor *pDrawActor;
    GgafDx9RectUV* pRectUV_Active;


    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {

        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedX[i], pDrawActor->_x);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedX) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahTransformedY[i], pDrawActor->_y);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahTransformedY) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahDepthZ[i], pDrawActor->_z);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahDepthZ) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahAlpha[i], pDrawActor->_fAlpha);
        checkDxException(hr, D3D_OK, "GgafDx9BoardSetModel::draw SetFloat(_ahAlpha) に失敗しました。");

        pRectUV_Active = _pBoardSetModel->_paRectUV + (((GgafDx9BoardSetActor*)(pDrawActor))->_pUvFlipper->_pattno_uvflip_now);
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetU) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pBoardSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "GgafDx9BoardModel::draw() SetFloat(_hOffsetV) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pBoardSetModel->draw(this);
}

//void GgafDx9BoardSetActor::setPatternNo(int prm_pattno) {
//    if (_pattno_top <= prm_pattno && prm_pattno <= _pattno_bottom) {
//        _patteno_now = prm_pattno;
//    } else if (prm_pattno < _pattno_top) {
//        _patteno_now = _pattno_top;
//    } else if (prm_pattno > _pattno_bottom) {
//        _patteno_now = _pattno_bottom;
//    }
//}

GgafDx9BoardSetActor::~GgafDx9BoardSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);

//    DELETEARR_IMPOSSIBLE_NULL(_technique);
//    _pModelCon->close();
//    _pEffectCon->close();
//
//    DELETEARR_POSSIBLE_NULL(_paD3DMaterial9);
    //GgafDx9BoardSetActorはマテリアルを使わないので_paD3DMaterial9はNULLのままである
}
