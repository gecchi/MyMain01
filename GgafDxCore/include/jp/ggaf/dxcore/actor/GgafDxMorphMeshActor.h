#ifndef GGAFDXCORE_GGAFDXMORPHMESHACTOR_H_
#define GGAFDXCORE_GGAFDXMORPHMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxDrawableActor.h"

namespace GgafDxCore {

/**
 * モーフメッシュアクター.
 * GgafDxDrawableActor を継承し、Xファイル定義のメッシュ表示機能及び<BR>
 * モーフアニメーション機能を備えたアクター<BR>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class GgafDxMorphMeshActor : public GgafDxDrawableActor {

private:
    /** モーフィング支援オブジェクト */
    GgafDxMorpher* const _pMorpher;

public:

    int _morph_target_num;
    /** [r]モデル資源 */
    GgafDxMorphMeshModel* const _pMorphMeshModel;
    /** [r]エフェクト資源 */
    GgafDxMorphMeshEffect* const _pMorphMeshEffect;
    /** [r/w]モーフターゲットの重み(0.0 ～ 1.0) */
    float _weight[MAX_MORPH_TARGET+1]; //[0]は未使用、[1]～[6]がモーフターゲット1～6の重み

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
    GgafDxMorphMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker );

    /**
     * 下位継承用コンストラクタ
     * @param prm_name アクター名称（任意）
     * @param prm_model_id モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     * @return
     */
    GgafDxMorphMeshActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

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

    /**
     * α設定.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;

    inline GgafDxMorpher* getMorpher() {
        return _pMorpher;
    }

    virtual ~GgafDxMorphMeshActor (); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMORPHMESHACTOR_H_*/
