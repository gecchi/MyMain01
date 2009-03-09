#ifndef GGAFDX9PRIMITIVEACTOR_H_
#define GGAFDX9PRIMITIVEACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9PrimitiveActor : public GgafDx9UntransformedActor {
private:

public:

    char* _technique;

    /** モデル */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9PrimitiveModel* _pPrimitiveModel;
    /** エフェクト */
    GgafDx9EffectConnection* _pEffectConnection;
    GgafDx9MeshEffect* _pMeshEffect;
    ID3DXEffect* _pID3DXEffect;

    /**
     * コンストラクタ
     * @param prm_name  モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_technique エフェクトのテクニック。
     * @param prm_pGeoMover 座標を操作するMoverクラスのインスタンスを渡す
     * @param prm_pGeoChecker   様々な判定を行なうチェッカークラスのインスタンスを渡す
     */
    GgafDx9PrimitiveActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_technique,
                         GgafDx9GeometryMover* prm_pGeoMover,
                         GgafDx9GeometryChecker* prm_pGeoChecker);

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

    virtual ~GgafDx9PrimitiveActor(); //デストラクタ
};

}
#endif /*GGAFDX9PRIMITIVEACTOR_H_*/
