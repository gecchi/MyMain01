#ifndef GGAFDX9WORLDBOUNDACTOR_H_
#define GGAFDX9WORLDBOUNDACTOR_H_
namespace GgafDx9Core {

/**
 * 環境マップモーフメッシュアクター.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9WorldBoundActor : public GgafDx9MorphMeshActor, public GgafDx9ICubeMapActor {
private:

public:
    /** モデル資源 */
    GgafDx9WorldBoundModel* _pWorldBoundModel;
    /** エフェクト資源 */
    GgafDx9WorldBoundEffect* _pWorldBoundEffect;

    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDx9WorldBoundActor(const char* prm_name,
                          const char* prm_model_id,
                          const char* prm_effect_id,
                          const char* prm_technique,
                          GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9WorldBoundActor (); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHACTOR_H_*/
