#include "jp/ggaf/lib/actor/FixFontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixFontBoardActor::FixFontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        FontBoardActor(prm_name, prm_model, prm_pStat) {
}

void FixFontBoardActor::prepare1(const char* prm_str) {
    _len = strlen(prm_str);
    if (_len+1 > _max_len) {
        chengeBufferLen(_len+1); //�o�b�t�@�g��
    }
    onUpdate(); //�R�[���o�b�N
    _draw_string = _buf;
    //�ێ�(_draw_string)����A���Ȃ�����s��(_nn)�����߂�A
    //���łɊe�s�P�ʂ̕���(_aWidth_line_px)�����߂Ă���
    bool is_different = false;
    const char* p_prm_str = prm_str;
    int* p_draw_string = _draw_string;
    pixcoord* p_width_line_px = _aWidth_line_px;  *p_width_line_px = 0;
    _nn = 0;
    _draw_chr_num = 0;
    int c;
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
        if (c != _chr_blank) { //�u�����N
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


void FixFontBoardActor::prepare2() {
    //ALIGN_RIGHT ��VALIGN_BOTTOM �ׂ̈�
    //�ǂ����Ă��Q��S���������[�v�łȂ߂�K�v������B
    //prepare1() �͂P��ڂ̃��[�v�A prepare2() �͂Q��ڂ̃��[�v�ɑ���
    if (_len == 0) {
        return;
    }
    //����Y�ʒu�����߂�
    pixcoord px_y, px_x;
    int nnn = 0; // num of \n now
    if (_align == ALIGN_CENTER) {
        px_x = -(_aWidth_line_px[nnn]/2);
    } else if (_align == ALIGN_RIGHT) {
        px_x = -(_aWidth_line_px[nnn]);
    } else {  //ALIGN_LEFT
        px_x = 0;
    }
    if (_valign == VALIGN_BOTTOM) {
        px_y = -(_chr_height_px*_nn);
    } else if (_valign == VALIGN_MIDDLE) {
        px_y = -(_chr_height_px*_nn/2);
    } else { //VALIGN_TOP
        px_y = 0;
    }
    float u, v;
    int* p_chr  = _draw_string;
    InstacePart* pInstacePart = _paInstacePart;
    while(true) { //�e�����P�ʂ̃��[�v
        int draw_chr = *p_chr;
        if (draw_chr == (int)('\0')) {
            break; //�����܂�
        } else if (draw_chr == (int)('\n')) {
            nnn++;
            if (_align == ALIGN_CENTER) {
                px_x = -(_aWidth_line_px[nnn]/2);
            } else if (_align == ALIGN_RIGHT) {
                px_x = -(_aWidth_line_px[nnn]);
            } else {  //ALIGN_LEFT
                px_x = 0;
            }
            px_y += _chr_height_px;
            p_chr++;
            continue; //�\�������͂Ȃ�
        }
        //���X�V
        if (draw_chr != _chr_blank) {
            pInstacePart->px_x = px_x;
            pInstacePart->px_y = px_y;
            getUvFlipper()->getUV(draw_chr-_chr_ptn_zero, u, v);
            pInstacePart->offset_u = u;
            pInstacePart->offset_v = v;
            pInstacePart++;
        }
        px_x += _chr_width_px;
        p_chr++;
    }
}

FixFontBoardActor::~FixFontBoardActor() {
}

