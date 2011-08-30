#ifndef GGAFDX9SPRITEMESHSETACTOR_H_
#define GGAFDX9SPRITEMESHSETACTOR_H_
namespace GgafDx9Core {

/**
 * スプライトメッシュアクター.
 * GgafDx9MeshSetActor を継承し、
 * さらにUVを切り替える機能を有したアクター
 * メッシュ３Dオブジェクトの表面のテクスチャをアニメーションできます。
 * それのSet版。
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteMeshSetActor : public GgafDx9MeshSetActor {

public:
    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9SpriteMeshSetActor(const char* prm_name,
                              const char* prm_model,
                              GgafCore::GgafStatus* prm_pStat,
                              GgafDx9Checker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDx9SpriteMeshSetActor();

};

}
#endif /*GGAFDX9SPRITEMESHSETACTOR_H_*/
