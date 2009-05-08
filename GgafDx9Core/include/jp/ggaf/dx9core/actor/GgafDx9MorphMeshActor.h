#ifndef GGAFDX9MORPHMESHACTOR_H_
#define GGAFDX9MORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9MorphMeshActor  : public GgafDx9UntransformedActor {
private:

public:

    char* _technique;
    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9;
    /** モデル資源接続 */
    GgafDx9ModelConnection* _pModelCon;
    /** モデル資源 */
    GgafDx9MorphMeshModel* _pMorphMeshModel;
    /** エフェクト資源接続 */
    GgafDx9EffectConnection* _pEffectCon;
    /** エフェクト資源 */
    GgafDx9MorphMeshEffect* _pMorphMeshEffect;
    /** 重み */
    float _weight;
    /**
     * コンストラクタ
     * @param prm_name  モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_technique エフェクト(GgafDx9MeshEffect.fx) のテクニック。
     * @param prm_pGeoMover 座標を操作するMoverクラスのインスタンスを渡す
     * @param prm_pGeoChecker   様々な判定を行なうチェッカークラスのインスタンスを渡す
     */
    GgafDx9MorphMeshActor (const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect,
                     const char* prm_technique,
                     GgafDx9GeometryMover* prm_pGeoMover,
                     GgafDx9GeometryChecker* prm_pGeoChecker );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

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
