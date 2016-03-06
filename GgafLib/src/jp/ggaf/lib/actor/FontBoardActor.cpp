#include "jp/ggaf/lib/actor/FontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"

#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"

#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontBoardActor::VERTEX_instancedata FontBoardActor::_aInstancedata[GGAFDXMASS_MAX_INSTACE];

FontBoardActor::FontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
//        GgafDxMassBoardActor(prm_name, prm_model, "FontBoardEffect", "FontBoardTechnique")
          GgafDxMassBoardActor(prm_name, prm_model, "DefaultMassBoardEffect", "DefaultMassBoardTechnique")
{
    _class_name = "FontBoardActor";
    _max_len = 8;  //最初はバッファは8文字
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper の パターン0番の文字。
    _len = 0;
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paOffset_x = NEW float[_max_len];
    _paOffset_y = NEW float[_max_len];
    _paOffset_u = NEW float[_max_len];
    _paOffset_v = NEW float[_max_len];
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
    GGAF_DELETEARR(_paOffset_x);
    GGAF_DELETEARR(_paOffset_y);
    GGAF_DELETEARR(_paOffset_u);
    GGAF_DELETEARR(_paOffset_v);
    _buf = NEW int[_max_len];
    _buf[0] = (int)('\0');
    _paOffset_x = NEW float[_max_len];
    _paOffset_y = NEW float[_max_len];
    _paOffset_u = NEW float[_max_len];
    _paOffset_v = NEW float[_max_len];
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
        chengeBufferLen(_len+1); //バッファ拡張
    }
    onUpdate(); //コールバック
    _draw_string = _buf;
    _aWidth_line_px[0] = 0;
    int nn = 0;
    int len = _len;

    //保持(_draw_string)する、しながら改行数(_nn)を求める、
    //ついでに各行単位の幅も(_aWidth_line_px)も求めておく
    bool is_different = false;
    int c;
    for (int i = 0; i < len+1; i++) {
        c = (int)(prm_str[i]);
        if (_draw_string[i] != c) {
            is_different = true;
        }
        _draw_string[i] = c; //保持
        if (c == '\n') {
            nn++;
            _aWidth_line_px[nn] = 0;
            continue;
        }
        if (c == '\0') {
            nn++;
            _aWidth_line_px[nn] = 0;
            break;
        }
#ifdef MY_DEBUG
        if (nn > 1024) {
            throwGgafCriticalException("FontBoardActor::update 文字列の改行数が1024個を超えました。name="<<getName()<<" prm_str="<<prm_str);
        }
        if (0 > _draw_string[i] || _draw_string[i] > 256) {
            throwGgafCriticalException("FontBoardActor::update 範囲外の扱えない文字種がありました _draw_string["<<i<<"]="<<_draw_string[i]<<"。 0〜255の範囲にして下さい。name="<<getName()<<" prm_str="<<prm_str);
        }
#endif
        _aWidth_line_px[nn] += _aWidthPx[c];
    }
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
    //初期Y位置を決める
    pixcoord offset_y = 0;
    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        if (_valign == VALIGN_BOTTOM) {
            offset_y = -(_chr_height_px*_nn);
        } else if (_valign == VALIGN_MIDDLE) {
            offset_y = -(_chr_height_px*_nn/2);
        } else {
            //VALIGN_TOP
        }
    } else {
        //ALIGN_RIGHT
        if (_valign == VALIGN_BOTTOM) {
            offset_y = -_chr_height_px;
        } else if (_valign == VALIGN_MIDDLE) {
            offset_y = ((_chr_height_px*_nn/2) - _chr_height_px);
        } else {
            //VALIGN_TOP
            offset_y = ((_chr_height_px*_nn) - _chr_height_px);
        }
    }

    if (_align == ALIGN_LEFT || _align == ALIGN_CENTER) {
        int nnn = 0; // num of \n now
        pixcoord offset_x =  -(_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
        pixcoord x_tmp = offset_x;
        float u, v;
        int pos = 0;
        int pattno = 0;
        while(true) { //各文字単位のループ
            if (_draw_string[pos] == (int)('\0')) {
                break; //おしまい
            } else if (_draw_string[pos] == (int)('\n')) {
                nnn++;
                offset_x = -(_align == ALIGN_CENTER ? _aWidth_line_px[nnn]/2 : 0);
                x_tmp = offset_x;
                offset_y += _chr_height_px;
                pos++;
                continue; //表示文字はない
            } else {
                pattno = _draw_string[pos] - _chr_ptn_zero; //通常文字列
            }
            //プロポーショナルな幅計算
            int w = ((_chr_width_px - _aWidthPx[_draw_string[pos]]) / 2);
            offset_x = x_tmp - w;
            x_tmp = offset_x + _chr_width_px - w;

            //情報更新
            _paOffset_x[pos] = offset_x;
            _paOffset_y[pos] = offset_y;
            getUvFlipper()->getUV(pattno, u,v);
            _paOffset_u[pos] = u;
            _paOffset_v[pos] = v;

            pos++;
        }
    } else if (_align == ALIGN_RIGHT) {
        //右から表示する
        pixcoord offset_x = 0;
        pixcoord x_tmp = offset_x;
        float u, v;
        int pos = _len-1;
        int pattno = 0;
        int w;
        while (true) {
            if (pos == -1) { //一番左に到達
                break; //おしまい
            } else if (_draw_string[pos] == (int)('\n')) {
                offset_x = 0;
                x_tmp = offset_x;
                offset_y -= _chr_height_px;
                pos--;
                continue;
            } else {
                pattno = _draw_string[pos] - _chr_ptn_zero; //通常文字列
            }
            //プロポーショナルな幅計算
            w = ((_chr_width_px - _aWidthPx[_draw_string[pos]]) / 2);
            offset_x = x_tmp - (w + _aWidthPx[_draw_string[pos]]);
            x_tmp = offset_x + w;

            //情報更新
            _paOffset_x[pos] = offset_x;
            _paOffset_y[pos] = offset_y;
            getUvFlipper()->getUV(pattno, u,v);
            _paOffset_u[pos] = u;
            _paOffset_v[pos] = v;

            pos--;
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
    //float transformed_x, transformed_y, depth_z;   // : TEXCOORD1
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
    int draw_set_num = 0; //GgafDxMassBoardActorの同じモデルで同じテクニックが
                       //連続しているカウント数。同一描画深度は一度に描画する。
    GgafDxMassBoardEffect* pMassBoardEffect = _pMassBoardEffect;
    ID3DXEffect* pID3DXEffect = pMassBoardEffect->_pID3DXEffect;
    VERTEX_instancedata* paInstancedata = FontBoardActor::_aInstancedata;
    GgafDxFigureActor* pDrawActor = this;
    FontBoardActor* pFontBoardActor = nullptr;
    int model_set_num = _pMassBoardModel->_set_num;
    while (pDrawActor) {
        if (pDrawActor->getModel() == this->getModel() && pDrawActor->_hash_technique == this->_hash_technique) {
            pFontBoardActor = (FontBoardActor*)pDrawActor;
            int len = pFontBoardActor->_len;
            pixcoord x = C_PX(pFontBoardActor->_x);
            pixcoord y = C_PX(pFontBoardActor->_y);
            pixcoord z = C_PX(pFontBoardActor->_z);
            float* paOffset_x = pFontBoardActor->_paOffset_x;
            float* paOffset_y = pFontBoardActor->_paOffset_y;
            float* paOffset_u = pFontBoardActor->_paOffset_u;
            float* paOffset_v = pFontBoardActor->_paOffset_v;
            float alpha = pFontBoardActor->_alpha;
            for (int i = 0; i < len; i++) {
                paInstancedata->transformed_x = (float)(x + paOffset_x[i]);
                paInstancedata->transformed_y = (float)(y + paOffset_y[i]);
                paInstancedata->depth_z = (float)(z);
                paInstancedata->offset_u = paOffset_u[i];
                paInstancedata->offset_v = paOffset_v[i];
                paInstancedata->alpha    = alpha;                paInstancedata++;

                draw_set_num++;
                if (draw_set_num >= model_set_num) {
                   _pMassBoardModel->GgafDxMassBoardModel::draw(this, draw_set_num);
                   paInstancedata = FontBoardActor::_aInstancedata;
                   draw_set_num = 0;
                }
            }
            GgafDxSpacetime::_pActor_draw_active = pDrawActor; //描画セットの最後アクターをセット
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
     GGAF_DELETEARR(_paOffset_x);
     GGAF_DELETEARR(_paOffset_y);
     GGAF_DELETEARR(_paOffset_u);
     GGAF_DELETEARR(_paOffset_v);
}

