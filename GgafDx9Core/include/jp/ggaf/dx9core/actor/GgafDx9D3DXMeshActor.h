#ifndef GGAFDX9D3DXMESHACTOR_H_
#define GGAFDX9D3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9DrawableActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9D3DXMeshActor : public GgafDx9DrawableActor {
private:

public:

    char* _technique;
    static DWORD FVF;
    /** モデル */
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;
    /** エフェクト資源 */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9D3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDraw();

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
