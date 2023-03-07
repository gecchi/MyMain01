#ifndef GGAF_DX_D3DXANIMESHACTOR_H_
#define GGAF_DX_D3DXANIMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/util/BoneAniMeshWorldMatStack.h"
namespace GgafDx {

/**
 * 現在未使用<BR>
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
    D3DXAniMeshActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     CollisionChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~D3DXAniMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_D3DXANIMESHACTOR_H_*/
