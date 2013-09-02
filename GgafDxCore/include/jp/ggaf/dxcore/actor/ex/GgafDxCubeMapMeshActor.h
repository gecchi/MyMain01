#ifndef GGAFDXCORE_GGAFDXCUBEMAPMESHACTOR_H_
#define GGAFDXCORE_GGAFDXCUBEMAPMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"
#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

namespace GgafDxCore {

/**
 * 環境マップメッシュアクター.
 * GgafDxMeshActor を継承し、環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshActor : public GgafDxMeshActor, public GgafDxICubeMapActor  {

public:
    /** モデル資源 */
    GgafDxCubeMapMeshModel* _pCubeMapMeshModel;
    /** エフェクト資源 */
    GgafDxCubeMapMeshEffect* _pCubeMapMeshEffect;

public:
    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     */
    GgafDxCubeMapMeshActor(const char* prm_name,
                            const char* prm_model_id,
                            const char* prm_effect_id,
                            const char* prm_technique,
                            GgafCore::GgafStatus* prm_pStat,
                            GgafDxChecker* prm_pChecker );


    virtual void processDraw() override;


    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~GgafDxCubeMapMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXCUBEMAPMESHACTOR_H_*/
