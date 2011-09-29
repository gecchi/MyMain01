#ifndef GGAFDXWORLDEFFECT_H_
#define GGAFDXWORLDEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxWorldBoundModel用エフェクトクラス.
 * @version 1.00
 * @since 2015/05/20
 * @author Masatoshi Tsuge
 */
class GgafDxWorldBoundEffect : public GgafDxMorphMeshEffect {
    friend class GgafDxEffectManager;

public:

//    D3DXHANDLE _h_pos_camera;

    GgafDxWorldBoundEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDxWorldBoundEffect(); //デストラクタ

};

}
#endif /*GGAFDXWORLDEFFECT_H_*/
