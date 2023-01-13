#ifndef GGAF_DX_CUBEMAPMESHACTOR_H_
#define GGAF_DX_CUBEMAPMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

namespace GgafDx {

/**
 * 環境マップメッシュアクター.
 * 環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class CubeMapMeshActor : public MeshActor, public ICubeMapActor  {

public:
    /** モデル資源 */
    CubeMapMeshModel* _pCubeMapMeshModel;
    /** エフェクト資源 */
    CubeMapMeshEffect* _pCubeMapMeshEffect;

public:
    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名。末尾に ".meshx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     */
    CubeMapMeshActor(const char* prm_name,
                     const char* prm_model,
                     const char* prm_effect_id,
                     const char* prm_technique,
                     CollisionChecker* prm_pChecker );


    virtual void processDraw() override;


    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual ~CubeMapMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_CUBEMAPMESHACTOR_H_*/
