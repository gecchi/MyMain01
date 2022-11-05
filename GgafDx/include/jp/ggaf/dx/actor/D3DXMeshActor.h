#ifndef GGAF_DX_D3DXMESHACTOR_H_
#define GGAF_DX_D3DXMESHACTOR_H_
#include "GgafDxCommonHeader.h"
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
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    D3DXMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect_id,
                  const char* prm_technique,
                  CollisionChecker* prm_pChecker);

    /**
     * D3DXMeshActorを描画 .
     */
    virtual void processDraw() override;

    virtual ~D3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_D3DXMESHACTOR_H_*/
