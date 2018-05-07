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

    /** [r/w]ベースの１文字幅(px) */
    pixcoord _chr_base_width_px;
    /** [r/w]ベースの１文字高さ(px) */
    pixcoord _chr_base_height_px;
    /** [r/w]パターン番号0とする文字 */
    int _chr_ptn_zero;
    /** [r/w]表示不要空白とする文字(指定すると描画文字が減る) */
    int _chr_blank;
    /** [r/w]改行とする文字 */
    int _chr_newline;
    /** [r]描画文字列 */
    int* _draw_string;
    /** [r]受け入れ可能な文字数(文字バッファの長さ) */
    int _max_len;
    /** [r]文字バッファ */
    int* _buf;
    struct InstancePart {
        float px_local_x;
        float px_local_y;
        float offset_u;
        float offset_v;
    };
    InstancePart* _paInstancePart;
    /** [r]文字列長 */
    int _len;
    /** [r]描画文字数（文字列長から改行と空白を除いた値）*/
    int _draw_chr_num;
    /** [r]文字バッファの文字列の行単位の幅(px) */
    pixcoord _px_row_width[L];
    /** [r]文字バッファの文字列の行数 */
    int _nn;
    /** [r/w]各文字間隔(px) */
    pixcoord _px_chr_width[N];
    bool _is_fixed_width;

    pixcoord _px_total_width;
    pixcoord _px_total_height;
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

    /**
     * 全ての文字の設定。update() により表示文字を更新しないと反映されません。 .
     * @param prm_width_ratio 幅の率(初期値の幅に乗じる値、初期値は1.0)
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
     * 文字の幅の比率を個々に設定。update() により表示文字を更新しないと反映されません。 .
     * @param c 文字
     * @param prm_width_ratio 幅の率(初期値の幅に乗じる値、初期値は1.0)
     */
    inline void setChrWidthRatio(const unsigned char c, double prm_width_ratio) {
        _is_fixed_width = false;
        _px_chr_width[c] = _chr_base_width_px * prm_width_ratio;
    }
    /**
     * 空白の文字を設定する .
     * 空白の文字は描画処理がスキップされるので、パフォーマンスが向上する。
     * デフォルトは ' ' が設定されている。
     * @param prm_c 空白文字
     */
    inline void setBlankChr(char prm_c) {
        _chr_blank = (int)prm_c;
    }

    /**
     * 改行文字を設定する .
     * デフォルトは '\n' が設定されている。
     * @param prm_c
     */
    inline void setNewlineChr(char prm_c) {
        _chr_newline = (int)prm_c;
    }

    /**
     * UvFlipperのパターン番号0番とする文字を設定する .
     * デフォルトは ' ' が設定されている。
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
    _max_len = 8;  //最初はバッファは8文字
    _chr_ptn_zero = (int)(' '); //GgafDxUvFlipper の パターン0番の文字。
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
    //デフォルトの１文字の幅(px)設定
    for (int i = 0; i < N; i++) {
        _px_chr_width[i] = _chr_base_width_px;
    }
    _px_total_width = 0;
    _px_total_height = 0;
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::chengeBufferLen(int prm_max_len) {
    _max_len = 8*((prm_max_len+8)/8); //直近８の倍数に切り上げ
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
            throwGgafCriticalException("範囲外の扱えない文字種がありました prm_str=["<<prm_str<<"] の中の値:"<<c<<"。 0～"<<(N-1)<<"の範囲にして下さい。this="<<this);
        }
#endif
        if (c != (*p_draw_string)) {
            is_different = true;
            *p_draw_string = c; //保存
        }
        if (c == _chr_newline) {
            if (_nn == 0 || max_width_line_px < *p_width_line_px) {
                max_width_line_px = *p_width_line_px;
            }
            _nn++; //行数カウント
            ++p_width_line_px;  *p_width_line_px = 0; //行の幅保持配列を次へ ＆ 0にリセット
        } else if (c == '\0') {
            if (_nn == 0 || max_width_line_px < *p_width_line_px) {
                max_width_line_px = *p_width_line_px;
            }
            _nn++; //文字列最後を行数１としてカウント。文字列は改行で終わる必要がない。
            break;
        } else {
            *p_width_line_px += (is_fixed_width ? chr_base_width_px : _px_chr_width[c]); //行の幅(px)を加算
        }
        if (c != chr_blank) { //ブランク
            _draw_chr_num++; //描画文字数カウント
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
        throwGgafCriticalException("文字列の行数が"<<L<<"個を超えました。name="<<_pBaseActor->getName()<<" prm_str="<<prm_str);
    }
#endif
}

template<class T, int N, int L>
void ICharacterChip<T, N, L>::prepare2() {
    //ALIGN_RIGHT やVALIGN_BOTTOM の為に
    //どうしても２回全文字をループでなめる必要がある。
    //prepare1() は１回目のループ、 prepare2() は２回目のループに相当
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
        //固定幅時
        //初期Y位置を決める
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
        while(true) { //各文字単位のループ
            int draw_chr = *p_chr;
            if (draw_chr == (int)('\0')) {
                break; //おしまい
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
                continue; //表示文字はない
            }
            //情報更新
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
        //可変幅時
        //初期Y位置を決める
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
            while(true) { //各文字単位のループ
                int draw_chr = *p_chr;
                if (draw_chr == (int)('\0')) {
                    break; //おしまい
                } else if (draw_chr == chr_newline) {
                    nnn++;
                    px_x = -(align == ALIGN_CENTER ? _px_row_width[nnn]/2 : 0);
                    x_tmp = px_x;
                    px_y += chr_base_height_px;
                    ++p_chr;
                    continue; //表示文字はない
                }
                //プロポーショナルな幅計算
                int w = ((chr_base_width_px - _px_chr_width[draw_chr]) / 2);
                px_x = x_tmp - w;
                x_tmp = px_x + chr_base_width_px - w;

                //情報更新
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

            //右から表示する
            pixcoord px_x = 0;
            pixcoord x_tmp = px_x;
            float u, v;
            int w;
            int* p_chr = &(_draw_string[_len-1]); //末尾から回す。_len は strlen の値
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
                //プロポーショナルな幅計算
                w = ((chr_base_width_px - _px_chr_width[draw_chr]) / 2);
                px_x = x_tmp - (w + _px_chr_width[draw_chr]);
                x_tmp = px_x + w;
                //情報更新
                if (draw_chr != chr_blank) {
                    pInstancePart->px_local_x = px_x;
                    pInstancePart->px_local_y = px_y;
                    pUvFlipper->getUV(draw_chr-chr_ptn_zero, u, v);
                    pInstancePart->offset_u = u;
                    pInstancePart->offset_v = v;
                    pInstancePart--;
                }
                if (p_chr == _draw_string) { //一番左に到達
                     break; //おしまい
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
