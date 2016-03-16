#include "jp/ggaf/lib/actor/FontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontBoardActor::VERTEX_instancedata FontBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE_NUM];

FontBoardActor::FontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
          GgafDxMassBoardActor(prm_name, prm_model, "FontBoardEffect", "FontBoardTechnique")
{
    _class_name = "FontBoardActor";
    _max_len = 8;  //最初はバッファは8文字
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper の パターン0番の文字。
    _chr_blank = (int)(' ');
    _len = 0;
    _draw_chr_num = 0;
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paInstacePart = NEW InstacePart[_max_len];
    _draw_string = _buf;
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < 256; i++) {
        _aWidthPx[i] = (int)(_pMassBoardModel->_model_width_px);
        _aWidth_line_px[i] = 0;
    }
    _chr_width_px = (int)(_pMassBoardModel->_model_width_px); //１文字の幅(px)
    _chr_height_px = (int)(_pMassBoardModel->_model_height_px); //１文字の高さ(px)
    _nn = 0;

    _pMassBoardModel->registerCallback_VertexInstaceDataInfo(FontBoardActor::createVertexInstaceData);
}

void FontBoardActor::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //直近８の倍数に切り上げ
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
    prepare1(prm_str);
}
void FontBoardActor::prepare1(const char* prm_str) {
    _len = strlen(prm_str);
    if (_len+1 > _max_len) {
        chengeBufferLen(_len+1); //バッファ拡張
    }
    onUpdate(); //コールバック
    _draw_string = _buf;
    //保持(_draw_string)する、しながら改行数(_nn)を求める、
    //ついでに各行単位の幅も(_aWidth_line_px)も求めておく
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
            *p_width_line_px += _aWidthPx[c]; //行の幅(px)を加算
        }
        if (c != _chr_blank) { //ブランク
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

void FontBoardActor::setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) {
    if (_align != prm_align || _valign != prm_valign) {
        _align = prm_align;
        _valign = prm_valign;
        prepare2();
    }
}

void FontBoardActor::setAlign(GgafDxAlign prm_align) {
    if (_align != prm_align) {
        _align = prm_align;
        prepare2();
    }
}

void FontBoardActor::setValign(GgafDxValign prm_valign) {
    if (_valign != prm_valign) {
        _valign = prm_valign;
        prepare2();
    }
}

void FontBoardActor::prepare2() {
    //ALIGN_RIGHT やVALIGN_BOTTOM の為に
    //どうしても２回全文字をループでなめる必要がある。
    //update() は１回目のループ、 prepare2() は２回目のループに相当
    if (_len == 0) {
        return;
    }
    //初期Y位置を決める
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
        int* p_chr  = _draw_string;
        InstacePart* pInstacePart = _paInstacePart;
        while(true) { //各文字単位のループ
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\0')) {
                break; //おしまい
            } else if (draw_chr == (int)('\n')) {
                nnn++;
                px_x = -(_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
                x_tmp = px_x;
                px_y += _chr_height_px;
                p_chr++;
                continue; //表示文字はない
            }
            //プロポーショナルな幅計算
            int w = ((_chr_width_px - _aWidthPx[draw_chr]) / 2);
            px_x = x_tmp - w;
            x_tmp = px_x + _chr_width_px - w;

            //情報更新
            if (draw_chr != _chr_blank) {
                pInstacePart->px_x = px_x;
                pInstacePart->px_y = px_y;
                getUvFlipper()->getUV(draw_chr-_chr_ptn_zero, u, v);
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
        } else {
            //VALIGN_TOP
            px_y = ((_chr_height_px*_nn) - _chr_height_px);
        }

        //右から表示する
        pixcoord px_x = 0;
        pixcoord x_tmp = px_x;
        float u, v;
        int w;
        int* p_chr = &(_draw_string[_len-1]); //末尾から回す。_len は strlen の値
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
            //プロポーショナルな幅計算
            w = ((_chr_width_px - _aWidthPx[draw_chr]) / 2);
            px_x = x_tmp - (w + _aWidthPx[draw_chr]);
            x_tmp = px_x + w;
            //情報更新
            if (draw_chr != _chr_blank) {
                pInstacePart->px_x = px_x;
                pInstacePart->px_y = px_y;
                getUvFlipper()->getUV(draw_chr-_chr_ptn_zero, u, v);
                pInstacePart->offset_u = u;
                pInstacePart->offset_v = v;
                pInstacePart--;
            }
            if (p_chr == _draw_string) { //一番左に到達
                 break; //おしまい
            }
            p_chr--;
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
    out_info->size_vertex_unit_instacedata = sizeof(FontBoardActor::VERTEX_instancedata);
    out_info->pInstancedata = FontBoardActor::_aInstancedata;
}

void FontBoardActor::processDraw() {
    int draw_set_num = 0; //GgafDxMassBoardActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
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
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット

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

