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

    _pattno_ani_top = 0;
    _pattno_ani_bottom = 1;
    _pattno_ani_now = 0;
    _frame_ani_interval = 0;
    _animation_method = ANIMATE_ORDER_LOOP;
    _aniframe_counter = 0;
    _is_reverse_order_in_oscillate_animation_flg = false;

    _tex_width = 0.0f;
    _tex_height = 0.0f;
    _tex_col_num = 0;
    _h_offset_u = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_offset_u" );
    _h_offset_v = _pMeshEffect->_pID3DXEffect->GetParameterByName( NULL, "g_offset_v" );

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

    int row = _tex_col_num / (_pattno_ani_now+1);
    int col = _tex_col_num % (_pattno_ani_now+1);
    float u = row * _tex_width;
    float v = col * _tex_height;
    hr = pID3DXEffect->SetFloat(_h_offset_u, u);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_u) に失敗しました。");
    hr = pID3DXEffect->SetFloat(_h_offset_v, v);
    checkDxException(hr, D3D_OK, "GgafDx9MeshActor::processDraw() SetMatrix(_h_offset_v) に失敗しました。");
    _pMeshModel->draw(this);

}

void GgafDx9SpriteMeshActor::setActivAnimationPattern(int prm_pattno_ani) {
    _pattno_ani_now = prm_pattno_ani;
}

void GgafDx9SpriteMeshActor::resetActivAnimationPattern() {
    _pattno_ani_now = _pattno_ani_top;
}

void GgafDx9SpriteMeshActor::setAnimationPatternRenge(int prm_top, int prm_bottom = 1) {
    _pattno_ani_top = prm_top;
    _pattno_ani_bottom = prm_bottom;
}

void GgafDx9SpriteMeshActor::setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_interval) {
    _animation_method = prm_method;
    _frame_ani_interval = prm_interval;
}

void GgafDx9SpriteMeshActor::addNextAnimationFrame() {
//    _TRACE_(getName()<<":_pattno_ani_now="<<_pattno_ani_now<<"/_pattno_ani_bottom="<<_pattno_ani_bottom<<"/_pattno_ani_top="<<_pattno_ani_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");

    _aniframe_counter++;
    if (_frame_ani_interval < _aniframe_counter) {
        if (_animation_method == ANIMATE_ORDER_LOOP) { //例：0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == ANIMATE_REVERSE_LOOP) { //例：0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == ANIMATE_ORDER_NOLOOP) { //例：0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_ani_bottom > _pattno_ani_now) {
                _pattno_ani_now++;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_ani_now = _pattno_ani_bottom;
            }
        } else if (_animation_method == ANIMATE_REVERSE_NOLOOP) { //例：5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_ani_top < _pattno_ani_now) {
                _pattno_ani_now--;
            } else {
                processHappen(GGAF_EVENT_NOLOOP_ANIMATION_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_ani_now = _pattno_ani_top;
            }
        } else if (_animation_method == ANIMATE_OSCILLATE_LOOP) { //例：0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_is_reverse_order_in_oscillate_animation_flg) { //逆順序時
                if (_pattno_ani_top < _pattno_ani_now) {
                    _pattno_ani_now--;
                } else {
                    _pattno_ani_now++;
                    _is_reverse_order_in_oscillate_animation_flg = false;
                }
            } else {                                            //正順序時
                if (_pattno_ani_bottom > _pattno_ani_now) {
                    _pattno_ani_now++;
                } else {
                    _pattno_ani_now--;
                    _is_reverse_order_in_oscillate_animation_flg = true;
                }

            }
        } else if (_animation_method == NOT_ANIMATED) {
            //何もしない
        }
        _aniframe_counter = 0;
    }

}

GgafDx9SpriteMeshActor::~GgafDx9SpriteMeshActor() {
}
