#ifndef GGAFDX9D3DXMESHACTOR_H_
#define GGAFDX9D3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9DrawableUntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9D3DXMeshActor : public GgafDx9DrawableUntransformedActor {
private:

public:

    char* _technique;
    static DWORD FVF;
    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9;
    /** モデル */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;
    /** エフェクト資源接続 */
    GgafDx9EffectConnection* _pEffectCon;
    /** エフェクト資源 */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9D3DXMeshActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

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

    virtual ~GgafDx9D3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9D3DXMESHACTOR_H_*/
