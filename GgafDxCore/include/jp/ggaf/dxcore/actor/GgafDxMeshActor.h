#ifndef GGAFDXMESHACTOR_H_
#define GGAFDXMESHACTOR_H_
namespace GgafDxCore {

/**
 * メッシュアクター.
 * GgafDxDrawableActor を継承し、独自のXファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxMeshActor : public GgafDxDrawableActor {

public:

    /** モデル資源 */
    GgafDxMeshModel* _pMeshModel;
    /** エフェクト資源 */
    GgafDxMeshEffect* _pMeshEffect;

    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDxMeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     GgafCore::GgafStatus* prm_pStat,
                     GgafDxChecker* prm_pChecker );

    /**
     * 下位継承用コンストラクタ
     * @param prm_name アクター名称（任意）
     * @param prm_model_id モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDxMeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_model_type,
                     const char* prm_effect_id,
                     const char* prm_effect_type,
                     const char* prm_technique,
                     GgafCore::GgafStatus* prm_pStat,
                     GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

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


    virtual ~GgafDxMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXMESHACTOR_H_*/
