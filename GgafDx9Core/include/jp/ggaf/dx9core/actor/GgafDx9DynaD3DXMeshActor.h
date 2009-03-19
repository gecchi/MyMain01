#ifndef GGAFDX9DYNAD3DXMESHACTOR_H_
#define GGAFDX9DYNAD3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * GgafDx9D3DXMeshActor との違いは、頂点バッファに直接アクセスをことに考慮して、<BR>
 * D3DXMESH_DYNAMIC オプションを使用しているところだけです。<BR>
 * 頂点をロックする場合はGgafDx9D3DXMeshActorではなく、こちらを継承してください。<BR>
 */
class GgafDx9DynaD3DXMeshActor : public GgafDx9UntransformedActor {
private:

public:

	char* _technique;
    static DWORD FVF;
    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9;
    /** モデルオブジェクトへのポインタ */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;
    /** エフェクト資源接続 */
    GgafDx9EffectConnection* _pEffectCon;
    /** エフェクト資源 */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9DynaD3DXMeshActor(const char* prm_name,
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

    virtual ~GgafDx9DynaD3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9DYNAD3DXMESHACTOR_H_*/
