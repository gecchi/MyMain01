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

    /** [r/w]ベースの１文字幅(px) */
    const pixcoord _chr_width_px;
    /** [r/w]ベースの１文字高さ(px) */
    const pixcoord _chr_height_px;
    /** [r/w]パターン番号0とする文字 */
    int _chr_ptn_zero;
    /** [r/w]表示不要空白とする文字(指定すると描画文字が減る) */
    int _chr_blank;
    /** [r]描画文字列 */
    int* _draw_string;
    /** [r]受け入れ可能な文字数(文字バッファの長さ) */
    int _max_len;
    /** [r]文字バッファ */
    int* _buf;
    struct InstacePart {
        float px_local_x;
        float px_local_y;
        float offset_u;
        float offset_v;
    };
    InstacePart* _paInstacePart;
    /** [r]文字列長 */
    int _len;
    /** [r]描画文字数（文字列長から改行と空白を除いた値）*/
    int _draw_chr_num;
    /** [r]文字バッファの文字列の行単位の幅(px) */
    pixcoord _px_row_width[1024];
    /** [r]文字バッファの文字列の行数 */
    int _nn;

    /**
     * 内部バッファ数を引数の直近8の倍数の切り上げに変更 .
     * @param prm_max_len 新しいバッファ数
     */
    void chengeBufferLen(int prm_max_len);

public:
    /**
     * 描画文字を更新設定 .
     * @param X X座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y Y座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, const char* prm_str);

    /**
     * 描画文字を更新設定  .
     * @param X X座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y Y座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     */
    virtual void update(const char* prm_str);

    /**
     * 描画文字を更新設定 .
     * @param X X座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y Y座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は文字列の左端／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端
     * @param prm_valign VALIGN_TOP:Y座標は文字列の高さの上辺／VALIGN_MIDDLE:Y座標は文字列の高さの真ん中／VALIGN_BOTTOM:Y座標は文字列の高さの底辺
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * 描画文字を更新設定  .
     * @param X X座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y Y座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は文字列の左端／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端
     * @param prm_valign VALIGN_TOP:Y座標は文字列の高さの上辺／VALIGN_MIDDLE:Y座標は文字列の高さの真ん中／VALIGN_BOTTOM:Y座標は文字列の高さの底辺
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は文字列の左端／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端
     * @param prm_valign VALIGN_TOP:Y座標は文字列の高さの上辺／VALIGN_MIDDLE:Y座標は文字列の高さの真ん中／VALIGN_BOTTOM:Y座標は文字列の高さの底辺
     */
    virtual void update(const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    virtual void prepare1(const char* prm_str);
    virtual void prepare2();
    /**
     * 描画文字が更新された時に呼び出されるコールバック .
     * 下位で実装してください。
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
}

template<class T>
void IFixedFont<T>::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //直近８の倍数に切り上げ
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
        throwGgafCriticalException("文字列の行数が1024個を超えました。name="<<_pBaseActor->getName()<<" prm_str="<<prm_str);
    }
#endif
}

template<class T>
void IFixedFont<T>::prepare2() {
    //ALIGN_RIGHT やVALIGN_BOTTOM の為に
    //どうしても２回全文字をループでなめる必要がある。
    //prepare1() は１回目のループ、 prepare2() は２回目のループに相当
    if (_len == 0) {
        return;
    }
    //初期Y位置を決める
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
    while(true) { //各文字単位のループ
        int draw_chr = *p_chr;
        if (draw_chr == (int)('\0')) {
            break; //おしまい
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
            continue; //表示文字はない
        }
        //情報更新
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
