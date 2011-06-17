#ifndef GGAFDX9CUBEMAPMESHACTOR_H_
#define GGAFDX9CUBEMAPMESHACTOR_H_
namespace GgafDx9Core {

/**
 * 環境マップメッシュアクター.
 * GgafDx9MeshActor を継承し、環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshActor : public GgafDx9MeshActor, public GgafDx9ICubeMapActor  {

public:

    /** モデル資源 */
    GgafDx9CubeMapMeshModel* _pCubeMapMeshModel;
    /** エフェクト資源 */
    GgafDx9CubeMapMeshEffect* _pCubeMapMeshEffect;

    /**
     * コンストラクタ
     * @param prm_name モデル名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名。末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDx9CubeMapMeshActor(const char* prm_name,
                       const char* prm_model_id,
                       const char* prm_effect_id,
                       const char* prm_technique,
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
        } else if (prm_no == GGAF_EVENT_DEVICE_LOST_RESTORE) {
            restoreCubeMapTex();
        }
    }

    virtual ~GgafDx9CubeMapMeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMESHACTOR_H_*/
