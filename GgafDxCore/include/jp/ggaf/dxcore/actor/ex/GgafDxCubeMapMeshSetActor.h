#ifndef GGAFDXCUBEMAPMESHSETACTOR_H_
#define GGAFDXCUBEMAPMESHSETACTOR_H_
namespace GgafDxCore {

/**
 * 環境マップメッシュセットアクター.
 * GgafDxMeshActor を継承し、環境マップテクスチャを実装したアクターです。<BR>
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshSetActor : public GgafDxMeshSetActor, public GgafDxICubeMapActor {

public:

    /** モデル資源 */
    GgafDxCubeMapMeshSetModel* _pCubeMapMeshSetModel;
    /** エフェクト資源 */
    GgafDxCubeMapMeshSetEffect* _pCubeMapMeshSetEffect;

    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDxCubeMapMeshSetActor(const char* prm_name,
                               const char* prm_model_id,
                               const char* prm_effect_id,
                               const char* prm_technique,
                               GgafCore::GgafStatus* prm_pStat,
                               GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }
//    /**
//     * デバイスロスト対応イベント処理 .
//     * モデルとは別管理のキューブマップテクスチャの解放と再構築処理を実行します。
//     * 下位で onCatchEvent(UINT32, void*) オーバーライドしたい場合は、上位を呼び出して下さい。
//     * @param prm_no
//     * @param prm_pSource
//     */
//    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
//        if (prm_no == GGAF_EVENT_ON_DEVICE_LOST) {
//            _TRACE_("GgafDxCubeMapMeshSetActor::onCatchEvent "<<getName()<<" GGAF_EVENT_ON_DEVICE_LOST キャッチ");
//            releaseCubeMapTex();
//        } else if (prm_no == GGAF_EVENT_DEVICE_LOST_REDEPOSITORY) {
//            restoreCubeMapTex();
//        }
//    }
    virtual ~GgafDxCubeMapMeshSetActor(); //デストラクタ
};

}
#endif /*GGAFDXCUBEMAPMESHSETACTOR_H_*/
