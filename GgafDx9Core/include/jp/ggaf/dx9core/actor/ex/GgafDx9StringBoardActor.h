#ifndef GGAFDX9STRINGBOARDACTOR_H_
#define GGAFDX9STRINGBOARDACTOR_H_
namespace GgafDx9Core {

/**
 * 文字表示クラス(座標変換済み).
 *  * GgafDx9BoardActor を継承し、文字セットテクスチャーから
 *  文字表示機能を追加したアクターです。<BR>
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
private:
    /** 描画文字列 */
    char* _draw_string;
    /** 文字バッファ(1024固定) */
    char* _buf;
    /** 文字列長 */
    int _len;
    /** 描画文字のパック数。(1パック = _pBoardSetModel->_set_num) */
    int _len_pack_num;
    /** 最終のパックで表示しなければならない文字数。*/
    int _remainder_len;

public:
    /** [r/w]各文字間隔(px) */
    int _aWidthPx[256];
    /** [r/w]ベースの１文字幅(px) */
    int _chr_width;

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
     * @param prm_x 左上のX座標(px)
     * @param prm_y 左上のY座標(px)
     * @param prm_str 描画文字列
     */
    virtual void update(int X, int Y, const char* prm_str);

    /**
     * 描画文字を更新設定  .
     * @param prm_x 左上のX座標(px)
     * @param prm_y 左上のY座標(px)
     * @param prm_str 描画文字列
     */
    virtual void update(int X, int Y, char* prm_str);

    /**
     * 描画文字を更新設定  .
     * @param prm_x 左上のX座標(px)
     * @param prm_y 左上のY座標(px)
     * @param prm_z プライオリティ(0.0 <= z < 1.0 値が小さい方が手前)
     * @param prm_str 描画文字列
     */
    virtual void update(int X, int Y, int Z, const char* prm_str);

    /**
     * 描画文字を更新設定  .
     * @param prm_x 左上のX座標(px)
     * @param prm_y 左上のY座標(px)
     * @param prm_z プライオリティ(0.0 <= z < 1.0 値が小さい方が手前)
     * @param prm_str 描画文字列
     */
    virtual void update(int X, int Y, int Z, char* prm_str);

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
     * 描画位置を更新設定  .
     * @param prm_x 左上のX座標(px)
     * @param prm_y 左上のY座標(px)
     * @param prm_z プライオリティ(0.0 <= z < 1.0 値が小さい方が手前)
     */
    virtual void update(int X, int Y, int Z);

    /**
     * 描画位置を更新設定  .
     * @param prm_x 左上のX座標(px)
     * @param prm_y 左上のY座標(px)
     */
    virtual void update(int X, int Y);

    virtual ~GgafDx9StringBoardActor();

};

}
#endif /*GGAFDX9STRINGBOARDACTOR_H_*/
