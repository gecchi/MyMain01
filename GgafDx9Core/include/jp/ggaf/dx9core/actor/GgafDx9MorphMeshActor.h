#ifndef GGAFDX9MORPHMESHACTOR_H_
#define GGAFDX9MORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * モーフメッシュアクター.
 * GgafDx9DrawableActor を継承し、Xファイル定義のメッシュ表示機能及び<BR>
 * モーフアニメーション機能を備えたアクター<BR>
 */
class GgafDx9MorphMeshActor : public GgafDx9DrawableActor {
private:

public:
    /** モデル資源 */
    GgafDx9MorphMeshModel* _pMorphMeshModel;
    /** エフェクト資源 */
    GgafDx9MorphMeshEffect* _pMorphMeshEffect;
    /** モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[10]; //[0]は未使用、[1]～[9]がモーフターゲット1～9の重み

    /**
     * コンストラクタ
     * @param prm_name  モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名。GgafDx9MorphMeshModel の説明参照。
     * @param prm_technique エフェクト(GgafDx9MeshEffect.fx) のテクニック。
     * @param prm_pChecker   様々な判定を行なうチェッカークラスのインスタンスを渡す
     */
    GgafDx9MorphMeshActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

    /**
     * モーフターゲットメッシュ数取得
     * @return モーフターゲットメッシュ数
     */
    int getMorphTergetNum();

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

    virtual ~GgafDx9MorphMeshActor (); //デストラクタ
};

}
#endif /*GGAFDX9MORPHMESHACTOR_H_*/
