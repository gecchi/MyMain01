#ifndef GGAF_LIB_IFIXEDFONT_H_
#define GGAF_LIB_IFIXEDFONT_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/dx/actor/supporter/UvFlipper.h"
#include <string.h>

namespace GgafLib {

/**
 * �����\���p�C���^�[�t�F�C�X .
 * UvFlipper�̃p�^�[���ԍ�0�ԂƂ��镶���́A
 * �f�t�H���g�� ' ' (32) ���ݒ肳��Ă���B
 * @tparam T �����N���X
 * @tparam N �L�����̎�ސ�
 * @tparam L �ő�\���s��
 */
template<class T, int N, int L>
class ICharacterChip {

    T* _pBaseActor;
public:

    /** [r/w]�x�[�X�̂P������(px) */
    pixcoord _chr_base_width_px;
    /** [r/w]�x�[�X�̂P��������(px) */
    pixcoord _chr_base_height_px;
    /** [r/w]�p�^�[���ԍ�0�Ƃ��镶��(�f�t�H���g��' '(32))  */
    int _chr_ptn_zero;
    /** [r/w]�\���s�v�󔒂Ƃ��镶��(�w�肷��ƕ`�敶��������) */
    int _chr_blank;
    /** [r/w]���s�Ƃ��镶�� */
    int _chr_newline;
    /** [r]�`�敶���� */
    int* _draw_string;
    /** [r]�󂯓���\�ȕ�����(�����o�b�t�@�̒���) */
    int _max_buf;
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
     * @param prm_max_buf �V�����o�b�t�@��
     */
    void extendBuffer(int prm_max_buf);
    virtual void prepare1(const char* prm_str);
    virtual void prepare1(const int prm_append_chr);
    virtual void prepare1_append(const char* prm_str);
    virtual void prepare1_append(const int prm_append_chr);
    virtual void prepare1_delete(int prm_delete_byte_num);
    virtual void prepare2();
public:
    /**
     * �L�����N�^�p�^�[���ԍ����\���͈͓������ׂ� .
     * @param prm_chr  �L�����N�^�p�^�[���ԍ�
     * @return true:�͈͓��^false�F�͈͊O
     */
    inline bool isDispChr(const int prm_chr) {
        int max_ptnno = _pBaseActor->getUvFlipper()->getMaxPtnno();
        if (max_ptnno < prm_chr - _chr_ptn_zero) {
            //�͈͊O
            return false;
        } else {
            return true;
        }
    }

    /**
     * �`�敶�����X�V�ݒ� .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, const char* prm_str);
    virtual void update(coord X, coord Y, const int prm_chr);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Z �v���C�I���e�B(�l��������������O)
     * @param prm_str �`�敶����
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    virtual void update(coord X, coord Y, coord Z, const int prm_chr);

    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     */
    virtual void update(const char* prm_str);
    virtual void update(const int prm_chr);

    /**
     * �`�敶�����X�V�ݒ� .
     * @param X X���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param Y Y���W(�s�N�Z�� : ���W �� 1 : LEN_UNIT)
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        Align prm_align,
                        Valign prm_valign);

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
                        Align prm_align,
                        Valign prm_valign);
    /**
     * �`�敶�����X�V�ݒ�  .
     * @param prm_str �`�敶����
     * @param prm_align ALIGN_LEFT:X���W�͕�����̍��[�^ALIGN_CENTER:X���W�͕�����̐^�񒆁^ALIGN_RIGHT:X���W�͉E�[
     * @param prm_valign VALIGN_TOP:Y���W�͕�����̍����̏�Ӂ^VALIGN_MIDDLE:Y���W�͕�����̍����̐^�񒆁^VALIGN_BOTTOM:Y���W�͕�����̍����̒��
     */
    virtual void update(const char* prm_str,
                        Align prm_align,
                        Valign prm_valign);

    /**
     * �`�敶����ǉ����čX�V�ݒ�  .
     * update() ���A���v�Z�����ǉ��������Ɍ��肷��̂ŁA�኱�p�t�H�[�}���X���ǂ��B
     * @param prm_str �ǉ����镶����
     */
    virtual void appendUpdate(const char* prm_str);

    /**
    * �`�敶����ǉ����čX�V�ݒ�  .
     * update() ���A���v�Z�����ǉ��������Ɍ��肷��̂ŁA�኱�p�t�H�[�}���X���ǂ��B
     * @param prm_c �ǉ�����ASCII������(0�`255)
     */
    virtual void appendUpdate(const int prm_c);

    /**
     * �`�敶���𖖔����珜�����čX�V�ݒ�  .
     * update() ���A�኱�p�t�H�[�}���X���ǂ��B
     * ���s���P�����Ƃ��Ĉ�����
     * @param prm_delete_byte_num �폜������
     */
    virtual void deleteUpdate(int prm_delete_byte_num);

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
    inline void setBlankChr(int prm_c) {
        _chr_blank = prm_c;
    }

    /**
     * ���s������ݒ肷�� .
     * �f�t�H���g�� '\n' ���ݒ肳��Ă���B
     * @param prm_c
     */
    inline void setNewlineChr(int prm_c) {
        _chr_newline = prm_c;
    }

    /**
     * UvFlipper�̃p�^�[���ԍ�0�ԂƂ��镶����ݒ肷�� .
     * �f�t�H���g�� ' ' ���ݒ肳��Ă���B
     * @param prm_c
     */
    inline void setPatternZeroChr(int prm_c) {
        _chr_ptn_zero = prm_c;
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
    /**
     * �R���X�g���N�^ .
     * @param prm_pBaseActor this��n��
     * @param prm_chr_base_width_px  ��{�ƂȂ�P�����̉���(px)
     * @param prm_chr_base_height_px ��{�ƂȂ�P�����̍�����(px)
     */
    ICharacterChip(T* prm_pBaseActor, int prm_chr_base_width_px, int prm_chr_base_height_px);

    virtual ~ICharacterChip();

};

template<class T, int N, int L>
ICharacterChip<T, N, L>::ICharacterChip(T* prm_pBaseActor, int prm_chr_base_width_px, int prm_chr_base_height_px) :
_pBaseActor(prm_pBaseActor),
_chr_base_width_px(prm_chr_base_width_px),
_chr_base_height_px(prm_chr_base_height_px)
{
    _max_buf = 8;  //�ŏ��̓o�b�t�@��8����
    _chr_ptn_zero = (int)(' '); //UvFlipper �� �p�^�[��0�Ԃ̕����B
    _chr_blank = (int)(' ');
    _chr_newline = (int)('\n');
    _len = 0;
    _draw_chr_num = 0;
    _buf = NEW int[_max_buf];
    _buf[0] = (int)('\0');
    _paInstancePart = NEW InstancePart[_max_buf];
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
void ICharacterChip<T, N, L>::extendBuffer(int prm_max_buf) {
    _max_buf = 8*((prm_max_buf+8)/8); //���߂W�̔{���ɐ؂�グ
    GGAF_DELETEARR(_buf);
    GGAF_DELETEARR(_paInstancePart);
    _buf = NEW int[_max_buf];
    _buf[0] = (int)('\0');
    _paInstancePart = NEW InstancePart[_max_buf];
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare1(const char* prm_str) {
    _len = (int)strlen(prm_str);
    if (_len+1 > _max_buf) {
        extendBuffer(_len+1); //�o�b�t�@�g��
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
        if (0 > c || c > (N-1)) {
            _TRACE_("�y�x���zICharacterChip::prepare1() �͈͊O�̈����Ȃ������킪����܂��� prm_str=["<<prm_str<<"] �̒��̒l:"<<c<<"�B 0�`"<<(N-1)<<"�͈̔͂ɂ��ĉ������Bthis="<<this);
            c = N-1;
        }
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
        throwCriticalException("ICharacterChip::prepare1() ������̍s����"<<L<<"�𒴂��܂����Bname="<<_pBaseActor->getName()<<" prm_str="<<prm_str);
    }
#endif
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare1(const int prm_chr) {
    onUpdate(); //�R�[���o�b�N
    _draw_string = _buf;
    bool is_different = false;
    if (_draw_string[0] != prm_chr) {
        is_different = true;
        _draw_string[0] = prm_chr; //�ۑ�
        _draw_string[1] = '\0'; //�ۑ�
    }
    if (prm_chr == _chr_newline) {
        _len = 0;
        _px_total_width = 0;
        _draw_chr_num = 0;
    } else if (prm_chr == '\0') {
        _len = 1;
        _px_total_width = 0;
        _draw_chr_num = 0;
    } else {
        _len = 1;
        _px_total_width = (_is_fixed_width ? _chr_base_width_px : _px_chr_width[prm_chr]); //�s�̕�(px)�����Z
        _draw_chr_num = 1;
    }
    _nn = 1;
    _px_total_height = _chr_base_height_px*_nn;
    if (is_different) {
        prepare2();
    }
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare1_append(const int prm_append_chr) {
    int new_buffer_size = _len+1+1;
    if (new_buffer_size > _max_buf) {//�o�b�t�@�g��
        _max_buf = 8*((new_buffer_size+8)/8); //���߂W�̔{���ɐ؂�グ
        int* tmp_buf = NEW int[_max_buf];
        memcpy(tmp_buf, _buf, sizeof(int)*(_len+1));
        InstancePart* tmp_paInstancePart = NEW InstancePart[_max_buf];
        memcpy(tmp_paInstancePart, _paInstancePart, sizeof(InstancePart)*(_len+1));
        GGAF_DELETEARR(_buf);
        GGAF_DELETEARR(_paInstancePart);
        _buf = tmp_buf;
        _paInstancePart = tmp_paInstancePart;
    }
    onUpdate(); //�R�[���o�b�N
    _draw_string = _buf;
    const pixcoord chr_base_width_px = _chr_base_width_px;
    int c = prm_append_chr;
    if (0 > c || c > (N-1)) {
        _TRACE_("�y�x���zICharacterChip::prepare1_append() �͈͊O�̈����Ȃ������킪����܂��� prm_append_chr="<<prm_append_chr<<"�B 0�`"<<(N-1)<<"�͈̔͂ɂ��ĉ������Bthis="<<this);
        c = N-1;
    }
    _draw_string[_len-1 + 1] = c; //�ۑ�
    _draw_string[_len-1 + 1+1] = '\0';//�ۑ�
    _len += 1;
    if (_nn > 0) {
        _nn--;//�s�͖��m���ԂɂȂ�̂ŁA -1 ����B
    }
    if (c == _chr_newline) {
        _nn++; //�s���J�E���g
    } else {
        _px_row_width[_nn] += (_is_fixed_width ? chr_base_width_px : _px_chr_width[c]); //�s�̕�(px)�����Z
        if (_nn == 0 || _px_total_width < _px_row_width[_nn]) {
            _px_total_width = _px_row_width[_nn];
        }
        _nn++; //�P�����ǉ��͍s���P�Ƃ��ăJ�E���g�B
    }
    if (c != _chr_blank) { //�u�����N
        _draw_chr_num++; //�`�敶�����J�E���g
    }
    _px_total_height = _chr_base_height_px*_nn;
    prepare2();
#ifdef MY_DEBUG
    if (_nn > L) {
        throwCriticalException("ICharacterChip::prepare1_append() ������̍s����"<<L<<"�𒴂��܂����Bname="<<_pBaseActor->getName()<<" prm_append_chr="<<prm_append_chr);
    }
#endif
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare1_append(const char* prm_append_str) {
    int append_len = (int)strlen(prm_append_str);
    int new_buffer_size = _len+append_len+1;
    if (new_buffer_size > _max_buf) {//�o�b�t�@�g��
        _max_buf = 8*((new_buffer_size+8)/8); //���߂W�̔{���ɐ؂�グ
        int* tmp_buf = NEW int[_max_buf];
        memcpy(tmp_buf, _buf, sizeof(int)*(_len+1));
        InstancePart* tmp_paInstancePart = NEW InstancePart[_max_buf];
        memcpy(tmp_paInstancePart, _paInstancePart, sizeof(InstancePart)*(_len+1));
        GGAF_DELETEARR(_buf);
        GGAF_DELETEARR(_paInstancePart);
        _buf = tmp_buf;
        _paInstancePart = tmp_paInstancePart;

    }
    onUpdate(); //�R�[���o�b�N
    _draw_string = _buf;
    //�ێ�(_draw_string)����A���Ȃ�����s��(_nn)�����߂�A
    //���łɊe�s�P�ʂ̕���(_px_row_width)�����߂Ă���
    const char* p_prm_append_str = prm_append_str;
    int* p_draw_string = &_draw_string[_len-1 + 1]; //+1��append����ʒu����Ƃ����Ӗ�
    _len += append_len;
    if (_nn > 0) {
        _nn--;//�s�͖��m���ԂɂȂ�̂ŁA -1 ����B
    }
    pixcoord* p_width_line_px = &_px_row_width[_nn];
    pixcoord max_width_line_px = _px_total_width;
    int c;
    const int chr_blank = _chr_blank;
    const bool is_fixed_width = _is_fixed_width;
    const pixcoord chr_base_width_px = _chr_base_width_px;
    while (true) {
        c = (int)(*p_prm_append_str);
        if (0 > c || c > (N-1)) {
            _TRACE_("�y�x���zICharacterChip::prepare1_append() �͈͊O�̈����Ȃ������킪����܂��� p_append_str=["<<p_prm_append_str<<"] �̒��̒l:"<<c<<"�B 0�`"<<(N-1)<<"�͈̔͂ɂ��ĉ������Bthis="<<this);
            c = N-1;
        }
        *p_draw_string = c; //�ۑ�
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
        ++p_prm_append_str;  ++p_draw_string;
    }
    _px_total_width = max_width_line_px;
    _px_total_height = _chr_base_height_px*_nn;
    prepare2();
#ifdef MY_DEBUG
    if (_nn > L) {
        throwCriticalException("ICharacterChip::prepare1_append() ������̍s����"<<L<<"�𒴂��܂����Bname="<<_pBaseActor->getName()<<" prm_str="<<prm_append_str);
    }
#endif
}


template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare1_delete(int prm_delete_byte_num) {
    onUpdate(); //�R�[���o�b�N
    _len -= prm_delete_byte_num;
    _draw_string[_len] = '\0';
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
        c = *p_draw_string;
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
        ++p_draw_string;
    }
    _px_total_width = max_width_line_px;
    _px_total_height = _chr_base_height_px*_nn;
    prepare2();
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare2() {
    //ALIGN_RIGHT ��VALIGN_BOTTOM �ׂ̈�
    //�ǂ����Ă��Q��S���������[�v�łȂ߂�K�v������B
    //prepare1() �͂P��ڂ̃��[�v�A prepare2() �͂Q��ڂ̃��[�v�ɑ���
    if (_len == 0) {
        return;
    }
    const Align align  = _pBaseActor->_align;
    const Valign valign = _pBaseActor->_valign;
    const pixcoord chr_base_height_px = _chr_base_height_px;
    const pixcoord chr_base_width_px = _chr_base_width_px;
    const int chr_newline = _chr_newline;
    const int chr_blank = _chr_blank;
    const int chr_ptn_zero = _chr_ptn_zero;
    GgafDx::UvFlipper* pUvFlipper = _pBaseActor->getUvFlipper();
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
                pInstancePart->px_local_x = (float)px_x;
                pInstancePart->px_local_y = (float)px_y;
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
                    pInstancePart->px_local_x = (float)px_x;
                    pInstancePart->px_local_y = (float)px_y;
                    int c = draw_chr - chr_ptn_zero;
                    if (c > pUvFlipper->_pattno_uvflip_max) {
                        _TRACE_("�y�x���z prepare2() draw_chr="<< draw_chr<<"["<<((char)draw_chr)<<"]�́A�p�^�[���ԍ�=" <<c<<"�ƂȂ�A"
                                "�͈͊O(�ő�p�^�[���ԍ�=" << pUvFlipper->_pattno_uvflip_max << ")�Ȃ̂ŁA�\���ł��܂���B" <<
                                "�������Ȃ��̂�[?] �ɒu�������܂����B�v�m�F");
                        c = (int)'?' - chr_ptn_zero;
                    }
                    pUvFlipper->getUV(c, u, v);
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
                    pInstancePart->px_local_x = (float)px_x;
                    pInstancePart->px_local_y = (float)px_y;
                    pUvFlipper->getUV(draw_chr-chr_ptn_zero, u, v);
                    pInstancePart->offset_u = (float)u;
                    pInstancePart->offset_v = (float)v;
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
void ICharacterChip<T, N, L>::update(coord X, coord Y, const int prm_chr) {
    update(prm_chr);
    _pBaseActor->setPosition(X, Y);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    _pBaseActor->setPosition(X, Y, Z);
}
template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, coord Z, const int prm_chr) {
    update(prm_chr);
    _pBaseActor->setPosition(X, Y, Z);
}


template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(const char* prm_str) {
    prepare1(prm_str);
}
template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(const int prm_chr) {
    prepare1(prm_chr);
}
template<class T, int N, int L>
void ICharacterChip<T, N, L>::appendUpdate(const int prm_c) {
    prepare1_append(prm_c);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::appendUpdate(const char* prm_str) {
    prepare1_append(prm_str);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::deleteUpdate(int prm_delete_byte_num) {
#ifdef MY_DEBUG
    if (prm_delete_byte_num < 0 || prm_delete_byte_num > _len) {
        throwCriticalException("ICharacterChip::deleteUpdate() �폜�������͈̔͊O�ł��B_len="<<_len<<" prm_delete_byte_num="<<prm_delete_byte_num<<
                " name="<<_pBaseActor->getName());
    }
#endif
    prepare1_delete(prm_delete_byte_num);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, const char* prm_str, Align prm_align, Valign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    _pBaseActor->setPosition(X, Y);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(coord X, coord Y, coord Z, const char* prm_str, Align prm_align, Valign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    _pBaseActor->setPosition(X, Y, Z);
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::update(const char* prm_str, Align prm_align, Valign prm_valign) {
    update(prm_str);
    _pBaseActor->setAlign(prm_align, prm_valign);
}

template<class T, int N, int L>
ICharacterChip<T, N, L>::~ICharacterChip() {
     GGAF_DELETEARR(_buf);
     GGAF_DELETEARR(_paInstancePart);
}

}

#endif /*GGAF_LIB_IFIXEDFONT_H_*/
