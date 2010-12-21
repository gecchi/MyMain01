#ifndef GGAFDX9CUBEMAPMESHEFFECT_H_
#define GGAFDX9CUBEMAPMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9CubeMapMeshModel�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshEffect : public GgafDx9MeshEffect {
    friend class GgafDx9EffectManager;

public:

    D3DXHANDLE _h_pos_camera;

    GgafDx9CubeMapMeshEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    virtual ~GgafDx9CubeMapMeshEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
