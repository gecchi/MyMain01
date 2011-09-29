#ifndef GGAFDXCUBEMAPMORPHMESHEFFECT_H_
#define GGAFDXCUBEMAPMORPHMESHEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxCubeMapMorphMeshModel�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMorphMeshEffect : public GgafDxMorphMeshEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_reflectance;
//    D3DXHANDLE _h_pos_camera;

    GgafDxCubeMapMorphMeshEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDxCubeMapMorphMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCUBEMAPMESHEFFECT_H_*/
