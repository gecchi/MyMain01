#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshSetActor::GgafDx9SpriteMeshSetActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshSetActor(prm_name,
                                                           prm_model,
                                                           "SpriteMeshSetEffect",
                                                           "SpriteMeshSetTechnique",
                                                           prm_pChecker) {

    _class_name = "GgafDx9SpriteMeshSetActor";
    _pUvFliper = NEW GgafDx9UvFliper(this);
    _pUvFliper->forceUvFlipPtnRange(0, 1);
    _pUvFliper->setUvFlipPtnNo(0);
    _pUvFliper->setUvFlipMethod(NOT_ANIMATED, 1);
//    _pattno_uvflip_top = 0;
//    _pattno_uvflip_bottom = 0;
//    _pattno_uvflip_now = 0;
//    _frame_uvflip_interval = 1;
//    _uvflip_method = FLIP_ORDER_LOOP;
//    _frame_counter_uvflip = 0;
//    _is_reverse_order_in_oscillate_animation_flg = false;

    //_tex_width = 1.0f;
    //_tex_height = 1.0f;
    //_tex_col_num = 1;
//    _h_offset_u = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_offset_u" );
//    _h_offset_v = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_offset_v" );

}


void GgafDx9SpriteMeshSetActor::processDraw() {

    _draw_set_num = 1; //GgafDx9MeshSetActorの同じモデルが連続しているカウント数。同一描画深度は一度に描画する。
    GgafDx9DrawableActor* _pNextDrawActor;
    _pNextDrawActor = _pNext_TheSameDrawDepthLevel;
    while (true) {
        if (_pNextDrawActor != NULL)  {
            if (_pNextDrawActor->_pGgafDx9Model == _pMeshSetModel && _pNextDrawActor->isActive()) {
                _draw_set_num++;
                if (_draw_set_num > _pMeshSetModel->_set_num) {
                    _draw_set_num = _pMeshSetModel->_set_num;
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
    pID3DXEffect = _pMeshSetEffect->_pID3DXEffect;

    HRESULT hr;

    //VIEW変換行列
    hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_hMatView, &pCAM->_vMatrixView);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(_hMatView) に失敗しました。");
    //基本モデル頂点数
    hr = pID3DXEffect->SetInt(_pMeshSetEffect->_h_nVertexs, _pMeshSetModel->_nVertices);
    checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetInt(_h_nVertexs) に失敗しました。2");

    GgafDx9DrawableActor *pDrawActor;
    pDrawActor = this;
    GgafDx9SpriteMeshSetActor* pA;
    float u = 0;
    float v = 0;
    for (int i = 0; i < _draw_set_num; i++) {
        (*_pFunc_calcWorldMatrix)(pDrawActor, pDrawActor->_matWorld);
        hr = pID3DXEffect->SetMatrix(_pMeshSetEffect->_ahMatWorld[i], &(pDrawActor->_matWorld));
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
        hr = pID3DXEffect->SetValue(_pMeshSetEffect->_ahMaterialDiffuse[i], &(pDrawActor->_paD3DMaterial9[0].Diffuse), sizeof(D3DCOLORVALUE) );
        checkDxException(hr, D3D_OK, "GgafDx9MeshSetModel::draw() SetValue(g_MaterialDiffuse) に失敗しました。");

        pA = (GgafDx9SpriteMeshSetActor*)pDrawActor; //このキャストは危険である。
        //[MEMO]
        //GgafDx9SpriteMeshSetActor は、GgafDx9MeshSetActor から派生しており、モデルクラスは同じである。
        //GgafDx9SpriteMeshSetActorが使用するモデル名("x/10/Flora"等)と、GgafDx9MeshSetActorが使用するモデル名が
        //同じものが存在する場合、pDrawActor は、GgafDx9MeshSetActor の可能性もある。
        //これは、_draw_set_num を求めるロジックは同一深度で連続の同一(アドレス)モデルである。という判定しか行っていないため。
        //したがって、本来は GgafDx9SpriteMeshSetActor と GgafDx9MeshSetActor で同一モデル名を使用することは禁止にしたい。
        //したいけども、そうそう起こる事でも無いので、とりあえず注意して重複させないように意識することにする。
        //TODO:重複しないようにする仕組みを組み込め

        //UVオフセット設定
        pA->_pUvFliper->getUV(u, v);
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetU[i], u);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
        hr = pID3DXEffect->SetFloat(_pMeshSetEffect->_ahOffsetV[i], v);
        checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");
        pDrawActor = pDrawActor -> _pNext_TheSameDrawDepthLevel;
        if (i > 0) {
            //アクティブを進める
            GgafDx9Universe::_pActor_DrawActive = GgafDx9Universe::_pActor_DrawActive->_pNext_TheSameDrawDepthLevel;
        }
    }
    _pMeshSetModel->draw(this);



}

//void GgafDx9SpriteMeshSetActor::setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height)  {
//    if (prm_tex_col_num < 0) {
//        throwGgafCriticalException("GgafDx9SpriteMeshSetActor::setTextureUvRotation prm_tex_col_numは0以上の整数で設定して下さい。");
//    }
//    _tex_width = prm_tex_width;
//    _tex_height = prm_tex_height;
//    _tex_col_num = prm_tex_col_num;
//}
//
//void GgafDx9SpriteMeshSetActor::setUvFlipPtnNo(int prm_pattno_uvflip) {
//    _pattno_uvflip_now = prm_pattno_uvflip;
//}
//
//void GgafDx9SpriteMeshSetActor::resetUvFlipPtnNo() {
//    _pattno_uvflip_now = _pattno_uvflip_top;
//}
//
//void GgafDx9SpriteMeshSetActor::forceUvFlipPtnRange(int prm_top, int prm_bottom = 1) {
//    _pattno_uvflip_top = prm_top;
//    _pattno_uvflip_bottom = prm_bottom;
//}
//
//void GgafDx9SpriteMeshSetActor::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
//    _uvflip_method = prm_method;
//    _frame_uvflip_interval = prm_interval;
//}
//
//void GgafDx9SpriteMeshSetActor::behaveUvFlip() {
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

GgafDx9SpriteMeshSetActor::~GgafDx9SpriteMeshSetActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFliper);
}
