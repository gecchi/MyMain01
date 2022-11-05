#ifndef GGAF_DX_DYNAD3DXMESHACTOR_H_
#define GGAF_DX_DYNAD3DXMESHACTOR_H_
#include "GgafDxCommonHeader.h"
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

    virtual ~DynaD3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_DYNAD3DXMESHACTOR_H_*/
