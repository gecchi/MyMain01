#ifndef GGAFDXWORLDBOUNDACTOR_H_
#define GGAFDXWORLDBOUNDACTOR_H_
namespace GgafDxCore {

/**
 * 環境マップ球アクター.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundActor : public GgafDxMorphMeshActor, public GgafDxICubeMapActor {

public:
    /** モデル資源 */
    GgafDxWorldBoundModel* _pWorldBoundModel;
    /** エフェクト資源 */
    GgafDxWorldBoundEffect* _pWorldBoundEffect;

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
    GgafDxWorldBoundActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafCore::GgafStatus* prm_pStat,
                          GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~GgafDxWorldBoundActor (); //デストラクタ
};

}
#endif /*GGAFDXCUBEMAPMORPHMESHACTOR_H_*/
