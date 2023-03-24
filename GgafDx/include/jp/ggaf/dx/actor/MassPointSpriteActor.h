#ifndef GGAF_DX_MASSPOINTSPRITEACTOR_H_
#define GGAF_DX_MASSPOINTSPRITEACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassPointSpriteModel.h"

namespace GgafDx {

/**
 * TODO:現在使えません。ビデオカード依存が高い為。
 * @version 1.00
 * @since 2016/05/16
 * @author Masatoshi Tsuge
 */
class MassPointSpriteActor : public MassActor {

public:
    /** [r]モデル資源 */
    MassPointSpriteModel* _pMassPointSpriteModel;
    /** [r]エフェクト資源 */
    MassPointSpriteEffect* const _pMassPointSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".psprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    MassPointSpriteActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         CollisionChecker* prm_pChecker );

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
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

    virtual ~MassPointSpriteActor();
};

}
#endif /*GGAF_DX_MASSSPRITEACTOR_H_*/
