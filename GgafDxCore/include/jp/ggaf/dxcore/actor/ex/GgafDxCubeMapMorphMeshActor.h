#ifndef GGAFDXCUBEMAPMORPHMESHACTOR_H_
#define GGAFDXCUBEMAPMORPHMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

namespace GgafDxCore {

/**
 * 環境マップモーフメッシュアクター.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMorphMeshActor : public GgafDxMorphMeshActor, public GgafDxICubeMapActor {

public:
    /** モデル資源 */
    GgafDxCubeMapMorphMeshModel* _pCubeMapMorphMeshModel;
    /** エフェクト資源 */
    GgafDxCubeMapMorphMeshEffect* _pCubeMapMorphMeshEffect;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxCubeMapMorphMeshActor(const char* prm_name,
                                const char* prm_model_id,
                                const char* prm_effect_id,
                                const char* prm_technique,
                                GgafCore::GgafStatus* prm_pStat,
                                GgafDxChecker* prm_pChecker );


    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~GgafDxCubeMapMorphMeshActor (); //デストラクタ
};

}
#endif /*GGAFDXCUBEMAPMORPHMESHACTOR_H_*/
