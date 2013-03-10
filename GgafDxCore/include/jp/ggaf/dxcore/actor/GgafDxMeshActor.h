#ifndef GGAFDXMESHACTOR_H_
#define GGAFDXMESHACTOR_H_
namespace GgafDxCore {

/**
 * メッシュアクター.
 * GgafDxDrawableActor を継承し、独自のXファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです。<BR>
 * @version 1.00
 * @since 2009/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxMeshActor : public GgafDxDrawableActor, public GgafDxIBumpMapActor {

public:
    /** [r]モデル資源 */
    GgafDxMeshModel* _pMeshModel;
    /** [r]エフェクト資源 */
    GgafDxMeshEffect* _pMeshEffect;

    float _far_rate;

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
    GgafDxMeshActor(const char* prm_name,
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
    GgafDxMeshActor(const char* prm_name,
                    const char* prm_model_id,
                    const char* prm_model_type,
                    const char* prm_effect_id,
                    const char* prm_effect_type,
                    const char* prm_technique,
                    GgafCore::GgafStatus* prm_pStat,
                    GgafDxChecker* prm_pChecker);

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

    void effectBumpMapping(const char* prm_cubemap_tex, frame prm_frame = MAX_FRAME);

    virtual ~GgafDxMeshActor(); //デストラクタ
};

}
#endif /*GGAFDXMESHACTOR_H_*/
