#ifndef GGAF_DX_WORLDBOUNDACTOR_H_
#define GGAF_DX_WORLDBOUNDACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MorphMeshActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"


namespace GgafDx {

/**
 * 環境マップ球アクター.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class WorldBoundActor : public MorphMeshActor, public ICubeMapActor {

public:
    /** モデル資源 */
    WorldBoundModel* _pWorldBoundModel;
    /** エフェクト資源 */
    WorldBoundEffect* _pWorldBoundEffect;

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
    WorldBoundActor(const char* prm_name,
                    const char* prm_model,
                    const char* prm_effect_id,
                    const char* prm_technique,
                    CollisionChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~WorldBoundActor (); //デストラクタ
};

}
#endif /*GGAF_DX_CUBEMAPMORPHMESHACTOR_H_*/
