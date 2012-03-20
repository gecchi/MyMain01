#ifndef GGAFDXD3DXANIMESHACTOR_H_
#define GGAFDXD3DXANIMESHACTOR_H_
namespace GgafDxCore {

/**
 * フレームアニメーション付きメッシュアクター.
 * GgafDxDrawableActor を継承し、Xファイル定義の
 * フレームアニメーションメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * アニメーションはパペッター(GgafDxPuppeteer)にお願いします。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshActor : public GgafDxDrawableActor {
private:

public:
    static DWORD FVF;
    /** モデル */
    GgafDxD3DXAniMeshModel* _pD3DXAniMeshModel;
    /** エフェクト資源 */
    GgafDxD3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** パペッター（アニメーション操作オブジェクト) */
    GgafDxPuppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

    GgafDxD3DXAniMeshActor(const char* prm_name,
                             const char* prm_model_id,
                             const char* prm_effect_id,
                             const char* prm_technique,
                             GgafCore::GgafStatus* prm_pStat,
                             GgafDxChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * α設定.
     * @param prm_alpha
     */
    void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    void addAlpha(float prm_alpha) override;

    virtual ~GgafDxD3DXAniMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXD3DXANIMESHACTOR_H_*/
