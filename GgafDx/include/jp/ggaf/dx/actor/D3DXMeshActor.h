#ifndef GGAF_DX_D3DXMESHACTOR_H_
#define GGAF_DX_D3DXMESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * DirectXメッシュアクター.
 * D3DXLoadMeshFromX()で読み込み、表示するアクター<BR>
 * @version 1.00
 * @since 2008/01/28
 * @author Masatoshi Tsuge
 */
class D3DXMeshActor : public FigureActor {

public:
    static DWORD FVF;
    /** [r]モデル */
    D3DXMeshModel* _pD3DXMeshModel;
    /** [r]エフェクト資源 */
    MeshEffect* _pMeshEffect;

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
    D3DXMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect_id,
                  const char* prm_technique);

    /**
     * D3DXMeshActorを描画 .
     */
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

    virtual ~D3DXMeshActor();
};

}
#endif /*GGAF_DX_D3DXMESHACTOR_H_*/
