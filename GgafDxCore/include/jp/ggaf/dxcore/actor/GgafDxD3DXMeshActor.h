#ifndef GGAFDXD3DXMESHACTOR_H_
#define GGAFDXD3DXMESHACTOR_H_
namespace GgafDxCore {

/**
 * DirectXメッシュアクター.
 * GgafDxDrawableActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXMeshActor : public GgafDxDrawableActor {
private:

public:
    static DWORD FVF;
    /** [r]モデル */
    GgafDxD3DXMeshModel* _pD3DXMeshModel;
    /** [r]エフェクト資源 */
    GgafDxMeshEffect* _pMeshEffect;

    GgafDxD3DXMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    /**
     * GgafDxD3DXMeshActorを描画 .
     */
    virtual void processDraw() override;

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

    virtual ~GgafDxD3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXD3DXMESHACTOR_H_*/
