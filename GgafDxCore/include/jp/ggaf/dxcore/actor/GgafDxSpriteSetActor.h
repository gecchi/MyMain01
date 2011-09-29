#ifndef GGAFDXSPRITESETACTOR_H_
#define GGAFDXSPRITESETACTOR_H_
namespace GgafDxCore {

/**
 * スプライトセットアクター.
 * GgafDxDrawableActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、複数同時描画に最適化されたアクターです。<BR>
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteSetActor : public GgafDxDrawableActor {

public:
    /** 同時描画セット数 */
    int _draw_set_num;

    /** モデルオブジェクトへのポインタ */
    GgafDxSpriteSetModel* _pSpriteSetModel;

    /** エフェクト */
    GgafDxSpriteSetEffect* _pSpriteSetEffect;

    /** UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* _pUvFlipper;

    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDxSpriteSetActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafCore::GgafStatus* prm_pStat,
                          GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteSetActor();

    /**
     * α設定.
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha) override;

    /**
     * α加算 .
     * @param prm_fAlpha
     */
    void addAlpha(float prm_fAlpha) override;
};

}
#endif /*GGAFDXSPRITESETACTOR_H_*/
