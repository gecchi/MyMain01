#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9SpriteMeshActor::GgafDx9SpriteMeshActor(const char* prm_name,
                                       const char* prm_model,
                                       GgafDx9Checker* prm_pChecker) :

                                        GgafDx9MeshActor(prm_name,
                                                         prm_model,
                                                         "SpriteMeshEffect",
                                                         "SpriteMeshTechnique",
                                                         prm_pChecker) {

    _class_name = "GgafDx9SpriteMeshActor";
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

//    _tex_width = 1.0f;
//    _tex_height = 1.0f;
//    _tex_col_num = 1;
}


void GgafDx9SpriteMeshActor::processDraw() {
    static ID3DXEffect* pID3DXEffect;
    pID3DXEffect = _pMeshEffect->_pID3DXEffect;
    HRESULT hr;
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatView, &pCAM->_vMatrixView );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matView) に失敗しました。");
    (*_pFunc_calcWorldMatrix)(this, _matWorld);
    hr = pID3DXEffect->SetMatrix(_pMeshEffect->_hMatWorld, &_matWorld );
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(g_matWorld) に失敗しました。");
    float u = 0;
    float v = 0;
    _pUvFliper->getUV(u, v);
    //_TRACE_("_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_tex_col_num="<<_tex_col_num<<"/_tex_width="<<_tex_width<<"/_tex_height="<<_tex_height<<"/u="<<u<<"/v="<<v<<"");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_pMeshEffect->_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");
    _pMeshModel->draw(this);

}

//void GgafDx9SpriteMeshActor::setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height)  {
//    if (prm_tex_col_num < 0) {
//        throwGgafCriticalException("GgafDx9SpriteMeshActor::setTextureUvRotation prm_tex_col_numは0以上の整数で設定して下さい。");
//    }
//    _tex_width = prm_tex_width;
//    _tex_height = prm_tex_height;
//    _tex_col_num = prm_tex_col_num;
//}
//
//void GgafDx9SpriteMeshActor::setUvFlipPtnNo(int prm_pattno_uvflip) {
//    _pattno_uvflip_now = prm_pattno_uvflip;
//}
//
//void GgafDx9SpriteMeshActor::resetUvFlipPtnNo() {
//    _pattno_uvflip_now = _pattno_uvflip_top;
//}
//
//void GgafDx9SpriteMeshActor::forceUvFlipPtnRange(int prm_top, int prm_bottom = 1) {
//    _pattno_uvflip_top = prm_top;
//    _pattno_uvflip_bottom = prm_bottom;
//}
//
//void GgafDx9SpriteMeshActor::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
//    _uvflip_method = prm_method;
//    _frame_uvflip_interval = prm_interval;
//}
//
//void GgafDx9SpriteMeshActor::behaveUvFlip() {
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

GgafDx9SpriteMeshActor::~GgafDx9SpriteMeshActor() {
    DELETE_IMPOSSIBLE_NULL(_pUvFliper);
}
