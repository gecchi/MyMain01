#include "jp/ggaf/lib/actor/FontBoardActor.h"

#include "jp/ggaf/dxcore/actor/supporter/GgafDxUvFlipper.h"
#include "jp/ggaf/dxcore/effect/GgafDxMassBoardEffect.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FontBoardActor::FontBoardActor(const char* prm_name, const char* prm_model, GgafStatus* prm_pStat) :
        FixedFontBoardActor(prm_name, prm_model, prm_pStat) {
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < 256; i++) {
        _px_chr_width[i] = _chr_width_px;
    }
}

void FontBoardActor::prepare1(const char* prm_str) {
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
            *p_width_line_px += _px_chr_width[c]; //行の幅(px)を加算
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
        while(true) { //各文字単位のループ
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\0')) {
                break; //おしまい
            } else if (draw_chr == (int)('\n')) {
                nnn++;
                px_x = -(_align == ALIGN_CENTER ? _px_row_width[nnn]/2 : 0);
                x_tmp = px_x;
                px_y += _chr_height_px;
                p_chr++;
                continue; //表示文字はない
            }
            //プロポーショナルな幅計算
            int w = ((_chr_width_px - _px_chr_width[draw_chr]) / 2);
            px_x = x_tmp - w;
            x_tmp = px_x + _chr_width_px - w;

            //情報更新
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

        //右から表示する
        int chr_blank = _chr_blank;
        int chr_ptn_zero = _chr_ptn_zero;
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
            w = ((_chr_width_px - _px_chr_width[draw_chr]) / 2);
            px_x = x_tmp - (w + _px_chr_width[draw_chr]);
            x_tmp = px_x + w;
            //情報更新
            if (draw_chr != chr_blank) {
                pInstacePart->px_local_x = px_x;
                pInstacePart->px_local_y = px_y;
                getUvFlipper()->getUV(draw_chr-chr_ptn_zero, u, v);
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


FontBoardActor::~FontBoardActor() {
}
