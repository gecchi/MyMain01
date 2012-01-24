#ifndef GGAFDXSPRITEMESHACTOR_H_
#define GGAFDXSPRITEMESHACTOR_H_
namespace GgafDxCore {

/**
 * スプライトメッシュセットアクター.
 * GgafDxMeshActor を継承し、
 * さらにUVを切り替える機能を有したアクター
 * メッシュ３Dオブジェクトの表面のテクスチャをアニメーションできます。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteMeshActor : public GgafDxMeshActor {

public:

    /** UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* _pUvFlipper;

    /**
     * コンストラクタ.
     * GgafDxSpriteMeshSetActor で使用するモデルIDは避けて下さい。
     * @param prm_name
     * @param prm_model
     * @param prm_pStat
     * @param prm_pChecker
     */
    GgafDxSpriteMeshActor(const char* prm_name,
                           const char* prm_model,
                           GgafCore::GgafStatus* prm_pStat,
                           GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteMeshActor();
};

}
#endif /*GGAFDXSPRITEMESHACTOR_H_*/
