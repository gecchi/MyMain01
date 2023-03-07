#ifndef GGAF_DX_MORPHMESHACTOR_H_
#define GGAF_DX_MORPHMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/supporter/Morpher.hpp"
#include "jp/ggaf/dx/actor/supporter/MorpherAssistantA.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace GgafDx {

/**
 * モーフメッシュアクター.
 * Xファイル定義のメッシュ表示機能及び<BR>
 * モーフアニメーション機能を備えたアクター<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MorphMeshActor : public FigureActor {

private:
    /** モーフィング支援オブジェクト */
    Morpher<MorphMeshActor>* const _pMorpher;

public:
    /** [r]モーフターゲット数(モデルのコピーした値) */
    int _morph_target_num;
    /** [r]モデル資源 */
    MorphMeshModel* _pMorphMeshModel;
    /** [r]エフェクト資源 */
    MorphMeshEffect* const _pMorphMeshEffect;
    /** [r/w]モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[MAX_MORPH_TARGET+1]; //[0]は未使用、[1]～[6]がモーフターゲット1～6の重み

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
    MorphMeshActor(const char* prm_name,
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
    MorphMeshActor(const char* prm_name,
                   const char* prm_model,
                   const char prm_model_type,
                   const char* prm_effect_id,
                   const char prm_effect_type,
                   const char* prm_technique,
                   CollisionChecker* prm_pChecker);

    virtual void processDraw() override;

    /**
     * モーフターゲットメッシュ数取得
     * @return モーフターゲットメッシュ数
     */
    int getMorphTergetNum();

    /**
     * モーフターゲットの重みを直接指定 .
     * @param prm_target_mesh_no モーフターゲットメッシュNO(1 ～)
     * @param prm_weight 重み 重み0.0～1.0。それ以上も可能
     */
    void setMorphWeight(int prm_target_mesh_no, float prm_weight);

    /**
     * 全モーフターゲットの重みを直接指定
     * @param prm_target_mesh_no 重み0.0～1.0。それ以上も可能
     */
    void setMorphWeight(float prm_weight);

    float getMorphWeight(int prm_target_mesh_no);

    void addMorphWeight(int prm_target_mesh_no, float prm_add_weight);

    inline Morpher<MorphMeshActor>* getMorpher() {
        return _pMorpher;
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

    virtual ~MorphMeshActor (); //デストラクタ
};

}
#endif /*GGAF_DX_MORPHMESHACTOR_H_*/
