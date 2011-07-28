#ifndef GGAFDX9STRINGBOARDACTOR_H_
#define GGAFDX9STRINGBOARDACTOR_H_
namespace GgafDx9Core {

/**
 * 文字表示クラス .
 * GgafDx9BoardActor を継承し、文字セットテクスチャーから
 * 文字表示機能を追加したアクターです。<BR>
 * 次のようなテクスチャであることが前提。（※実際の画像は罫線無しです）<BR>
 * <code><pre>
 * ┌─┬─┬─┬─┬─┬─┬─┬─┐
 * │　│！│”│＃│＄│％│＆│’│
 * ├─┼─┼─┼─┼─┼─┼─┼─┤
 * │（│）│＊│＋│，│－│．│／│
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
 * @version 1.00
 * @since 2009/04/09
 * @author Masatoshi Tsuge
 */
class GgafDx9StringBoardActor : public GgafDx9BoardSetActor {
public:
    /** [r]描画文字列 */
    char* _draw_string;
    /** [r]文字バッファ(1024固定) */
    char* _buf;
    /** [r]文字列長 */
    int _len;
    /** [r]描画文字のパック数。(1パック = _pBoardSetModel->_set_num) */
    int _len_pack_num;
    /** [r]最終のパックで表示しなければならない文字数。*/
    int _remainder_len;

    /** [r/w]各文字間隔(px) */
    pixcoord _aWidthPx[256];
    /** [r/w]ベースの１文字幅(px) */
    pixcoord _chr_width_px;
    GgafDx9StringAlign _align;
    coord _X_offset_align;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_model 文字セットテクスチャのモデル定義ID
     * @return
     */
    GgafDx9StringBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override;

    virtual void processDraw() override;

    virtual void processAfterDraw() override {
    }

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
    virtual void update(coord X, coord Y, const char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, coord Z, const char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * 描画文字を更新設定  .
     * @param X 左上のX座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Y 左上のY座標(ピクセル : 座標 ＝ 1 : LEN_UNIT)
     * @param Z プライオリティ(値が小さい方が手前)
     * @param prm_str 描画文字列
     */
    virtual void update(coord X, coord Y, coord Z, char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     */
    virtual void update(const char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);

    /**
     * 描画文字を更新設定  .
     * @param prm_str 描画文字列
     */
    virtual void update(char* prm_str, GgafDx9StringAlign prm_align = ALIGN_LEFT);




    virtual void processSettlementBehavior() override;

    virtual ~GgafDx9StringBoardActor();

};

}
#endif /*GGAFDX9STRINGBOARDACTOR_H_*/
