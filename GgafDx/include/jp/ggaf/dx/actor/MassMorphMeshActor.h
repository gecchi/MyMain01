#ifndef GGAF_DX_MASSMORPHMESHACTOR_H_
#define GGAF_DX_MASSMORPHMESHACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/Morpher.hpp"
#include "jp/ggaf/dx/actor/supporter/MorpherAssistantA.hpp"
#include "jp/ggaf/dx/model/MassMeshModel.h"

#define MAX_MASS_MORPH_TARGET_NUM 4

namespace GgafDx {

/**
 * モーフメッシュアクター.
 * Xファイル定義のメッシュ表示機能及び<BR>
 * モーフアニメーション機能を備えたアクター<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class MassMorphMeshActor : public FigureActor {

private:
    /** モーフィング支援オブジェクト */
    Morpher<MassMorphMeshActor>* const _pMorpher;

public:
    /** [r]モーフターゲット数(モデルのコピーした値) */
    int _morph_target_num;
    /** [r]モデル資源 */
    MassMorphMeshModel* _pMassMorphMeshModel;
    /** [r]エフェクト資源 */
    MassMorphMeshEffect* const _pMassMorphMeshEffect;
    /** [r/w]モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[MAX_MASS_MORPH_TARGET_NUM+1]; //[0]は未使用、[1]～[MAX_MASS_MORPH_TARGET_NUM]がモーフターゲットの重み

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
    MassMorphMeshActor(const char* prm_name,
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
    MassMorphMeshActor(const char* prm_name,
                       const char* prm_model,
                       const char prm_model_type,
                       const char* prm_effect_id,
                       const char prm_effect_type,
                       const char* prm_technique,
                       CollisionChecker* prm_pChecker);

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

    inline Morpher<MassMorphMeshActor>* getMorpher() {
        return _pMorpher;
    }

    /**
     * エフェクトのテクニックの変更 .
     * 引数のテクニック名末尾にターゲット数を付与して設定します。
     * @param prm_technique テクニック名
     */
    virtual void changeEffectTechnique(const char* prm_technique) override;

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModel(int prm_model_index) override;

    virtual ~MassMorphMeshActor (); //デストラクタ
};

}
#endif /*GGAF_DX_MASSMORPHMESHACTOR_H_*/
