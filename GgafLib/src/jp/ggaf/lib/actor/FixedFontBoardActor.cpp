#include "jp/ggaf/lib/actor/FixedFontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FixedFontBoardActor::VERTEX_instancedata FixedFontBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE_NUM];

FixedFontBoardActor::FixedFontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
          GgafDxMassBoardActor(prm_name, prm_model, "FontBoardEffect", "FontBoardTechnique"),

_chr_width_px((int)(_pMassBoardModel->_model_width_px)),
_chr_height_px((int)(_pMassBoardModel->_model_height_px))
{
    _class_name = "FixedFontBoardActor";
    _max_len = 8;  //最初はバッファは8文字
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper の パターン0番の文字。
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

    _pMassBoardModel->registerCallback_VertexInstaceDataInfo(FixedFontBoardActor::createVertexInstaceData);
}

void FixedFontBoardActor::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //直近８の倍数に切り上げ
    GGAF_DELETEARR(_buf);
    GGAF_DELETEARR(_paInstacePart);
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstacePart = NEW InstacePart[_max_len];
}

void FixedFontBoardActor::update(coord X, coord Y, const char* prm_str) {
    update(prm_str);
    position(X, Y);
}

void FixedFontBoardActor::update(coord X, coord Y, coord Z, const char* prm_str) {
    update(prm_str);
    position(X, Y, Z);
}
void FixedFontBoardActor::update(const char* prm_str) {
    prepare1(prm_str);
}


void FixedFontBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        prepare2();
    }
}

void FixedFontBoardActor::setAlign(GgafDxAlign prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        prepare2();
    }
}

void FixedFontBoardActor::setValign(GgafDxValign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        prepare2();
    }
}

void FixedFontBoardActor::prepare1(const char* prm_str) {
    _len = strlen(prm_str);
    if (_len+1 > _max_len) {
        chengeBufferLen(_len+1); //バッファ拡張
    }
    onUpdate(); //コールバック
    _draw_string = _buf;
    //保持(_draw_string)する、しながら改行数(_nn)を求める、
    //ついでに各行単位の幅も(_px_row_width)も求めておく
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
            throwGgafCriticalException("範囲外の扱えない文字種がありました prm_str=["<<prm_str<<"] の中の値:"<<c<<"。 0～255の範囲にして下さい。this="<<this);
        }
#endif
        if (c != (*p_draw_string)) {
            is_different = true;
            *p_draw_string = c; //保存
        }
        if (c == '\n') {
            _nn++; //行数カウント
            p_width_line_px++;  *p_width_line_px = 0; //行の幅保持配列を次へ ＆ 0にリセット
        } else if (c == '\0') {
            _nn++; //文字列最後を行数１としてカウント。文字列は改行で終わる必要がない。
            break;
        } else {
            *p_width_line_px += _chr_width_px; //行の幅(px)を加算
        }
        if (c != chr_blank) { //ブランク
            _draw_chr_num++; //描画文字数カウント
        }
        p_prm_str++;  p_draw_string++;
    }
    if (is_different) {
        prepare2();
    }
#ifdef MY_DEBUG
    if (_nn > 1024) {
        throwGgafCriticalException("文字列の行数が1024個を超えました。name="<<getName()<<" prm_str="<<prm_str);
    }
#endif
}

void FixedFontBoardActor::prepare2() {
    //ALIGN_RIGHT やVALIGN_BOTTOM の為に
    //どうしても２回全文字をループでなめる必要がある。
    //prepare1() は１回目のループ、 prepare2() は２回目のループに相当
    if (_len == 0) {
        return;
    }
    //初期Y位置を決める
    pixcoord px_y, px_x;
    int nnn = 0; // num of \n now
    if (_align == ALIGN_CENTER) {
        px_x = -(_px_row_width[nnn]/2);
    } else if (_align == ALIGN_RIGHT) {
        px_x = -(_px_row_width[nnn]);
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
    int chr_blank = _chr_blank;
    int chr_ptn_zero = _chr_ptn_zero;
    float u, v;
    int* p_chr  = _draw_string;
    InstacePart* pInstacePart = _paInstacePart;
    while(true) { //各文字単位のループ
        int draw_chr = *p_chr;
        if (draw_chr == (int)('\0')) {
            break; //おしまい
        } else if (draw_chr == (int)('\n')) {
            nnn++;
            if (_align == ALIGN_CENTER) {
                px_x = -(_px_row_width[nnn]/2);
            } else if (_align == ALIGN_RIGHT) {
                px_x = -(_px_row_width[nnn]);
            } else {  //ALIGN_LEFT
                px_x = 0;
            }
            px_y += _chr_height_px;
            p_chr++;
            continue; //表示文字はない
        }
        //情報更新
        if (draw_chr != chr_blank) {
            pInstacePart->px_local_x = px_x;
            pInstacePart->px_local_y = px_y;
            getUvFlipper()->getUV(draw_chr-chr_ptn_zero, u, v);
            pInstacePart->offset_u = u;
            pInstacePart->offset_v = v;
            pInstacePart++;
        }
        px_x += _chr_width_px;
        p_chr++;
    }
}

void FixedFontBoardActor::update(coord X, coord Y, const char* prm_str, GgafDxAlign prm_align,
                            GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    position(X, Y);
}

void FixedFontBoardActor::update(coord X, coord Y, coord Z, const char* prm_str, GgafDxAlign prm_align,
                            GgafDxValign prm_valign) {
    update(prm_str, prm_align, prm_valign);
    position(X, Y, Z);
}

void FixedFontBoardActor::update(const char* prm_str, GgafDxAlign prm_align, GgafDxValign prm_valign) {
    update(prm_str);
    setAlign(prm_align, prm_valign);
}

void FixedFontBoardActor::createVertexInstaceData(void* prm, GgafDxMassModel::VertexInstaceDataInfo* out_info) {
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
    //float offset_u, offset_v, alpha;   // : TEXCOORD2
    out_info->paElement[1].Stream = 1;
    out_info->paElement[1].Offset = st1_offset_next;
    out_info->paElement[1].Type   = D3DDECLTYPE_FLOAT3;
    out_info->paElement[1].Method = D3DDECLMETHOD_DEFAULT;
    out_info->paElement[1].Usage  = D3DDECLUSAGE_TEXCOORD;
    out_info->paElement[1].UsageIndex = 2;
    st1_offset_next += sizeof(float)*3;
    // <---- Stream = 1

    out_info->element_num = element_num;
    out_info->size_vertex_unit_instacedata = sizeof(FixedFontBoardActor::VERTEX_instancedata);
    out_info->pInstancedata = FixedFontBoardActor::_aInstancedata;
}

void FixedFontBoardActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassBoardActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxMassBoardEffect* pMassBoardEffect = _pMassBoardEffect;
    VERTEX_instancedata* paInstancedata = FixedFontBoardActor::_aInstancedata;
    GgafDxFigureActor* pDrawActor = this;
    FixedFontBoardActor* pFixedFontBoardActor = nullptr;
    int model_set_num = _pMassBoardModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFixedFontBoardActor = (FixedFontBoardActor*)pDrawActor;
            int n = pFixedFontBoardActor->_draw_chr_num;
            pixcoord x = C_PX(pFixedFontBoardActor->_x);
            pixcoord y = C_PX(pFixedFontBoardActor->_y);
            pixcoord z = C_PX(pFixedFontBoardActor->_z);
            InstacePart* pInstacePart = pFixedFontBoardActor->_paInstacePart;
            float alpha = pFixedFontBoardActor->_alpha;
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット

            for (int i = 0; i < n; i++) {
                paInstancedata->px_x = (float)(x + pInstacePart->px_local_x);
                paInstancedata->px_y = (float)(y + pInstacePart->px_local_y);
                paInstancedata->depth_z = (float)(z);
                paInstancedata->offset_u = pInstacePart->offset_u;
                paInstancedata->offset_v = pInstacePart->offset_v;
                paInstancedata->alpha    = alpha;
                pInstacePart++;
                paInstancedata++;

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                   _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
                   paInstancedata = FixedFontBoardActor::_aInstancedata;
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
}

FixedFontBoardActor::~FixedFontBoardActor() {
     GGAF_DELETEARR(_buf);
     GGAF_DELETEARR(_paInstacePart);
}


