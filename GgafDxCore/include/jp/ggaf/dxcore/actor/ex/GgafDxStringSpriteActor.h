#ifndef GGAFDXSTRINGSPRITEACTOR_H_
#define GGAFDXSTRINGSPRITEACTOR_H_
namespace GgafDxCore {

/**
 * 座標未変換文字表示クラス（現在作成中で、未使用！）
 */
class GgafDxStringSpriteActor : public GgafDxSpriteSetActor {
    /**
     * オーバーライド不可 .
     */
//    virtual void processSettlementBehavior() override;

public:
    /** [r]描画文字列 */
    char* _draw_string;
    /** [r]文字バッファ(1024固定) */
    char* _buf;
    /** [r]文字列長 */
    int _len;
    /** [r]描画文字のパック数。(1パック = _pSpriteSetModel->_set_num) */
    int _len_pack_num;
    /** [r]最終のパックで表示しなければならない文字数。*/
    int _remainder_len;

    /** [r/w]ベースの１文字幅(px) */
    pixcoord _chr_width_px;
    /** [r/w]ベースの１文字高さ(px) */
    pixcoord _chr_height_px;
    /** [r/w]各文字間隔(px) */
    pixcoord _aWidthPx[256];


    pixcoord _width_len_px;

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
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, const char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, char* prm_str);

    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str);
    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
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
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);

    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
     * @param prm_str 描画文字列
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str,
                        GgafDxAlign prm_align,
                        GgafDxValign prm_valign);
    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
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

    /**
     * 描画文字のアラインメントを設定する  .
     * @param prm_align ALIGN_LEFT:X座標は左端を意味する／ALIGN_CENTER:X座標は文字列の真ん中／ALIGN_RIGHT:X座標は右端を意味する
     * @param prm_valign VALIGN_TOP:Y座標は文字の高さの上辺を意味する／VALIGN_MIDDLE:Y座標は文字の高さの真ん中を意味する／VALIGN_BOTTOM:Y座標は文字の高さの底辺を意味する
     */
    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;

    virtual ~GgafDxStringSpriteActor();

};

}
#endif /*GGAFDXSTRINGSPRITEACTOR_H_*/
