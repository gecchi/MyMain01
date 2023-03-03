#ifndef GGAF_DX_CUBEMAPMESHSETACTOR_H_
#define GGAF_DX_CUBEMAPMESHSETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

namespace GgafDx {

/**
 * 環境マップメッシュセットアクター.
 * 環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetActor : public MeshSetActor, public ICubeMapActor {

public:

    /** モデル資源 */
    CubeMapMeshSetModel* _pCubeMapMeshSetModel;
    /** エフェクト資源 */
    CubeMapMeshSetEffect* _pCubeMapMeshSetEffect;

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
    CubeMapMeshSetActor(const char* prm_name,
                        const char* prm_model,
                        const char* prm_effect_id,
                        const char* prm_technique,
                        CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    /**
     * モデル資源(TYPE_CUBEMAPMESH_MODEL)を１つ生成して追加する。.
     * 初めて本メソッドを実行すると、内部リストに保持され、そのモデル資源が有効になります。
     * ２回目以降の実行は、生成したモデル資源を内部リストの末尾に追加します。（有効になりません）
     * @param prm_model モデル定義名
     * @return 生成された（＝リストの末尾に追加された）モデル資源
     */
    virtual MeshSetModel* addModel(const char* prm_model) override;

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModel(int prm_model_index) override;

    virtual ~CubeMapMeshSetActor(); //デストラクタ
};

}
#endif /*GGAF_DX_CUBEMAPMESHSETACTOR_H_*/
