#ifndef GGAFDXCORE_GGAFDXD3DXANIMESHACTOR_H_
#define GGAFDXCORE_GGAFDXD3DXANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxFigureActor.h"

namespace GgafDxCore {

/**
 * フレームアニメーション付きメッシュアクター.
 * GgafDxFigureActor を継承し、Xファイル定義の
 * フレームアニメーションメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * アニメーションはパペッター(GgafDxPuppeteer)にお願いします。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class GgafDxD3DXAniMeshActor : public GgafDxFigureActor {

public:
    static DWORD FVF;
    /** モデル */
    GgafDxD3DXAniMeshModel* _pD3DXAniMeshModel;
    /** エフェクト資源 */
    GgafDxD3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** パペッター（アニメーション操作オブジェクト) */
    GgafDxPuppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
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
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    virtual ~GgafDxD3DXAniMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXD3DXANIMESHACTOR_H_*/
