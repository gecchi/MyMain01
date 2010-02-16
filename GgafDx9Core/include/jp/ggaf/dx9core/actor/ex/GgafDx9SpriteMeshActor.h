#ifndef GGAFDX9SPRITEMESHACTOR_H_
#define GGAFDX9SPRITEMESHACTOR_H_
namespace GgafDx9Core {

/**
 * スプライトメッシュセットアクター.
 * GgafDx9MeshActor を継承し、
 * UVを切り替える機能を有したアクター
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteMeshActor : public GgafDx9MeshActor {

public:

    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;

    /**
     * コンストラクタ.
     * GgafDx9SpriteMeshSetActor で使用するモデルIDは避けて下さい。
     * @param prm_name
     * @param prm_model
     * @param prm_pChecker
     * @return
     */
    GgafDx9SpriteMeshActor(const char* prm_name,
                           const char* prm_model,
                           GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteMeshActor();
};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
