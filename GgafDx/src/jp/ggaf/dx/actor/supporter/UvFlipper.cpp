#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/texture/Texture.h"


using namespace GgafDx;

UvFlipper::UvFlipper(Texture* prm_pTexture) : GgafCore::Object(),
_pTexture(prm_pTexture) {
    _pattno_uvflip_top = 0;
    _pattno_uvflip_max = 0;
    _pattno_uvflip_bottom = 0;
    _pattno_uvflip_now = 0;
    _uvflip_interval_frames = 1;
    _uvflip_method = FLIP_ORDER_LOOP;
    _frame_counter_uvflip = 0;
    _is_reverse_order_in_oscillate_animation_flg = false;
    _one_ptn_tex_width = 1.0f;
    _one_ptn_tex_height = 1.0f;
    _ptn_col_num = 1;
    _ptn_row_num = 1;
    _pa_ptn_offset_customized = nullptr;
    _ptn_customized = 0;
    _cnt_customized = 0;
    _base_u = 0.0f;
    _base_v = 0.0f;
    _paUV = nullptr;
}

void UvFlipper::locatePatternNo(float prm_base_u, float prm_base_v,
                                      float prm_one_ptn_tex_width, float prm_one_ptn_tex_height,
                                      int prm_ptn_col_num, int prm_num_of_max_patterns) {
#ifdef MY_DEBUG
    if (prm_ptn_col_num < 0) {
        throwCriticalException("prm_ptn_col_num��0���傫�����Őݒ肵�ĉ������BTexture="<<_pTexture->_texture_name);
    }
#endif
    _base_u = prm_base_u;
    _base_v = prm_base_v;
    _one_ptn_tex_width = prm_one_ptn_tex_width;
    _one_ptn_tex_height = prm_one_ptn_tex_height;
    _ptn_col_num = prm_ptn_col_num;
    _pattno_uvflip_max = prm_num_of_max_patterns-1;
    _ptn_row_num = (int)(((1.0*prm_num_of_max_patterns)/(1.0*_ptn_col_num))+0.5); //�l�̌ܓ�
    if (_pattno_uvflip_bottom > _pattno_uvflip_max || _pattno_uvflip_bottom == 0) {
        _pattno_uvflip_bottom = _pattno_uvflip_max; //�����p�^�[���ԍ������ݒ�Ȃ�ő�ɂ��킹�Ă���
    }
    if (_paUV) {
        GGAF_DELETEARR(_paUV);
    }
    _paUV = NEW UV[_pattno_uvflip_max+1];

    for (int row = 0; row < _ptn_row_num; row++) {
        for (int col = 0; col < _ptn_col_num; col++) {
            int pattno_uvflip = row*_ptn_col_num + col;
            _paUV[pattno_uvflip]._u = (float)(1.0*col/_ptn_col_num);
            _paUV[pattno_uvflip]._v = (float)(1.0*row/_ptn_row_num);
        }
    }
}
void UvFlipper::locatePatternNo(int prm_ptn_col_num, int prm_ptn_row_num) {
    locatePatternNo(0, 0,
                    1.0 / prm_ptn_col_num, 1.0 / prm_ptn_row_num,
                    prm_ptn_col_num, prm_ptn_col_num*prm_ptn_row_num);
}

void UvFlipper::remapPatternNoUv(int prm_ptn_num, ...) {
    UV* paUV_temp = NEW UV[_pattno_uvflip_max+1];
    for (int row = 0; row < _ptn_row_num; row++) {
        for (int col = 0; col < _ptn_col_num; col++) {
            int pattno_uvflip = row*_ptn_col_num + col;
            paUV_temp[pattno_uvflip] = _paUV[pattno_uvflip];
        }
    }
    va_list ap;
    va_start(ap, prm_ptn_num);
    for (int i = 0; i < prm_ptn_num; i++ ) {
        int new_ptn_no = va_arg(ap, int);
        _paUV[i] = paUV_temp[new_ptn_no];
    }
    va_end(ap);
    GGAF_DELETEARR(paUV_temp);
}

void UvFlipper::setActivePtn(int prm_pattno_uvflip) {
#ifdef MY_DEBUG
    if (prm_pattno_uvflip > _pattno_uvflip_max) {
        throwCriticalException("�y�x���zUvFlipper::setActivePtn �����̃p�^�[���ԍ�="<<prm_pattno_uvflip<<"�́A�ő�p�^�[���ԍ��iNOT ����p�^�[���ԍ��j�𒴂��Ă��܂��B_pattno_uvflip_max="<<_pattno_uvflip_max<<" Texture="<<_pTexture->_texture_name);
    }
#endif
    _pattno_uvflip_now = prm_pattno_uvflip;
//    if (_pattno_uvflip_top <= prm_pattno_uvflip && prm_pattno_uvflip <= _pattno_uvflip_bottom) {
//        _pattno_uvflip_now = prm_pattno_uvflip;
//    } else if (prm_pattno_uvflip < _pattno_uvflip_top) {
//        _pattno_uvflip_now = _pattno_uvflip_top;
//    } else if (prm_pattno_uvflip > _pattno_uvflip_bottom) {
//        _pattno_uvflip_now = _pattno_uvflip_bottom;
//    }
}

void UvFlipper::setFlipPtnRange(int prm_top, int prm_bottom) {
#ifdef MY_DEBUG
    if (prm_top < 0) {
        _TRACE_(FUNC_NAME<<" prm_top="<<prm_top<<" TOP�����ł��B�Ӑ}���Ă܂����H");
    }
    if (prm_top > prm_bottom) {
        throwCriticalException("prm_top="<<prm_top<<",prm_bottom="<<prm_bottom<<" �召�����������ł��BTexture="<<_pTexture->_texture_name);
    }
#endif
    _pattno_uvflip_top = prm_top;
    _pattno_uvflip_bottom = prm_bottom;
}

void UvFlipper::exec(UvFlippingMethod prm_method, int prm_interval) {
    _uvflip_method = prm_method;
    _uvflip_interval_frames = prm_interval;
    _is_reverse_order_in_oscillate_animation_flg = false;
}

void UvFlipper::behave() {
//    _TRACE_(getName()<<":_pattno_uvflip_now="<<_pattno_uvflip_now<<"/_pattno_uvflip_bottom="<<_pattno_uvflip_bottom<<"/_pattno_uvflip_top="<<_pattno_uvflip_top<<"/_is_reverse_order_in_oscillate_animation_flg="<<_is_reverse_order_in_oscillate_animation_flg<<"");
#ifdef MY_DEBUG
    if (_paUV == nullptr) {
        throwCriticalException("���O��locatePatternNo()�Ńp�^�[�����Ă��������B_pTexture="<<_pTexture->getName());
    }
#endif
    _frame_counter_uvflip++;
    if (_uvflip_method == NOT_ANIMATED) {
        return;
    }
    if (_uvflip_interval_frames < _frame_counter_uvflip) {
        switch (_uvflip_method) {
            case FLIP_ORDER_LOOP: {  //��F0,1,2,3,4,5,0,1,2,3,4,5,...
                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                    _pattno_uvflip_now++;
                } else {
                    _pattno_uvflip_now = _pattno_uvflip_top;
                }
                break;
            }
            case FLIP_REVERSE_LOOP: {  //��F5,4,3,2,1,0,5,4,3,2,1,0,5,4...
                if (_pattno_uvflip_top < _pattno_uvflip_now) {
                    _pattno_uvflip_now--;
                } else {
                    _pattno_uvflip_now = _pattno_uvflip_bottom;
                }
                break;
            }
            case FLIP_ORDER_NOLOOP: {  //��F0,1,2,3,4,5,5,5,5,5,5,5...
                if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                    _pattno_uvflip_now++;
                } else {
                    _pattno_uvflip_now = _pattno_uvflip_bottom;
                    //_pTexture->onCatchEvent(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED, this); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                    _uvflip_method = NOT_ANIMATED;
                }
                break;
            }
            case FLIP_REVERSE_NOLOOP: { //��F5,4,3,2,1,0,0,0,0,0,0...
                if (_pattno_uvflip_top < _pattno_uvflip_now) {
                    _pattno_uvflip_now--;
                } else {
                    _pattno_uvflip_now = _pattno_uvflip_top;
                    //_pTexture->onCatchEvent(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED, this); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                    _uvflip_method = NOT_ANIMATED;
                }
                break;
            }
            case FLIP_OSCILLATE_LOOP: { //��F0,1,2,3,4,5,4,3,2,1,0,1,2,3,4,5,...
                if (_is_reverse_order_in_oscillate_animation_flg) { //�t������
                    if (_pattno_uvflip_top < _pattno_uvflip_now) {
                        _pattno_uvflip_now--;
                    } else {
                        _pattno_uvflip_now++;
                        _is_reverse_order_in_oscillate_animation_flg = false;
                    }
                } else {                                            //��������
                    if (_pattno_uvflip_bottom > _pattno_uvflip_now) {
                        _pattno_uvflip_now++;
                    } else {
                        _pattno_uvflip_now--;
                        _is_reverse_order_in_oscillate_animation_flg = true;
                    }
                }
                break;
            }
            case FLIP_CUSTOMIZED_LOOP: {
                if (_pa_ptn_offset_customized) {
                    _pattno_uvflip_now = _pa_ptn_offset_customized[_cnt_customized];
                    _cnt_customized ++;
                    if (_cnt_customized == _ptn_customized) {
                        _cnt_customized = 0;
                    }
                }
                break;
            }
            case FLIP_CUSTOMIZED_NOLOOP: {
                if (_pa_ptn_offset_customized) {
                    _pattno_uvflip_now = _pa_ptn_offset_customized[_cnt_customized];
                    _cnt_customized ++;
                    if (_cnt_customized == _ptn_customized) {
                        //_pTexture->onCatchEvent(GGAF_EVENT_NOLOOP_UVFLIP_FINISHED, this); //�����A�j���[�V�����͐i�܂Ȃ����Ƃ�ʒm
                        _cnt_customized = 0;
                        _uvflip_method = NOT_ANIMATED;
                    }
                }
                break;
            }
            case NOT_ANIMATED: {
                //�������Ȃ�
                break;
            }
            default:
                break;
        }

        _frame_counter_uvflip = 0;
    }
}

void UvFlipper::customizePtnOrder(int prm_aPtnOffset[], int prm_num) {
    if (_pa_ptn_offset_customized) {
        GGAF_DELETEARR_NULLABLE(_pa_ptn_offset_customized);
    }
    _pa_ptn_offset_customized = NEW int[prm_num];
    _ptn_customized = prm_num;
    for (int i = 0; i < prm_num; i++) {
        _pa_ptn_offset_customized[i] = prm_aPtnOffset[i];
    }
}

void UvFlipper::getUV(float& out_u, float& out_v) {
    out_u = _base_u + _paUV[_pattno_uvflip_now]._u;
    out_v = _base_v + _paUV[_pattno_uvflip_now]._v;
}

void UvFlipper::getUV(int prm_pattno_uvflip, float& out_u, float& out_v) {
#ifdef MY_DEBUG
    if (prm_pattno_uvflip > _pattno_uvflip_max) {
        throwCriticalException("�����̃p�^�[���ԍ�="<<prm_pattno_uvflip<<"�́A�͈͊O�ł��B_pattno_uvflip_max="<<_pattno_uvflip_max<<" Texture="<<_pTexture->_texture_name);
    }
#endif
    out_u = _base_u + _paUV[prm_pattno_uvflip]._u;
    out_v = _base_v + _paUV[prm_pattno_uvflip]._v;
}

UvFlipper::~UvFlipper() {
    GGAF_DELETEARR_NULLABLE(_paUV);
    GGAF_DELETEARR_NULLABLE(_pa_ptn_offset_customized);
}
