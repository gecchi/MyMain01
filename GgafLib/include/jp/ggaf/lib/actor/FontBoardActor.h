#ifndef GGAFLIB_DEFAULTMASSBOARDACTOR_H_
#define GGAFLIB_DEFAULTMASSBOARDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMassBoardActor.h"

namespace GgafLib {

/**
 * 座標変換済みスプライトアクターの具象クラス.
 * GgafDxCore::GgafDxMassBoardActor を空実装した具象アクターです。
 * 本クラスを継承して色々画面表示を作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>オブジェクトへのアクセス</TH><TH>概要</TH><TH>CLASS名</TH></TR>
 * <TR><TD>getProgress()</TD><TD>進捗管理</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>黒衣。移動回転支援</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>パラパラアニメーション支援</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTx()</TD><TD>効果音発生管理</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * </TABLE>
 * <B>【注意】</B>拡大縮小支援(GgafDxCore::GgafDxScaler)は使用出来ません。
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class FontBoardActor : public GgafDxCore::GgafDxMassBoardActor {

private:
    struct VERTEX_instancedata {
        float transformed_x, transformed_y, depth_z;   // : TEXCOORD1
        float offset_u, offset_v, alpha;               // : TEXCOORD2
    };
    static VERTEX_instancedata _aInstancedata[];
    static void createVertexInstaceData(GgafDxCore::GgafDxMassModel::VertexInstaceDataInfo* out_info);

public:
    /** [r/w]パターン番号0とする文字 */
    int _chr_ptn_zero;
    /** [r]描画文字列 */
    int* _draw_string;
    /** [r]受け入れ可能な文字数(文字バッファの長さ) */
    int _max_len;
    /** [r]文字バッファ */
    int* _buf;

    float* _paOffset_x;
    float* _paOffset_y;
    float* _paOffset_u;
    float* _paOffset_v;
    /** [r]文字列長 */
    int _len;
    /** [r/w]ベースの１文字幅(px) */
    pixcoord _chr_width_px;
    /** [r/w]ベースの１文字高さ(px) */
    pixcoord _chr_height_px;
    /** [r/w]各文字間隔(px) */
    pixcoord _aWidthPx[256];
    /** [r]文字バッファの文字列の行単位の幅(px) */
    pixcoord _aWidth_line_px[1024];
    /** [r]文字バッファの文字列の改行数 */
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

    virtual void setAlign(GgafDxAlign prm_align, GgafDxValign prm_valign) override;
    virtual void setAlign(GgafDxAlign prm_align) override;
    virtual void setValign(GgafDxValign prm_valign) override;

    void updateOffset();
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
    FontBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat = nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~FontBoardActor();

};

}
#endif /*GGAFLIB_DEFAULTMASSBOARDACTOR_H_*/
