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
    _class_name = "GgafDx9SpriteSetActor";

    //モデル取得
    _pSpriteSetModel = (GgafDx9SpriteSetModel*)_pGgafDx9Model;
    _pSpriteSetEffect = (GgafDx9SpriteSetEffect*)_pGgafDx9Effect;
    _pUvFliper = NEW GgafDx9UvFliper(this);
    _pUvFliper->forceUvFlipPtnRange(0, _pSpriteSetModel->_pattno_uvflip_Max);
    _pUvFliper->setUvFlipPtnNo(0);
    _pUvFliper->setUvFlipMethod(FLIP_ORDER_LOOP, 1);
    _pFunc_calcWorldMatrix = GgafDx9Util::calcWorldMatrix_ScRxRzRyMv;
}

void GgafDx9SpriteSetActor::processDraw() {
    _draw_set_num = 1; //同一描画深度に、GgafDx9SpriteSetActorの同じモデルが連続しているカウント数
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pSpriteSetModel && _pNextDrawActor->isActive()) {
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

    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pSpriteSetEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::GgafDx9MeshEffect SetMatrix(g_matView) に失敗しました。");

    GgafDx9DrawableActor *pDrawActor;
    GgafDx9RectUV* pRectUV_Active;
    pDrawActor = this;
    for (int i = 0; i < _draw_set_num; i++) {
        (*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pSpriteSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld) );
        checkDxException(hr, D3D_OK, "GgafDx9SpriteSetActor::processDraw SetMatrix(_hMatWorld) に失敗しました。");
        //今回描画のUV

        pRectUV_Active = _pSpriteSetModel->_paRectUV + (((GgafDx9SpriteSetActor*)(pDrawActor))->_pUvFliper->_pattno_uvflip_now);

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
    // Zバッファを無効に
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    // Zバッファ書き込み不可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    _pSpriteSetModel->draw(this);

    // Zバッファを有効に
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファ書き込み可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

//void GgafDx9SpriteSetActor::setUvFlipPtnNo(int prm_pattno_uvflip) {
//    if (0 > prm_pattno_uvflip || prm_pattno_uvflip > (_pSpriteSetModel->_pattno_uvflip_Max)) {
//        throwGgafCriticalException("GgafDx9SpriteSetActor::setUvFlipPtnNo アニメーションパターン番号が範囲外です。引数="<<prm_pattno_uvflip);
//    } else {
//        _pattno_uvflip_now = prm_pattno_uvflip;
//    }
//}
//
//void GgafDx9SpriteSetActor::resetUvFlipPtnNo() {
//    _pattno_uvflip_now = _pattno_uvflip_top;
//}
//
//void GgafDx9SpriteSetActor::forceUvFlipPtnRange(int prm_top, int prm_bottom = 1) {
//    if (prm_top < 0 || prm_bottom > (_pSpriteSetModel->_pattno_uvflip_Max)) {
//        throwGgafCriticalException("GgafDx9SpriteSetActor::forceUvFlipPtnRange アニメーションパターン番号が範囲外です。引数("<<prm_top<<","<<prm_bottom<<")");
//    } else {
//        _pattno_uvflip_top = prm_top;
//        _pattno_uvflip_bottom = prm_bottom;
//    }
//}
//
//void GgafDx9SpriteSetActor::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
//    _uvflip_method = prm_method;
//    _frame_uvflip_interval = prm_interval;
//}
//
//void GgafDx9SpriteSetActor::behaveUvFlip() {
////    _TRACE_(getName()<<":_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_pattno_uvflip_bottom="<<_pattno_uvflip_bottom<<"/_pattno_uvflip_top="<<_pattno_uvflip_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");
//
//    _frame_counter_uvflip++;
//    if (_frame_uvflip_interval < _frame_counter_uvflip) {
//        if (_uvflip_method == FLIP_ORDER_LOOP) { //例：0,1,2,3,4,5,0,1,2,3,4,5,...
//            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                _pattno_uvflip_now++;
//            } else {
//                _pattno_uvflip_now = _pattno_uvflip_top;
//            }
//        } else if (_uvflip_method == FLIP_REVERSE_LOOP) { //例：0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
//            if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                _pattno_uvflip_now--;
//            } else {
//                _pattno_uvflip_now = _pattno_uvflip_bottom;
//            }
//        } else if (_uvflip_method == FLIP_ORDER_NOLOOP) { //例：0,1,2,3,4,5,5,5,5,5,5,5...
//            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                _pattno_uvflip_now++;
//            } else {
//                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //もうアニメーションは進まないことを通知
//                _pattno_uvflip_now = _pattno_uvflip_bottom;
//            }
//        } else if (_uvflip_method == FLIP_REVERSE_NOLOOP) { //例：5,4,3,2,1,0,0,0,0,0,0...
//            if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                _pattno_uvflip_now--;
//            } else {
//                processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //もうアニメーションは進まないことを通知
//                _pattno_uvflip_now = _pattno_uvflip_top;
//            }
//        } else if (_uvflip_method == FLIP_OSCILLATE_LOOP) { //例：0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
//            if (_is_reverse_order_in_oscillate_animation_flg) { //逆順序時
//                if (_pattno_uvflip_top < _pattno_uvflip_now) {
//                    _pattno_uvflip_now--;
//                } else {
//                    _pattno_uvflip_now++;
//                    _is_reverse_order_in_oscillate_animation_flg = false;
//                }
//            } else {                                            //正順序時
//                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
//                    _pattno_uvflip_now++;
//                } else {
//                    _pattno_uvflip_now--;
//                    _is_reverse_order_in_oscillate_animation_flg = true;
//                }
//
//            }
//        } else if (_uvflip_method == NOT_ANIMATED) {
//            //何もしない
//        }
//        _frame_counter_uvflip = 0;
//    }
//
//}

void GgafDx9SpriteSetActor::setAlpha(float prm_fAlpha) {
    _fAlpha = prm_fAlpha;
    //α設定、現在マテリアルはDiffuse以外関係ない
    _paD3DMaterial9[0].Ambient.a = _fAlpha; //＜今のところ無意味
    _paD3DMaterial9[0].Diffuse.a = _fAlpha;
}

GgafDx9SpriteSetActor::~GgafDx9SpriteSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFliper);
}
