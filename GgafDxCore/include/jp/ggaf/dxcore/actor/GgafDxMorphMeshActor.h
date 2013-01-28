#ifndef GGAFDXMORPHMESHACTOR_H_
#define GGAFDXMORPHMESHACTOR_H_
namespace GgafDxCore {

/**
 * モーフメッシュアクター.
 * GgafDxDrawableActor を継承し、Xファイル定義のメッシュ表示機能及び<BR>
 * モーフアニメーション機能を備えたアクター<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshActor : public GgafDxDrawableActor {

public:
    /** [r]モデル資源 */
    GgafDxMorphMeshModel* _pMorphMeshModel;
    /** [r]エフェクト資源 */
    GgafDxMorphMeshEffect* _pMorphMeshEffect;
    /** [r/w]モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[MAX_MORPH_TARGET+1]; //[0]は未使用、[1]～[6]がモーフターゲット1～6の重み
    /** モーフィング支援オブジェクト */
    GgafDxCore::GgafDxMorpher* _pMorpher;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxMorphMeshActor(const char* prm_name,
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
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxMorphMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * モーフターゲットメッシュ数取得
     * @return モーフターゲットメッシュ数
     */
    int getMorphTergetNum();

    /**
     * α設定.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;


    virtual ~GgafDxMorphMeshActor (); //デストラクタ
};

}
#endif /*GGAFDXMORPHMESHACTOR_H_*/
