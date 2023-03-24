#ifndef GGAF_DX_DYNAD3DXMESHACTOR_H_
#define GGAF_DX_DYNAD3DXMESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

//注意：このクラスは現在未使用です。削除予定。
//     固定機能パイプライン時に頂点書き換えのため作成したが、
//     現在は全てプログラマブルシェーダーであるため、もう使わない。
/**
 * メッシュアクター.
 * Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * D3DXMeshActor との違いは、頂点バッファに直接アクセスをことに考慮して、<BR>
 * D3DXMESH_DYNAMIC オプションを使用しているところだけです。<BR>
 * 頂点をロックする場合はD3DXMeshActorではなく、こちらを継承してください。<BR>
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DynaD3DXMeshActor : public FigureActor {

public:
    static DWORD FVF;
    D3DXMeshModel* _pD3DXMeshModel;
    /** エフェクト資源 */
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
    DynaD3DXMeshActor(const char* prm_name,
                      const char* prm_model,
                      const char* prm_effect_id,
                      const char* prm_technique,
                      CollisionChecker* prm_pChecker );

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

    virtual ~DynaD3DXMeshActor();
};

}
#endif /*GGAF_DX_DYNAD3DXMESHACTOR_H_*/
