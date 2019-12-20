#ifndef GGAF_DX_SKINANIMESHACTOR_H_
#define GGAF_DX_SKINANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/SkinAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * スキンアニメーション付きメッシュアクター.
 * FigureActor を継承し、Xファイル定義の
 * フレームアニメーションメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * アニメーションはパペッター(Puppeteer)にお願いします。<BR>
 * @version 1.00
 * @since 2019/12/20
 * @author Masatoshi Tsuge
 */
class SkinAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** モデル */
    SkinAniMeshModel* _pSkinAniMeshModel;
    /** エフェクト資源 */
    SkinAniMeshEffect* _pSkinAniMeshEffect;
    /** パペッター（アニメーション操作オブジェクト) */
    Puppeteer* _pPuppeteer;

    SkinAniMeshWorldMatStack _stackWorldMat;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    SkinAniMeshActor(const char* prm_name,
                 const char* prm_model_id,
                 const char* prm_effect_id,
                 const char* prm_technique,
                 Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual Puppeteer* getPuppeteer() {
        return _pPuppeteer;
    }

    virtual ~SkinAniMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_SKINANIMESHACTOR_H_*/
