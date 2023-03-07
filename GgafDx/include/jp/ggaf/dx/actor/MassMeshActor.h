#ifndef GGAF_DX_MASSMESHACTOR_H_
#define GGAF_DX_MASSMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MassActor.h"
#include "jp/ggaf/dx/model/MassMeshModel.h"

namespace GgafDx {

/**
 * メッシュアクター（大量表示用） .
 * Xファイル定義のメッシュ表示機能を<BR>
 * インスタンシングにより、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2016/02/09
 * @author Masatoshi Tsuge
 */
class MassMeshActor : public MassActor {

public:
    /** [r]モデル資源 */
    MassMeshModel* _pMassMeshModel;
    /** [r]エフェクト資源 */
    MassMeshEffect* const _pMassMeshEffect;

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
    MassMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect_id,
                  const char* prm_technique,
                  CollisionChecker* prm_pChecker );


    /**
     * 下位継承用コンストラクタ
     * @param prm_name アクター名称（任意）
     * @param prm_model モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    MassMeshActor(const char* prm_name,
                  const char* prm_model,
                  const char prm_model_type,
                  const char* prm_effect_id,
                  const char prm_effect_type,
                  const char* prm_technique,
                  CollisionChecker* prm_pChecker);

    /**
     * モデル資源(MassMeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~MassMeshActor(); //デストラクタ
};

}
#endif /*GGAF_DX_MASSMESHACTOR_H_*/
