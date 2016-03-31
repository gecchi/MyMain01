#ifndef GGAFLIB_IPROPORTIONALFONT_H_
#define GGAFLIB_IPROPORTIONALFONT_H_
#include "GgafLibCommonHeader.h"
#include "ICharacterChip.hpp"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

namespace GgafLib {

template<class T>
class IProportionalFont : public ICharacterChip<T> {

public:
    /** [r/w]�e�����Ԋu(px) */
    pixcoord _px_chr_width[256];
public:
    /**
     * �R���X�g���N�^
     * @param prm_name �m�[�h���́i���j�[�N�ɂ��ĉ������j
     */
    IProportionalFont(T* prm_pBaseActor, int prm_chr_width_px, int prm_chr_height_px);

    virtual void prepare1(const char* prm_str) override;

    virtual void prepare2() override;

    /**
     * �S�Ă̕����̕��̔䗦��ݒ�
     * @param prm_width_ratio ���̗�(�����l�̕��ɏ悶��l�A�����l��1.0)
     */
    inline void setAllChrWidthRatio(double prm_width_ratio) {
        pixcoord* p = _px_chr_width;
        for (int i = 0; i < 256; i++) {
            *p = _chr_width_px * prm_width_ratio;
            p++;
        }
    }

    /**
     * �����̕��̔䗦���X�ɐݒ� .
     * @param c ����
     * @param prm_width_ratio ���̗�(�����l�̕��ɏ悶��l�A�����l��1.0)
     */
    inline void setChrWidthRatio(const char c, double prm_width_ratio) {
        _px_chr_width[c] = _chr_width_px * prm_width_ratio;
    }

    /**
     * �f�X�g���N�^�B���c���[�m�[�h���������B .
     */
    virtual ~IProportionalFont();
};



///////////////////////////////////////////////////////////////// ��������͎�����

template<class T>
IProportionalFont<T>::IProportionalFont(T* prm_pBaseActor, int prm_chr_width_px, int prm_chr_height_px) :
    ICharacterChip<T>(prm_pBaseActor,prm_chr_width_px,prm_chr_height_px)
{

}

template<class T>
void IProportionalFont<T>::prepare1(const char* prm_str) {
    _len = strlen(prm_str);
    if (_len+1 > _max_len) {
        chengeBufferLen(_len+1); //�o�b�t�@�g��
    }
    onUpdate(); //�R�[���o�b�N
    _draw_string = _buf;
    //�ێ�(_draw_string)����A���Ȃ�����s��(_nn)�����߂�A
    //���łɊe�s�P�ʂ̕���(_px_row_width)�����߂Ă���
    bool is_different = false;
    const char* p_prm_str = prm_str;
    int* p_draw_string = _draw_string;
    pixcoord* p_width_line_px = _px_row_width;
    *p_width_line_px = 0;
    _nn = 0;
    _draw_chr_num = 0;
    int c;
    int chr_blank = _chr_blank;
    while (true) {
        c = (int)(*p_prm_str);
#ifdef MY_DEBUG
        if (0 > c || c > 255) {
            throwGgafCriticalException("�͈͊O�̈����Ȃ������킪����܂��� prm_str=["<<prm_str<<"] �̒��̒l:"<<c<<"�B 0�`255�͈̔͂ɂ��ĉ������Bthis="<<this);
        }
#endif
        if (c != (*p_draw_string)) {
            is_different = true;
            *p_draw_string = c; //�ۑ�
        }
        if (c == '\n') {
            _nn++; //�s���J�E���g
            p_width_line_px++;  *p_width_line_px = 0; //�s�̕��ێ��z������� �� 0�Ƀ��Z�b�g
        } else if (c == '\0') {
            _nn++; //������Ō���s���P�Ƃ��ăJ�E���g�B������͉��s�ŏI���K�v���Ȃ��B
            break;
        } else {
            *p_width_line_px += _px_chr_width[c]; //�s�̕�(px)�����Z
        }
        if (c != chr_blank) { //�u�����N
            _draw_chr_num++; //�`�敶�����J�E���g
        }
        p_prm_str++;  p_draw_string++;
    }
    if (is_different) {
        prepare2();
    }
#ifdef MY_DEBUG
    if (_nn > 1024) {
        throwGgafCriticalException("������̍s����1024�𒴂��܂����Bname="<<getName()<<" prm_str="<<prm_str);
    }
#endif
}

template<class T>
void IProportionalFont<T>::prepare2() {
    //ALIGN_RIGHT ��VALIGN_BOTTOM �ׂ̈�
    //�ǂ����Ă��Q��S���������[�v�łȂ߂�K�v������B
    //update() �͂P��ڂ̃��[�v�A prepare2() �͂Q��ڂ̃��[�v�ɑ���
    if (_len == 0) {
        return;
    }
    //����Y�ʒu�����߂�
    pixcoord px_y = 0;
    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        if (_valign == VALIGN_BOTTOM) {
            px_y = -(_chr_height_px*_nn);
        } else if (_valign == VALIGN_MIDDLE) {
            px_y = -(_chr_height_px*_nn/2);
        } else { //VALIGN_TOP
            px_y = 0;
        }
        int chr_blank = _chr_blank;
        int chr_ptn_zero = _chr_ptn_zero;
        int nnn = 0; // num of \n now
        pixcoord px_x =  -(_align == ALIGN_CENTER ? _px_row_width[nnn]/2 : 0);
        pixcoord x_tmp = px_x;
        float u, v;
        int* p_chr  = _draw_string;
        InstacePart* pInstacePart = _paInstacePart;
        while(true) { //�e�����P�ʂ̃��[�v
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\0')) {
                break; //�����܂�
            } else if (draw_chr == (int)('\n')) {
                nnn++;
                px_x = -(_align == ALIGN_CENTER ? _px_row_width[nnn]/2 : 0);
                x_tmp = px_x;
                px_y += _chr_height_px;
                p_chr++;
                continue; //�\�������͂Ȃ�
            }
            //�v���|�[�V���i���ȕ��v�Z
            int w = ((_chr_width_px - _px_chr_width[draw_chr]) / 2);
            px_x = x_tmp - w;
            x_tmp = px_x + _chr_width_px - w;

            //���X�V
            if (draw_chr != chr_blank) {
                pInstacePart->px_local_x = px_x;
                pInstacePart->px_local_y = px_y;
                getUvFlipper()->getUV(draw_chr-chr_ptn_zero, u, v);
                pInstacePart->offset_u = u;
                pInstacePart->offset_v = v;
                pInstacePart++;
            }
            p_chr++;
        }
    } else if (_align == ALIGN_RIGHT) {
        if (_valign == VALIGN_BOTTOM) {
            px_y = -_chr_height_px;
        } else if (_valign == VALIGN_MIDDLE) {
            px_y = ((_chr_height_px*_nn/2) - _chr_height_px);
        } else { //VALIGN_TOP
            px_y = ((_chr_height_px*_nn) - _chr_height_px);
        }

        //�E����\������
        int chr_blank = _chr_blank;
        int chr_ptn_zero = _chr_ptn_zero;
        pixcoord px_x = 0;
        pixcoord x_tmp = px_x;
        float u, v;
        int w;
        int* p_chr = &(_draw_string[_len-1]); //��������񂷁B_len �� strlen �̒l
        InstacePart* pInstacePart = &(_paInstacePart[_draw_chr_num - 1]);
        while (true) {
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\n')) {
                px_x = 0;
                x_tmp = px_x;
                px_y -= _chr_height_px;
                p_chr--;
                continue;
            }
            //�v���|�[�V���i���ȕ��v�Z
            w = ((_chr_width_px - _px_chr_width[draw_chr]) / 2);
            px_x = x_tmp - (w + _px_chr_width[draw_chr]);
            x_tmp = px_x + w;
            //���X�V
            if (draw_chr != chr_blank) {
                pInstacePart->px_local_x = px_x;
                pInstacePart->px_local_y = px_y;
                getUvFlipper()->getUV(draw_chr-chr_ptn_zero, u, v);
                pInstacePart->offset_u = u;
                pInstacePart->offset_v = v;
                pInstacePart--;
            }
            if (p_chr == _draw_string) { //��ԍ��ɓ��B
                 break; //�����܂�
            }
            p_chr--;
        }
    }
}

template<class T>
IProportionalFont<T>::~IProportionalFont() {
    GGAF_DELETE_NULLABLE(_pProg);
}

}
#endif /*GGAFLIB_IPROPORTIONALFONT_H_*/
