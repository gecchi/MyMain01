#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

GgafDx9UvFlipper::GgafDx9UvFlipper(GgafDx9GeometricActor* prm_pActor) : GgafObject() {
    _pActor = prm_pActor;
    _pattno_uvflip_top = 0;
    _pattno_uvflip_bottom = 0;
    _pattno_uvflip_now = 0;
    _frame_uvflip_interval = 1;
    _uvflip_method = FLIP_ORDER_LOOP;
    _frame_counter_uvflip = 0;
    _is_reverse_order_in_oscillate_animation_flg = false;
    _tex_width = 1.0f;
    _tex_height = 1.0f;
    _tex_col_num = 1;
}

void GgafDx9UvFlipper::setTextureUvRotation(int prm_tex_col_num, float prm_tex_width, float prm_tex_height)  {
    if (prm_tex_col_num < 0) {
        throwGgafCriticalException("GgafDx9UvFlipper::setTextureUvRotation prm_tex_col_numは0以上の整数で設定して下さい。");
    }
    _tex_width = prm_tex_width;
    _tex_height = prm_tex_height;
    _tex_col_num = prm_tex_col_num;
}

void GgafDx9UvFlipper::setUvFlipPtnNo(int prm_pattno_uvflip) {
    if (_pattno_uvflip_top <= prm_pattno_uvflip && prm_pattno_uvflip <= _pattno_uvflip_bottom) {
        _pattno_uvflip_now = prm_pattno_uvflip;
    } else if (prm_pattno_uvflip < _pattno_uvflip_top) {
        _pattno_uvflip_now = _pattno_uvflip_top;
    } else if (prm_pattno_uvflip > _pattno_uvflip_bottom) {
        _pattno_uvflip_now = _pattno_uvflip_bottom;
    }
}

void GgafDx9UvFlipper::resetUvFlipPtnNo() {
    _pattno_uvflip_now = _pattno_uvflip_top;
}

void GgafDx9UvFlipper::forceUvFlipPtnRange(int prm_top, int prm_bottom) {
#ifdef MY_DEBUG
    if (prm_top < 0) {
        _TRACE_("GgafDx9UvFlipper::forceUvFlipPtnRange prm_top="<<prm_top<<" TOPが負です。意図してますか？");
    }
    if (prm_top > prm_bottom) {
        throwGgafCriticalException("GgafDx9UvFlipper::forceUvFlipPtnRange prm_top="<<prm_top<<",prm_bottom="<<prm_bottom<<" 大小がおかしいです");
    }
#endif
    _pattno_uvflip_top = prm_top;
    _pattno_uvflip_bottom = prm_bottom;
}

void GgafDx9UvFlipper::setUvFlipMethod(GgafDx9UvFlipMethod prm_method, int prm_interval) {
    _uvflip_method = prm_method;
    _frame_uvflip_interval = prm_interval;
}

void GgafDx9UvFlipper::behave() {
//    _TRACE_(getName()<<":_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_pattno_uvflip_bottom="<<_pattno_uvflip_bottom<<"/_pattno_uvflip_top="<<_pattno_uvflip_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");

    _frame_counter_uvflip++;
    if (_frame_uvflip_interval < _frame_counter_uvflip) {
        if (_uvflip_method == FLIP_ORDER_LOOP) { //例：0,1,2,3,4,5,0,1,2,3,4,5,...
            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                _pattno_uvflip_now++;
            } else {
                _pattno_uvflip_now = _pattno_uvflip_top;
            }
        } else if (_uvflip_method == FLIP_REVERSE_LOOP) { //例：0,5,4,3,2,1,0,5,4,3,2,1,0,5,4...
            if (_pattno_uvflip_top < _pattno_uvflip_now) {
                _pattno_uvflip_now--;
            } else {
                _pattno_uvflip_now = _pattno_uvflip_bottom;
            }
        } else if (_uvflip_method == FLIP_ORDER_NOLOOP) { //例：0,1,2,3,4,5,5,5,5,5,5,5...
            if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                _pattno_uvflip_now++;
            } else {
                _pActor->processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_uvflip_now = _pattno_uvflip_bottom;
            }
        } else if (_uvflip_method == FLIP_REVERSE_NOLOOP) { //例：5,4,3,2,1,0,0,0,0,0,0...
            if (_pattno_uvflip_top < _pattno_uvflip_now) {
                _pattno_uvflip_now--;
            } else {
                _pActor->processHappen(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED); //もうアニメーションは進まないことを通知
                _pattno_uvflip_now = _pattno_uvflip_top;
            }
        } else if (_uvflip_method == FLIP_OSCILLATE_LOOP) { //例：0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
            if (_is_reverse_order_in_oscillate_animation_flg) { //逆順序時
                if (_pattno_uvflip_top < _pattno_uvflip_now) {
                    _pattno_uvflip_now--;
                } else {
                    _pattno_uvflip_now++;
                    _is_reverse_order_in_oscillate_animation_flg = false;
                }
            } else {                                            //正順序時
                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                    _pattno_uvflip_now++;
                } else {
                    _pattno_uvflip_now--;
                    _is_reverse_order_in_oscillate_animation_flg = true;
                }

            }
        } else if (_uvflip_method == NOT_ANIMATED) {
            //何もしない
        }
        _frame_counter_uvflip = 0;
    }

}

void GgafDx9UvFlipper::getUV(float& out_u, float& out_v) {
#ifdef MY_DEBUG
    if (_tex_col_num == 0) {
        throwGgafCriticalException("GgafDx9UvFlipper::getUV ゼロ割り算になってしまいます。_tex_col_numの値が不正です。");
    }
#endif
    out_u = ((int)(_pattno_uvflip_now % _tex_col_num)) * _tex_height;
    out_v = ((int)(_pattno_uvflip_now / _tex_col_num)) * _tex_width;
}

GgafDx9UvFlipper::~GgafDx9UvFlipper() {
}
