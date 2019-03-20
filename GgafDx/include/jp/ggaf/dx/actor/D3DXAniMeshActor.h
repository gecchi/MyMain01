#ifndef GGAF_DX_D3DXANIMESHACTOR_H_
#define GGAF_DX_D3DXANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * フレームアニメーション付きメッシュアクター.
 * FigureActor を継承し、Xファイル定義の
 * フレームアニメーションメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * アニメーションはパペッター(Puppeteer)にお願いします。<BR>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class D3DXAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** モデル */
    D3DXAniMeshModel* _pD3DXAniMeshModel;
    /** エフェクト資源 */
    D3DXAniMeshEffect* _pD3DXAniMeshEffect;
    /** パペッター（アニメーション操作オブジェクト) */
    Puppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    D3DXAniMeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual ~D3DXAniMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_D3DXANIMESHACTOR_H_*/
