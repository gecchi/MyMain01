#ifndef GGAFDX9CUBEMAPMORPHMESHACTOR_H_
#define GGAFDX9CUBEMAPMORPHMESHACTOR_H_
namespace GgafDx9Core {

/**
 * 環境マップモーフメッシュアクター.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMorphMeshActor : public GgafDx9MorphMeshActor, public GgafDx9ICubeMapActor {
private:

public:
    /** モデル資源 */
    GgafDx9CubeMapMorphMeshModel* _pCubeMapMorphMeshModel;
    /** エフェクト資源 */
    GgafDx9CubeMapMorphMeshEffect* _pCubeMapMorphMeshEffect;

    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model_id モデル定義名、末尾に ".x" をつけてXファイル名になること。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     * @return
     */
    GgafDx9CubeMapMorphMeshActor(const char* prm_name,
                                 const char* prm_model_id,
                                 const char* prm_effect_id,
                                 const char* prm_technique,
                                 GgafCore::GgafStatus* prm_pStat,
                                 GgafDx9Checker* prm_pChecker );


    virtual void processDraw() override;

//    virtual void end(frame prm_offset_frames = 1) override；

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

    virtual ~GgafDx9CubeMapMorphMeshActor (); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMORPHMESHACTOR_H_*/
