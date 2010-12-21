#ifndef GGAFDX9MESHACTOR_H_
#define GGAFDX9MESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9DrawableActor を継承し、独自のXファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class GgafDx9MeshActor : public GgafDx9DrawableActor {

public:

    /** モデル資源 */
    GgafDx9MeshModel* _pMeshModel;
    /** エフェクト資源 */
    GgafDx9MeshEffect* _pMeshEffect;

    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDx9MeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     GgafDx9Checker* prm_pChecker );

    GgafDx9MeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_model_type,
                     const char* prm_effect_id,
                     const char* prm_effect_type,
                     const char* prm_technique,
                     GgafDx9Checker* prm_pChecker);

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


    virtual ~GgafDx9MeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9MESHACTOR_H_*/
