#ifndef GGAFDXWORLDEFFECT_H_
#define GGAFDXWORLDEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxWorldBoundModel�p�G�t�F�N�g�N���X.
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

    virtual ~GgafDxWorldBoundEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXWORLDEFFECT_H_*/
