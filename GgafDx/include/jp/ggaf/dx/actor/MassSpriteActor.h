#ifndef GGAF_DX_MASSSPRITEACTOR_H_
#define GGAF_DX_MASSSPRITEACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassSpriteModel.h"

namespace GgafDx {

/**
 * スプライトセットアクター（大量表示用） .
 * 板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、複数同時描画に最適化されたアクターです。<BR>
 * setMaterialColor() による個別色指定はできません(セットしても効果がありません)<BR>
 * @version 1.00
 * @since 2016/02/25
 * @author Masatoshi Tsuge
 */
class MassSpriteActor : public MassActor {

public:
    /** [r]モデル資源 */
    MassSpriteModel* _pMassSpriteModel;
    /** [r]エフェクト資源 */
    MassSpriteEffect* const _pMassSpriteEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".sprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    MassSpriteActor(const char* prm_name,
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

    virtual ~MassSpriteActor();
};

}
#endif /*GGAF_DX_MASSSPRITEACTOR_H_*/
