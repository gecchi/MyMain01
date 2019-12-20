#ifndef GGAF_DX_BONEANIMESHACTOR_H_
#define GGAF_DX_BONEANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * フレームアニメーション付きメッシュアクター.
 * FigureActor を継承し、Xファイル定義の
 * フレームアニメーションメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 * アニメーションはパペッター(Puppeteer)にお願いします。<BR>
 * @version 1.00
 * @since 2019/11/26
 * @author Masatoshi Tsuge
 */
class BoneAniMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** モデル */
    BoneAniMeshModel* _pBoneAniMeshModel;
    /** エフェクト資源 */
    BoneAniMeshEffect* _pBoneAniMeshEffect;
    /** パペッター（アニメーション操作オブジェクト) */
    Puppeteer* _pPuppeteer;

    BoneAniMeshWorldMatStack _stackWorldMat;

    LPD3DXANIMATIONSET* _papAnimationSet;

public:
    BoneAniMeshActor(const char* prm_name,
                 const char* prm_model_id,
                 const char* prm_effect_id,
                 const char* prm_technique,
                 Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual Puppeteer* getPuppeteer() {
        return _pPuppeteer;
    }

    virtual ~BoneAniMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_BONEANIMESHACTOR_H_*/
