#ifndef GGAFLIB_IFIXEDFONT_H_
#define GGAFLIB_IFIXEDFONT_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

namespace GgafLib {

template<class T>
class IFixedFont {

    T* _pBaseActor;
public:

    /** [r/w]�x�[�X�̂P������(px) */
    const pixcoord _chr_width_px;
    /** [r/w]�x�[�X�̂P��������(px) */
    const pixcoord _chr_height_px;
    /** [r/w]�p�^�[���ԍ�0�Ƃ��镶�� */
    int _chr_ptn_zero;
    /** [r/w]�\���s�v�󔒂Ƃ��镶��(�w�肷��ƕ`�敶��������) */
    int _chr_blank;
    /** [r]�`�敶���� */
    int* _draw_string;
    /** [r]�󂯓���\�ȕ�����(�����o�b�t�@�̒���) */
    int _max_len;
    /** [r]�����o�b�t�@ */
    int* _buf;
    struct InstacePart {
        float px_local_x;
        float px_local_y;
        float offset_u;
        float offset_v;
    };
    InstacePart* _paInstacePart;
    /** [r]������ */
    int _len;
    /** [r]�`�敶�����i�����񒷂�����s�Ƌ󔒂��������l�j*/
    int _draw_chr_num;
    /** [r]�����o�b�t�@�̕�����̍s�P�ʂ̕�(px) */
    pixcoord _px_row_width[1024];
    /** [r]�����o�b�t�@�̕�����̍s�� */
    int _nn;

    /**
     * �����o�b�t�@���������̒���8�̔{���̐؂�グ�ɕύX .
     * @param prm_max_len �V�����o�b�t�@��
     */
    void chengeBufferLen(int prm_max_len);

public:
    /**
     * �`�敶�����X�V�ݒ� .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, const char* prm_str);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(const char* prm_str);

    /**
     * �`�敶�����X�V�ݒ� .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    virtual void prepare1(const char* prm_str);
    virtual void prepare2();
    /**
     * �`�敶�����X�V���ꂽ���ɌĂяo�����R�[���o�b�N .
     * ���ʂŎ������Ă��������B
     */
    virtual void onUpdate() {
    }

    inline void getDrawString(char* out_paCh) {
        int len = _len;
        for (int i = 0; i < len; i++) {
            out_paCh[i] = _draw_string[i];
        }
        out_paCh[len] = '\0';
    }

    inline std::string getDrawString() {
        int len = _len;
        char* paCh = NEW char[len+1];
        getDrawString(paCh);
        std::string s = paCh;
        GGAF_DELETEARR(paCh);
        return s;
    }


public:
    IFixedFont(T* prm_pBaseActor, int prm_chr_width_px, int prm_chr_height_px);

    virtual ~IFixedFont();

};

template<class T>
IFixedFont<T>::IFixedFont(T* prm_pBaseActor, int prm_chr_width_px, int prm_chr_height_px) :
_pBaseActor(prm_pBaseActor),
_chr_width_px(prm_chr_width_px),
_chr_height_px(prm_chr_height_px)
{
    _max_len = 8;  //�ŏ��̓o�b�t�@��8����
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper �� �p�^�[��0�Ԃ̕����B
    _chr_blank = (int)(' ');
    _len = 0;
    _draw_chr_num = 0;
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstacePart = NEW InstacePart[_max_len];
    _draw_string = _buf;
    for (int i = 0; i < 1024; i++) {
        _px_row_width[i] = 0;
    }
    _nn = 0;
}

template<class T>
void IFixedFont<T>::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //���߂W�̔{���ɐ؂�グ
    GGAF_DELETEARR(_buf);
    GGAF_DELETEARR(_paInstacePart);
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstacePart = NEW InstacePart[_max_len];
}

template<class T>
void IFixedFont<T>::prepare1(const char* prm_str) {
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
            *p_width_line_px += _chr_width_px; //�s�̕�(px)�����Z
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
        throwGgafCriticalException("������̍s����1024�𒴂��܂����Bname="<<_pBaseActor->getName()<<" prm_str="<<prm_str);
    }
#endif
}

template<class T>
void IFixedFont<T>::prepare2() {
    //ALIGN_RIGHT ��VALIGN_BOTTOM �ׂ̈�
    //�ǂ����Ă��Q��S���������[�v�łȂ߂�K�v������B
    //prepare1() �͂P��ڂ̃��[�v�A prepare2() �͂Q��ڂ̃��[�v�ɑ���
    if (_len == 0) {
        return;
    }
    //����Y�ʒu�����߂�
    pixcoord px_y, px_x;
    int nnn = 0; // num of \n now
    if (_pBaseActor->_align == ALIGN_CENTER) {
        px_x = -(_px_row_width[nnn]/2);
    } else if (_pBaseActor->_align == ALIGN_RIGHT) {
        px_x = -(_px_row_width[nnn]);
    } else {  //ALIGN_LEFT
        px_x = 0;
    }
    if (_pBaseActor->_valign == VALIGN_BOTTOM) {
        px_y = -(_chr_height_px*_nn);
    } else if (_pBaseActor->_valign == VALIGN_MIDDLE) {
        px_y = -(_chr_height_px*_nn/2);
    } else { //VALIGN_TOP
        px_y = 0;
    }
    int chr_blank = _chr_blank;
    int chr_ptn_zero = _chr_ptn_zero;
    float u, v;
    int* p_chr  = _draw_string;
    InstacePart* pInstacePart = _paInstacePart;
    while(true) { //�e�����P�ʂ̃��[�v
        int draw_chr = *p_chr;
        if (draw_chr == (int)('\0')) {
            break; //�����܂�
        } else if (draw_chr == (int)('\n')) {
            nnn++;
            if (_pBaseActor->_align == ALIGN_CENTER) {
                px_x = -(_px_row_width[nnn]/2);
            } else if (_pBaseActor->_align == ALIGN_RIGHT) {
                px_x = -(_px_row_width[nnn]);
            } else {  //ALIGN_LEFT
                px_x = 0;
            }
            px_y += _chr_height_px;
            p_chr++;
            continue; //�\�������͂Ȃ�
        }
        //���X�V
        if (draw_chr != chr_blank) {
            pInstacePart->px_local_x = px_x;
            pInstacePart->px_local_y = px_y;
            _pBaseActor->getUvFlipper()->getUV(draw_chr-chr_ptn_zero, u, v);
            pInstacePart->offset_u = u;
            pInstacePart->offset_v = v;
            pInstacePart++;
        }
        px_x += _chr_width_px;
        p_chr++;
    }
}

template<class T>
void IFixedFont<T>::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    _pBaseActor->position(X, Y);
}

template<class T>
void IFixedFont<T>::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    _pBaseActor->position(X, Y, Z);
}
template<class T>
void IFixedFont<T>::update(const char* prm_str) {
    prepare1(prm_str);
}

template<class T>
void IFixedFont<T>::update(coord X, coord Y, const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    _pBaseActor->position(X, Y);
}

template<class T>
void IFixedFont<T>::update(coord X, coord Y, coord Z, const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    _pBaseActor->position(X, Y, Z);
}

template<class T>
void IFixedFont<T>::update(const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    _pBaseActor->setAlign(prm_align, prm_valign);
}

template<class T>
IFixedFont<T>::~IFixedFont() {
     GGAF_DELETEARR(_buf);
     GGAF_DELETEARR(_paInstacePart);
}

}

#endif /*GGAFLIB_IFIXEDFONT_H_*/
