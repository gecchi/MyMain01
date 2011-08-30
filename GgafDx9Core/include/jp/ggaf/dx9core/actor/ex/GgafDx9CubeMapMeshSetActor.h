#ifndef GGAFDX9CUBEMAPMESHSETACTOR_H_
#define GGAFDX9CUBEMAPMESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * 環境マップメッシュセットアクター.
 * GgafDx9MeshActor を継承し、環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshSetActor : public GgafDx9MeshSetActor, public GgafDx9ICubeMapActor {

public:

    /** モデル資源 */
    GgafDx9CubeMapMeshSetModel* _pCubeMapMeshSetModel;
    /** エフェクト資源 */
    GgafDx9CubeMapMeshSetEffect* _pCubeMapMeshSetEffect;

    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDx9CubeMapMeshSetActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafCore::GgafStatus* prm_pStat,
                               GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    /**
     * デバイスロスト対応イベント処理 .
     * モデルとは別管理のキューブマップテクスチャの解放と再構築処理を実行します。
     * 下位で onCatchEvent(UINT32, void*) オーバーライドしたい場合は、上位を呼び出して下さい。
     * @param prm_no
     * @param prm_pSource
     */
    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
        if (prm_no == GGAF_EVENT_ON_DEVICE_LOST) {
            releaseCubeMapTex();
        } else if (prm_no == GGAF_EVENT_DEVICE_LOST_REDEPOSITORY) {
            restoreCubeMapTex();
        }
    }
    virtual ~GgafDx9CubeMapMeshSetActor(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMESHSETACTOR_H_*/
