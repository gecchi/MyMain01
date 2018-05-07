#ifndef GGAFLIB_IFIXEDFONT_H_
#define GGAFLIB_IFIXEDFONT_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

namespace GgafLib {

template<class T, int N, int L>
class ICharacterChip {

    T* _pBaseActor;
public:

    /** [r/w]�x�[�X�̂P������(px) */
    pixcoord _chr_base_width_px;
    /** [r/w]�x�[�X�̂P��������(px) */
    pixcoord _chr_base_height_px;
    /** [r/w]�p�^�[���ԍ�0�Ƃ��镶�� */
    int _chr_ptn_zero;
    /** [r/w]�\���s�v�󔒂Ƃ��镶��(�w�肷��ƕ`�敶��������) */
    int _chr_blank;
    /** [r/w]���s�Ƃ��镶�� */
    int _chr_newline;
    /** [r]�`�敶���� */
    int* _draw_string;
    /** [r]�󂯓���\�ȕ�����(�����o�b�t�@�̒���) */
    int _max_len;
    /** [r]�����o�b�t�@ */
    int* _buf;
    struct InstancePart {
        float px_local_x;
        float px_local_y;
        float offset_u;
        float offset_v;
    };
    InstancePart* _paInstancePart;
    /** [r]������ */
    int _len;
    /** [r]�`�敶�����i�����񒷂�����s�Ƌ󔒂��������l�j*/
    int _draw_chr_num;
    /** [r]�����o�b�t�@�̕�����̍s�P�ʂ̕�(px) */
    pixcoord _px_row_width[L];
    /** [r]�����o�b�t�@�̕�����̍s�� */
    int _nn;
    /** [r/w]�e�����Ԋu(px) */
    pixcoord _px_chr_width[N];
    bool _is_fixed_width;

    pixcoord _px_total_width;
    pixcoord _px_total_height;
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

    /**
     * �S�Ă̕����̐ݒ�Bupdate() �ɂ��\���������X�V���Ȃ��Ɣ��f����܂���B .
     * @param prm_width_ratio ���̗�(�����l�̕��ɏ悶��l�A�����l��1.0)
     */
    inline void setBaseChrWidth(pixcoord prm_width_px) {
        _is_fixed_width = true;
        _chr_base_width_px = prm_width_px;
        pixcoord* p = _px_chr_width;
        for (int i = 0; i < N; i++) {
            *p = prm_width_px;
            ++p;
        }
    }

    /**
     * �����̕��̔䗦���X�ɐݒ�Bupdate() �ɂ��\���������X�V���Ȃ��Ɣ��f����܂���B .
     * @param c ����
     * @param prm_width_ratio ���̗�(�����l�̕��ɏ悶��l�A�����l��1.0)
     */
    inline void setChrWidthRatio(const unsigned char c, double prm_width_ratio) {
        _is_fixed_width = false;
        _px_chr_width[c] = _chr_base_width_px * prm_width_ratio;
    }
    /**
     * �󔒂̕�����ݒ肷�� .
     * �󔒂̕����͕`�揈�����X�L�b�v�����̂ŁA�p�t�H�[�}���X�����シ��B
     * �f�t�H���g�� ' ' ���ݒ肳��Ă���B
     * @param prm_c �󔒕���
     */
    inline void setBlankChr(char prm_c) {
        _chr_blank = (int)prm_c;
    }

    /**
     * ���s������ݒ肷�� .
     * �f�t�H���g�� '\n' ���ݒ肳��Ă���B
     * @param prm_c
     */
    inline void setNewlineChr(char prm_c) {
        _chr_newline = (int)prm_c;
    }

    /**
     * UvFlipper�̃p�^�[���ԍ�0�ԂƂ��镶����ݒ肷�� .
     * �f�t�H���g�� ' ' ���ݒ肳��Ă���B
     * @param prm_c
     */
    inline void setPatternZeroChr(char prm_c) {
        _chr_ptn_zero = (int)prm_c;
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

    inline int getDrawStringLength() {
        return _len;
    }
    inline pixcoord getTotalWidth() {
        return _px_total_width;
    }
    inline pixcoord getTotalHeight() {
        return _px_total_height;
    }

public:
    ICharacterChip(T* prm_pBaseActor, int prm_chr_base_width_px, int prm_chr_base_height_px);

    virtual ~ICharacterChip();

};

template<class T, int N, int L>
ICharacterChip<T, N, L>::ICharacterChip(T* prm_pBaseActor, int prm_chr_base_width_px, int prm_chr_base_height_px) :
_pBaseActor(prm_pBaseActor),
_chr_base_width_px(prm_chr_base_width_px),
_chr_base_height_px(prm_chr_base_height_px)
{
    _max_len = 8;  //�ŏ��̓o�b�t�@��8����
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper �� �p�^�[��0�Ԃ̕����B
    _chr_blank = (int)(' ');
    _chr_newline = (int)('\n');
    _len = 0;
    _draw_chr_num = 0;
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstancePart = NEW InstancePart[_max_len];
    _draw_string = _buf;
    for (int i = 0; i < L; i++) {
        _px_row_width[i] = 0;
    }
    _nn = 0;
    _is_fixed_width = false;
    //�f�t�H���g�̂P�����̕�(px)�ݒ�
    for (int i = 0; i < N; i++) {
        _px_chr_width[i] = _chr_base_width_px;
    }
    _px_total_width = 0;
    _px_total_height = 0;
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //���߂W�̔{���ɐ؂�グ
    GGAF_DELETEARR(_buf);
    GGAF_DELETEARR(_paInstancePart);
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstancePart = NEW InstancePart[_max_len];
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare1(const char* prm_str) {
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
    pixcoord max_width_line_px = 0;

    *p_width_line_px = 0;
    _nn = 0;
    _draw_chr_num = 0;
    int c;
    const int chr_blank = _chr_blank;
    const bool is_fixed_width = _is_fixed_width;
    const pixcoord chr_base_width_px = _chr_base_width_px;
    while (true) {
        c = (int)(*p_prm_str);
#ifdef MY_DEBUG
        if (0 > c || c > (N-1)) {
            throwGgafCriticalException("�͈͊O�̈����Ȃ������킪����܂��� prm_str=["<<prm_str<<"] �̒��̒l:"<<c<<"�B 0�`"<<(N-1)<<"�͈̔͂ɂ��ĉ������Bthis="<<this);
        }
#endif
        if (c != (*p_draw_string)) {
            is_different = true;
            *p_draw_string = c; //�ۑ�
        }
        if (c == _chr_newline) {
            if (_nn == 0 || max_width_line_px < *p_width_line_px) {
                max_width_line_px = *p_width_line_px;
            }
            _nn++; //�s���J�E���g
            ++p_width_line_px;  *p_width_line_px = 0; //�s�̕��ێ��z������� �� 0�Ƀ��Z�b�g
        } else if (c == '\0') {
            if (_nn == 0 || max_width_line_px < *p_width_line_px) {
                max_width_line_px = *p_width_line_px;
            }
            _nn++; //������Ō���s���P�Ƃ��ăJ�E���g�B������͉��s�ŏI���K�v���Ȃ��B
            break;
        } else {
            *p_width_line_px += (is_fixed_width ? chr_base_width_px : _px_chr_width[c]); //�s�̕�(px)�����Z
        }
        if (c != chr_blank) { //�u�����N
            _draw_chr_num++; //�`�敶�����J�E���g
        }
        ++p_prm_str;  ++p_draw_string;
    }
    _px_total_width = max_width_line_px;
    _px_total_height = _chr_base_height_px*_nn;
    if (is_different) {
        prepare2();
    }
#ifdef MY_DEBUG
    if (_nn > L) {
        throwGgafCriticalException("������̍s����"<<L<<"�𒴂��܂����Bname="<<_pBaseActor->getName()<<" prm_str="<<prm_str);
    }
#endif
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare2() {
    //ALIGN_RIGHT ��VALIGN_BOTTOM �ׂ̈�
    //�ǂ����Ă��Q��S���������[�v�łȂ߂�K�v������B
    //prepare1() �͂P��ڂ̃��[�v�A prepare2() �͂Q��ڂ̃��[�v�ɑ���
    if (_len == 0) {
        return;
    }
    const GgafDxAlign align  = _pBaseActor->_align;
    const GgafDxValign valign = _pBaseActor->_valign;
    const pixcoord chr_base_height_px = _chr_base_height_px;
    const pixcoord chr_base_width_px = _chr_base_width_px;
    const int chr_newline = _chr_newline;
    const int chr_blank = _chr_blank;
    const int chr_ptn_zero = _chr_ptn_zero;
    GgafDxCore::GgafDxUvFlipper* pUvFlipper = _pBaseActor->getUvFlipper();
    if (_is_fixed_width) {
        //�Œ蕝��
        //����Y�ʒu�����߂�
        pixcoord px_y, px_x;
        int nnn = 0; // num of \n now
        if (align == ALIGN_CENTER) {
            px_x = -(_px_row_width[nnn]/2);
        } else if (align == ALIGN_RIGHT) {
            px_x = -(_px_row_width[nnn]);
        } else {  //ALIGN_LEFT
            px_x = 0;
        }
        if (valign == VALIGN_BOTTOM) {
            px_y = -_px_total_height;
        } else if (valign == VALIGN_MIDDLE) {
            px_y = -(_px_total_height/2);
        } else { //VALIGN_TOP
            px_y = 0;
        }
        float u, v;
        int* p_chr  = _draw_string;
        InstancePart* pInstancePart = _paInstancePart;
        while(true) { //�e�����P�ʂ̃��[�v
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\0')) {
                break; //�����܂�
            } else if (draw_chr == chr_newline) {
                nnn++;
                if (align == ALIGN_CENTER) {
                    px_x = -(_px_row_width[nnn]/2);
                } else if (align == ALIGN_RIGHT) {
                    px_x = -(_px_row_width[nnn]);
                } else {  //ALIGN_LEFT
                    px_x = 0;
                }
                px_y += chr_base_height_px;
                ++p_chr;
                continue; //�\�������͂Ȃ�
            }
            //���X�V
            if (draw_chr != chr_blank) {
                pInstancePart->px_local_x = px_x;
                pInstancePart->px_local_y = px_y;
                pUvFlipper->getUV(draw_chr-chr_ptn_zero, u, v);
                pInstancePart->offset_u = u;
                pInstancePart->offset_v = v;
                ++pInstancePart;
            }
            px_x += chr_base_width_px;
            ++p_chr;
        }
    } else {
        //�ϕ���
        //����Y�ʒu�����߂�
        pixcoord px_y = 0;
        if (align == ALIGN_LEFT || align == ALIGN_CENTER) {
            if (valign == VALIGN_BOTTOM) {
                px_y = -_px_total_height;
            } else if (valign == VALIGN_MIDDLE) {
                px_y = -(_px_total_height/2);
            } else { //VALIGN_TOP
                px_y = 0;
            }
            int nnn = 0; // num of \n now
            pixcoord px_x =  -(align == ALIGN_CENTER ? _px_row_width[nnn]/2 : 0);
            pixcoord x_tmp = px_x;
            float u, v;
            int* p_chr  = _draw_string;
            InstancePart* pInstancePart = _paInstancePart;
            while(true) { //�e�����P�ʂ̃��[�v
                int draw_chr = *p_chr;
                if (draw_chr == (int)('\0')) {
                    break; //�����܂�
                } else if (draw_chr == chr_newline) {
                    nnn++;
                    px_x = -(align == ALIGN_CENTER ? _px_row_width[nnn]/2 : 0);
                    x_tmp = px_x;
                    px_y += chr_base_height_px;
                    ++p_chr;
                    continue; //�\�������͂Ȃ�
                }
                //�v���|�[�V���i���ȕ��v�Z
                int w = ((chr_base_width_px - _px_chr_width[draw_chr]) / 2);
                px_x = x_tmp - w;
                x_tmp = px_x + chr_base_width_px - w;

                //���X�V
                if (draw_chr != chr_blank) {
                    pInstancePart->px_local_x = px_x;
                    pInstancePart->px_local_y = px_y;
                    pUvFlipper->getUV(draw_chr-chr_ptn_zero, u, v);
                    pInstancePart->offset_u = u;
                    pInstancePart->offset_v = v;
                    ++pInstancePart;
                }
                ++p_chr;
            }
        } else if (align == ALIGN_RIGHT) {
            if (valign == VALIGN_BOTTOM) {
                px_y = -chr_base_height_px;
            } else if (valign == VALIGN_MIDDLE) {
                px_y = ((_px_total_height/2) - chr_base_height_px);
            } else { //VALIGN_TOP
                px_y = ((_px_total_height*_nn) - chr_base_height_px);
            }

            //�E����\������
            pixcoord px_x = 0;
            pixcoord x_tmp = px_x;
            float u, v;
            int w;
            int* p_chr = &(_draw_string[_len-1]); //��������񂷁B_len �� strlen �̒l
            InstancePart* pInstancePart = &(_paInstancePart[_draw_chr_num - 1]);
            while (true) {
                int draw_chr = *p_chr;
                if (draw_chr == chr_newline) {
                    px_x = 0;
                    x_tmp = px_x;
                    px_y -= chr_base_height_px;
                    p_chr--;
                    continue;
                }
                //�v���|�[�V���i���ȕ��v�Z
                w = ((chr_base_width_px - _px_chr_width[draw_chr]) / 2);
                px_x = x_tmp - (w + _px_chr_width[draw_chr]);
                x_tmp = px_x + w;
                //���X�V
                if (draw_chr != chr_blank) {
                    pInstancePart->px_local_x = px_x;
                    pInstancePart->px_local_y = px_y;
                    pUvFlipper->getUV(draw_chr-chr_ptn_zero, u, v);
                    pInstancePart->offset_u = u;
                    pInstancePart->offset_v = v;
                    pInstancePart--;
                }
                if (p_chr == _draw_string) { //��ԍ��ɓ��B
                     break; //�����܂�
                }
                p_chr--;
            }
        }
    }
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    _pBaseActor->setPosition(X, Y);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    _pBaseActor->setPosition(X, Y, Z);
}
template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(const char* prm_str) {
    prepare1(prm_str);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    _pBaseActor->setPosition(X, Y);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, coord Z, const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    _pBaseActor->setPosition(X, Y, Z);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    _pBaseActor->setAlign(prm_align, prm_valign);
}

template<class T, int N, int L>
ICharacterChip<T, N, L>::~ICharacterChip() {
     GGAF_DELETEARR(_buf);
     GGAF_DELETEARR(_paInstancePart);
}

}

#endif /*GGAFLIB_IFIXEDFONT_H_*/
