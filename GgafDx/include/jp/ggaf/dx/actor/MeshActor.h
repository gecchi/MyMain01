#ifndef GGAF_DX_MESHACTOR_H_
#define GGAF_DX_MESHACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IBumpMapActor.h"

namespace GgafDx {

/**
 * メッシュアクター.
 * 独自のXファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class MeshActor : public FigureActor, public IBumpMapActor {

public:
    /** [r]モデル資源 */
    MeshModel* _pMeshModel;
    /** [r]エフェクト資源 */
    MeshEffect* const _pMeshEffect;

    float _far_rate;

    float _lambert_flg;//1.0:Half Lambert/ -1.0:Lambert
public:
    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名。末尾に ".meshx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     */
    MeshActor(const char* prm_name,
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
    MeshActor(const char* prm_name,
              const char* prm_model,
              const char prm_model_type,
              const char* prm_effect_id,
              const char prm_effect_type,
              const char* prm_technique,
              CollisionChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * 遠くの座標でも強制表示 .
     * @param prm_b
     */
    void drawAnyFar(bool prm_b) {
        if (prm_b) {
            _far_rate = 0.999f;
        } else {
            _far_rate = -1.0f;
        }
    }

    void effectBumpMapping(const char* prm_cubemap_tex, frame prm_frame = MAX_FRAME);

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~MeshActor();
};

}
#endif /*GGAF_DX_MESHACTOR_H_*/
