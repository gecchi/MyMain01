#ifndef GGAF_DX_BONEANIMESHACTOR_H_
#define GGAF_DX_BONEANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * フレームアニメーション付きメッシュアクター.
 * フレームアニメーションメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
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
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".meshx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    BoneAniMeshActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     CollisionChecker* prm_pChecker);

    virtual void processDraw() override;

    virtual Puppeteer* getPuppeteer() {
        return _pPuppeteer;
    }

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModel(int prm_model_index) override;

    virtual ~BoneAniMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_BONEANIMESHACTOR_H_*/
