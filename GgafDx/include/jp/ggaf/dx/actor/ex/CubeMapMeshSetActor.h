#ifndef GGAF_DX_CUBEMAPMESHSETACTOR_H_
#define GGAF_DX_CUBEMAPMESHSETACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
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
     * @param prm_pColliChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    CubeMapMeshSetActor(const char* prm_name,
                        const char* prm_model,
                        const char* prm_effect_id,
                        const char* prm_technique);
     
    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
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

    virtual ~CubeMapMeshSetActor();
};

}
#endif /*GGAF_DX_CUBEMAPMESHSETACTOR_H_*/
