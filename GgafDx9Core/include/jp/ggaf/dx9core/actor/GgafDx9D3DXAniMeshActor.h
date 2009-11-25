#ifndef GGAFDX9D3DXANIMESHACTOR_H_
#define GGAFDX9D3DXANIMESHACTOR_H_
namespace GgafDx9Core {

/**
 * フレームアニメーションメッシュアクター.
 * GgafDx9DrawableActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDx9D3DXAniMeshActor : public GgafDx9DrawableActor {
private:

public:
    static DWORD FVF;
    /** モデル */
    GgafDx9D3DXAniMeshModel* _pD3DXAniMeshModel;
    /** エフェクト資源 */
    GgafDx9MeshEffect* _pMeshEffect;

    GgafDx9D3DXAniMeshActor(const char* prm_name,
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

    virtual ~GgafDx9D3DXAniMeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9D3DXANIMESHACTOR_H_*/
