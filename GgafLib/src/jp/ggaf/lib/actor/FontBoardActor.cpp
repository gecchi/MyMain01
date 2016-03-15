#include "jp/ggaf/lib/actor/FontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontBoardActor::VERTEX_instancedata FontBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE];

FontBoardActor::FontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
          GgafDxMassBoardActor(prm_name, prm_model, "FontBoardEffect", "FontBoardTechnique")
{
    _class_name = "FontBoardActor";
    _max_len = 8;  //�ŏ��̓o�b�t�@��8����
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper �� �p�^�[��0�Ԃ̕����B
    _len = 0;
    _draw_chr_num = 0;
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstacePart = NEW InstacePart[_max_len];
    _draw_string = _buf;
    //�f�t�H���g�̂P�����̕�(px)�ݒ�
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pMassBoardModel->_model_width_px);
        _aWidth_line_px[i] = 0;
    }
    _chr_width_px = (int)(_pMassBoardModel->_model_width_px); //�P�����̕�(px)
    _chr_height_px = (int)(_pMassBoardModel->_model_height_px); //�P�����̍���(px)
    _nn = 0;

    _pMassBoardModel->registerCallback_VertexInstaceDataInfo(FontBoardActor::createVertexInstaceData);
}

void FontBoardActor::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //���߂W�̔{���ɐ؂�グ
    GGAF_DELETEARR(_buf);
    GGAF_DELETEARR(_paInstacePart);
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstacePart = NEW InstacePart[_max_len];

}

void FontBoardActor::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    position(X, Y);
}

void FontBoardActor::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    position(X, Y, Z);
}

void FontBoardActor::update(const char* prm_str) {
    _len = strlen(prm_str);
    if (_len+1 > _max_len) {
        chengeBufferLen(_len+1); //�o�b�t�@�g��
    }
    onUpdate(); //�R�[���o�b�N
    _draw_string = _buf;
    _aWidth_line_px[0] = 0;
    int nn = 0;
    int len = _len;
    _draw_chr_num = 0;
    //�ێ�(_draw_string)����A���Ȃ�����s��(_nn)�����߂�A
    //���łɊe�s�P�ʂ̕���(_aWidth_line_px)�����߂Ă���
    bool is_different = false;
    int c;
    for (int i = 0; i < len+1; i++) { //+1�͍Ō��'\0'�𔻒肷�邽��
        c = (int)(prm_str[i]);
        if (_draw_string[i] != c) {
            is_different = true;
        }
        _draw_string[i] = c; //�ێ�
        if (c == '\n') {
            nn++;
            _aWidth_line_px[nn] = 0;
            continue;
        } else if (c == '\0') {
            nn++; //�Ō���s���P�Ƃ��ăJ�E���g
            _aWidth_line_px[nn] = 0;
            break;
        } else {
            _draw_chr_num++;
        }
#ifdef MY_DEBUG
        if (0 > _draw_string[i] || _draw_string[i] > 256) {
            throwGgafCriticalException("�͈͊O�̈����Ȃ������킪����܂��� _draw_string["<<i<<"]="<<_draw_string[i]<<"�B 0�`255�͈̔͂ɂ��ĉ������Bname="<<getName()<<" prm_str="<<prm_str);
        }
#endif
        _aWidth_line_px[nn] += _aWidthPx[c];
    }
#ifdef MY_DEBUG
    if (nn > 1024) {
        throwGgafCriticalException("������̍s����1024�𒴂��܂����Bname="<<getName()<<" prm_str="<<prm_str);
    }
#endif
    _nn = nn;
    if (is_different) {
        updateOffset();
    }
}

void FontBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        updateOffset();
    }
}

void FontBoardActor::setAlign(GgafDxAlign prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        updateOffset();
    }
}

void FontBoardActor::setValign(GgafDxValign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        updateOffset();
    }
}

void FontBoardActor::updateOffset() {
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
        } else {
            //VALIGN_TOP
        }

        int nnn = 0; // num of \n now
        pixcoord px_x =  -(_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
        pixcoord x_tmp = px_x;
        float u, v;
        int pattno = 0;
        int* p_chr  = _draw_string;
        InstacePart* pInstacePart = _paInstacePart;
        while(true) { //�e�����P�ʂ̃��[�v
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\0')) {
                break; //�����܂�
            } else if (draw_chr == (int)('\n')) {
                nnn++;
                px_x = -(_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
                x_tmp = px_x;
                px_y += _chr_height_px;
                p_chr++;
                continue; //�\�������͂Ȃ�
            } else {
                pattno = draw_chr - _chr_ptn_zero; //�ʏ핶����
            }
            //�v���|�[�V���i���ȕ��v�Z
            int w = ((_chr_width_px - _aWidthPx[draw_chr]) / 2);
            px_x = x_tmp - w;
            x_tmp = px_x + _chr_width_px - w;

            //���X�V
            pInstacePart->px_x = px_x;
            pInstacePart->px_y = px_y;
            getUvFlipper()->getUV(pattno, u,v);
            pInstacePart->offset_u = u;
            pInstacePart->offset_v = v;
            p_chr++;
            pInstacePart++;
        }
    } else if (_align == ALIGN_RIGHT) {
        if (_valign == VALIGN_BOTTOM) {
            px_y = -_chr_height_px;
        } else if (_valign == VALIGN_MIDDLE) {
            px_y = ((_chr_height_px*_nn/2) - _chr_height_px);
        } else {
            //VALIGN_TOP
            px_y = ((_chr_height_px*_nn) - _chr_height_px);
        }

        //�E����\������
        pixcoord px_x = 0;
        pixcoord x_tmp = px_x;
        float u, v;
        int pattno = 0;
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
            } else {
                pattno = draw_chr - _chr_ptn_zero; //�ʏ핶����
            }
            //�v���|�[�V���i���ȕ��v�Z
            w = ((_chr_width_px - _aWidthPx[draw_chr]) / 2);
            px_x = x_tmp - (w + _aWidthPx[draw_chr]);
            x_tmp = px_x + w;

            //���X�V
            pInstacePart->px_x = px_x;
            pInstacePart->px_y = px_y;
            getUvFlipper()->getUV(pattno, u,v);
            pInstacePart->offset_u = u;
            pInstacePart->offset_v = v;
            if (p_chr == _draw_string) { //��ԍ��ɓ��B
                break; //�����܂�
            }
            p_chr--;
            pInstacePart--;
        }
    }

}

void FontBoardActor::update(coord X, coord Y, const char* prm_str, GgafDxAlign prm_align,
                            GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    position(X, Y);
}

void FontBoardActor::update(coord X, coord Y, coord Z, const char* prm_str, GgafDxAlign prm_align,
                            GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    position(X, Y, Z);
}

void FontBoardActor::update(const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    setAlign(prm_align, prm_valign);
}

void FontBoardActor::createVertexInstaceData(GgafDxMassModel::VertexInstaceDataInfo* out_info) {
    int element_num = 2;
    out_info->paElement = NEW D3DVERTEXELEMENT9[element_num];
    // Stream = 1 ---->
    WORD st1_offset_next = 0;
    //float px_x, px_y, depth_z;   // : TEXCOORD1
    out_info->paElement[0].Stream = 1;
    out_info->paElement[0].Offset = st1_offset_next;
    out_info->paElement[0].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[0].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[0].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[0].UsageIndex = 1;
    st1_offset_next += sizeof(float)*3;
    //float offset_u, offset_v, alpha;                    // : TEXCOORD2
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*3;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instacedata = sizeof(FontBoardActor::VERTEX_instancedata);
    out_info->pInstancedata = FontBoardActor::_aInstancedata;
}

void FontBoardActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassBoardActor�̓������f���œ����e�N�j�b�N��
                       //�A�����Ă���J�E���g���B����`��[�x�͈�x�ɕ`�悷��B
    GgafDxMassBoardEffect* pMassBoardEffect = _pMassBoardEffect;
    VERTEX_instancedata* paInstancedata = FontBoardActor::_aInstancedata;
    GgafDxFigureActor* pDrawActor = this;
    FontBoardActor* pFontBoardActor = nullptr;
    int model_set_num = _pMassBoardModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFontBoardActor = (FontBoardActor*)pDrawActor;
            int n = pFontBoardActor->_draw_chr_num;
            pixcoord x = C_PX(pFontBoardActor->_x);
            pixcoord y = C_PX(pFontBoardActor->_y);
            pixcoord z = C_PX(pFontBoardActor->_z);
            InstacePart* pInstacePart = pFontBoardActor->_paInstacePart;
            float alpha = pFontBoardActor->_alpha;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //�`��Z�b�g�̍Ō�A�N�^�[���Z�b�g

            for (int i = 0; i < n; i++) {
                paInstancedata->px_x = (float)(x + pInstacePart->px_x);
                paInstancedata->px_y = (float)(y + pInstacePart->px_y);
                paInstancedata->depth_z = (float)(z);
                paInstancedata->offset_u = pInstacePart->offset_u;
                paInstancedata->offset_v = pInstacePart->offset_v;
                paInstancedata->alpha    = alpha;
                pInstacePart++;                paInstancedata++;

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                   _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
                   paInstancedata = FontBoardActor::_aInstancedata;
                   draw_set_num = 0;
                }
            }
            pDrawActor = pDrawActor->_pNextRenderActor;
        } else {
            break;
        }
    }
    if (draw_set_num > 0) {
        _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
    }
//    _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
}

FontBoardActor::~FontBoardActor() {
     GGAF_DELETEARR(_buf);
     GGAF_DELETEARR(_paInstacePart);
}

