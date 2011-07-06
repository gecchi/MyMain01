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
    _pSpriteSetModel = (GgafDx9SpriteSetModel*)_pModel;
    _pSpriteSetEffect = (GgafDx9SpriteSetEffect*)_pEffect;
    _pUvFlipper = NEW GgafDx9UvFlipper(_pSpriteSetModel->_papTextureCon[0]->refer());
    _pUvFlipper->setRotation(_pSpriteSetModel->_col_texture_split,
                             _pSpriteSetModel->_row_texture_split
                            );
    _pUvFlipper->setActivePtnNo(0);
    _pUvFlipper->setFlipMethod(NOT_ANIMATED, 1);

    _pFunc_calcRotMvWorldMatrix = GgafDx9Util::setWorldMatrix_RxRzRyMv;
}

void GgafDx9SpriteSetActor::processDraw() {
    _draw_set_num = 0; //GgafDx9SpriteSetActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    ID3DXEffect* pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;

    GgafDx9DrawableActor* pDrawActor = this;
    GgafDx9SpriteSetActor* pSpriteSetActor = NULL;
//    GgafDx9RectUV* pRectUV_Active;
    float u,v;
//    pTargetActor->_pUvFlipper->getUV(u,v);
    while (true) {
        if (pDrawActor)  {
            if (pDrawActor->_pModel == _pSpriteSetModel && pDrawActor->_hash_technique == _hash_technique) {
                pSpriteSetActor = (GgafDx9SpriteSetActor*)pDrawActor;

                hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ah_matWorld[_draw_set_num], &(pDrawActor->_matWorld) );
                checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetMatrix(_h_matWorld) に失敗しました。");
                pSpriteSetActor->_pUvFlipper->getUV(u,v);
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetU[_draw_set_num], u);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw() SetFloat(_hOffsetU) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahOffsetV[_draw_set_num], v);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw() SetFloat(_hOffsetV) に失敗しました。");
                hr = pID3DXEffect->SetFloat(_pSpriteSetEffect->_ahAlpha[_draw_set_num], pDrawActor->_fAlpha);
                checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetFloat(_fAlpha) に失敗しました。");

                _draw_set_num++;
                if (_draw_set_num >= _pSpriteSetModel->_set_num) {
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
    GgafDx9Universe::_pActor_DrawActive = pSpriteSetActor; //描画セットの最後アクターをセット
    _pSpriteSetModel->draw(this, _draw_set_num);
}

void GgafDx9SpriteSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _fAlpha; //＜ーこっちは今のところ無意味
    _paMaterial[0].Diffuse.a = _fAlpha;
}

void GgafDx9SpriteSetActor::addAlpha(float prm_fAlpha) {
    _fAlpha += prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paMaterial[0].Ambient.a = _fAlpha; //＜ーこっちは今のところ無意味
    _paMaterial[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteSetActor::~GgafDx9SpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFlipper);
}
