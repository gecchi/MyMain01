#ifndef GGAF_DX_SKINANIMESHACTOR_H_
#define GGAF_DX_SKINANIMESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

#include "jp/ggaf/dx/util/SkinAniMeshWorldMatStack.h"

namespace GgafDx {

/**
 * スキンアニメーション付きメッシュアクター.
 * Xファイル定義の
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
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".meshx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pColliChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    SkinAniMeshActor(const char* prm_name,
                 const char* prm_model,
                 const char* prm_effect_id,
                 const char* prm_technique);

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
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~SkinAniMeshActor();
};

}
#endif /*GGAF_DX_SKINANIMESHACTOR_H_*/
