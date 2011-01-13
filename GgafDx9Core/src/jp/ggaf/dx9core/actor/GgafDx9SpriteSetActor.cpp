#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteSetActor::GgafDx9SpriteSetActor(const char* prm_name,
                                       const char* prm_model_id,
                                       const char* prm_effect_id,
                                       const char* prm_technique,
                                       GgafDx9Checker* prm_pChecker) :

                                           GgafDx9DrawableActor(prm_name,
                                                                prm_model_id,
                                                                "s",
                                                                prm_effect_id,
                                                                "s",
                                                                prm_technique,
                                                                prm_pChecker) {
    _obj_class |= Obj_GgafDx9SpriteSetActor;
    _class_name = "GgafDx9SpriteSetActor";

    //モデル取得
    _pSpriteSetModel = (GgafDx9SpriteSetModel*)_pGgafDx9Model;
    _pSpriteSetEffect = (GgafDx9SpriteSetEffect*)_pGgafDx9Effect;
    _pUvFlipper = NEW GgafDx9UvFlipper(this);
    _pUvFlipper->forcePtnNoRange(0, _pSpriteSetModel->_pattno_uvflip_Max);
    _pUvFlipper->setPtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);
    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}

void GgafDx9SpriteSetActor::processDraw() {
    _draw_set_num = 1; //同一描画深度に、GgafDx9SpriteSetActorの同じモデルかつ同じテクニックが
                       //連続しているカウント数
    GgafDx9DrawableActor* _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pSpriteSetModel &&
                _pNextDrawActor->_hash_technique == _hash_technique
            ) {
                _draw_set_num++;
                if (_draw_set_num > _pSpriteSetModel->_set_num) {
                    _draw_set_num = _pSpriteSetModel->_set_num;
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

    ID3DXEffect* pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
//    hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_h_matView, &P_CAM->_vMatrixView );
//    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");

    GgafDx9DrawableActor *pDrawActor;
    GgafDx9RectUV* pRectUV_Active;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        //(*_pFunc_calcRotMvWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ah_matWorld[i], &(pDrawActor->_matWorld) );
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetMatrix(_h_matWorld) に失敗しました。");
        //今回描画のUV

        pRectUV_Active = _pSpriteSetModel->_paRectUV + (((GgafDx9SpriteSetActor*)(pDrawActor))->_pUvFlipper->_pattno_uvflip_now);

        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[i], pRectUV_Active->_aUV[0].tu);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw() SetFloat(_hOffsetU) に失敗しました。");

        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[i], pRectUV_Active->_aUV[0].tv);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw() SetFloat(_hOffsetV) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[i], pDrawActor->_fAlpha);
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetFloat(_fAlpha) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }

    _pSpriteSetModel->draw(this, _draw_set_num);


}

void GgafDx9SpriteSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paD3DMaterial9[0].Ambient.a = _fAlpha; //＜ーこっちは今のところ無意味
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

void GgafDx9SpriteSetActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paD3DMaterial9[0].Ambient.a = _fAlpha; //＜ーこっちは今のところ無意味
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteSetActor::~GgafDx9SpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
