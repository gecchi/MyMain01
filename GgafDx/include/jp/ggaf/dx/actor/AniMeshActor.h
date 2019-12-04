#ifndef GGAF_DX_ANIMESHACTOR_H_
#define GGAF_DX_ANIMESHACTOR_H_
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
class AniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** モデル */
    AniMeshModel* _pAniMeshModel;
    /** エフェクト資源 */
    AniMeshEffect* _pAniMeshEffect;
    /** パペッター（アニメーション操作オブジェクト) */
    Puppeteer* _pPuppeteer;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    AniMeshActor(const char* prm_name,
                     const char* prm_model_id,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual ~AniMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_ANIMESHACTOR_H_*/
