#ifndef GGAFDXSTRINGSPRITEACTOR_H_
#define GGAFDXSTRINGSPRITEACTOR_H_
namespace GgafDxCore {

/**
 * 文字表示クラス .
 * GgafDxSpriteSetActor を継承し、文字セットテクスチャーから
 * 文字表示機能を追加したアクターです。<BR>
 * 次のようなテクスチャであることが前提。（※実際の画像は罫線無しです）<BR>
 * <code><pre>
 * ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * │　│！│”│＃│＄│％│＆│’│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │（│）│＊│＋│，│−│．│／│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │０│１│２│３│４│５│６│７│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │８│９│：│；│＜│＝│＞│？│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │＠│Ａ│Ｂ│Ｃ│Ｄ│Ｅ│Ｆ│Ｇ│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │Ｈ│Ｉ│Ｊ│Ｋ│Ｌ│Ｍ│Ｎ│Ｏ│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │Ｐ│Ｑ│Ｒ│Ｓ│Ｔ│Ｕ│Ｖ│Ｗ│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │Ｘ│Ｙ│Ｚ│［│＼│］│＾│＿│
 * └─┴─┴─┴─┴─┴─┴─┴─┘
 * </pre></code>
 * 文字表示と言ってもUVを切り替えて連続表示るだけ。
 * TODO:GgafDxStringBoardActorと共通化したい・・・
 * @version 1.00
 * @since 2009/04/09
 * @author Masatoshi Tsuge
 */
class GgafDxStringSpriteActor : public GgafDxSpriteSetActor {

public:
    /** [r]描画文字列 */
    char* _draw_string;
    /** [r]文字バッファ(1024固定) */
    char* _buf;
    /** [r]文字列長 */
    int _len;
    /** [r/w]ベースの１文字幅(px) */
    pixcoord _chr_width_px;
    /** [r/w]ベースの１文字高さ(px) */
    pixcoord _chr_height_px;
    /** [r/w]各文字間隔(px) */
    pixcoord _aWidthPx[256];
    /** [r]文字バッファの行単位の幅(px) */
    pixcoord _aWidth_line_px[256];
    /** [r]文字バッファ改行数 */
    int _nn;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_model 文字セットテクスチャのモデル定義ID
     * @return
     */
    GgafDxStringSpriteActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override;

    virtual void processDraw() override;

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) {
    }
    /**
     * 描画文字を更新設定 .
     * @param X X座標
     * @param Y Y座標
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, const char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param X X座標
     * @param Y Y座標
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, char* prm_str);

    /**
     * 描画文字を更新設定  .
     * @param X X座標
     * @param Y Y座標
     * @param Z Z座標
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param X X座標
     * @param Y Y座標
     * @param Z Z座標
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     */
    virtual void update(const char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     */
    virtual void update(char* prm_str);

    /**
     * 描画文字を更新設定 .
     * @param X X座標
     * @param Y Y座標
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param X X座標
     * @param Y Y座標
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * 描画文字を更新設定  .
     * @param X X座標
     * @param Y Y座標
     * @param Z Z座標
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param X X座標
     * @param Y Y座標
     * @param Z Z座標
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    virtual ~GgafDxStringSpriteActor();

};

}
#endif /*GGAFDXSTRINGSPRITEACTOR_H_*/
