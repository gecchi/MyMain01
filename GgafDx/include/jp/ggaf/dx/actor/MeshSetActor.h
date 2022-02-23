#ifndef GGAF_DX_MESHSETACTOR_H_
#define GGAF_DX_MESHSETACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * メッシュアクター.
 * Xファイル定義のメッシュ表示機能を<BR>
 * 追加、さらに同一モデル複数オブジェクトの頂点バッファを持ち、大量表示に最適化したアクターです<BR>
 * @version 1.00
 * @since 2009/06/16
 * @author Masatoshi Tsuge
 */
class MeshSetActor : public FigureActor {

public:
    /** [r]モデル資源 */
    MeshSetModel* const _pMeshSetModel;
    /** [r]エフェクト資源 */
    MeshSetEffect* const _pMeshSetEffect;

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
    MeshSetActor(const char* prm_name,
                       const char* prm_model,
                       const char* prm_effect_id,
                       const char* prm_technique,
                       Checker* prm_pChecker );


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
    MeshSetActor(const char* prm_name,
                 const char* prm_model,
                 const char prm_model_type,
                 const char* prm_effect_id,
                 const char prm_effect_type,
                 const char* prm_technique,
                 Checker* prm_pChecker);

    virtual void processDraw() override;

    virtual ~MeshSetActor(); //デストラクタ
};

}
#endif /*GGAF_DX_MESHSETACTOR_H_*/
