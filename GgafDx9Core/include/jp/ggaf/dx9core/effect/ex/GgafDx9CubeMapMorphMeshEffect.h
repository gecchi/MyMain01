#ifndef GGAFDX9CUBEMAPMORPHMESHEFFECT_H_
#define GGAFDX9CUBEMAPMORPHMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9CubeMapMorphMeshModel�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMorphMeshEffect : public GgafDx9MorphMeshEffect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_reflectance;
//    D3DXHANDLE _h_pos_camera;

    GgafDx9CubeMapMorphMeshEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDx9CubeMapMorphMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
