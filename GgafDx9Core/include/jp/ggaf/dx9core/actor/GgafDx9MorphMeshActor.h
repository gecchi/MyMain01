#ifndef GGAFDX9MORPHMESHACTOR_H_
#define GGAFDX9MORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * モーフメッシュアクター.
 * GgafDx9DrawableActor を継承し、Xファイル定義のメッシュ表示機能及び<BR>
 * モーフアニメーション機能を備えたアクター<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDx9MorphMeshActor : public GgafDx9DrawableActor {
private:

public:
    /** モデル資源 */
    GgafDx9MorphMeshModel* _pMorphMeshModel;
    /** エフェクト資源 */
    GgafDx9MorphMeshEffect* _pMorphMeshEffect;
    /** モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[MAX_MORPH_TARGET+1]; //[0]は未使用、[1]～[6]がモーフターゲット1～6の重み

    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDx9MorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    /**
     * 下位継承用コンストラクタ
     * @param prm_name アクター名称（任意）
     * @param prm_model_id モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDx9MorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_model_type,
                          const char* prm_effect_id,
                          const char* prm_effect_type,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * モーフターゲットメッシュ数取得
     * @return モーフターゲットメッシュ数
     */
    int getMorphTergetNum();

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


    virtual ~GgafDx9MorphMeshActor (); //デストラクタ
};

}
#endif /*GGAFDX9MORPHMESHACTOR_H_*/
