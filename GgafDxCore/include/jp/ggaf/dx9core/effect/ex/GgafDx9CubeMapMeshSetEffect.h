#ifndef GGAFDX9CUBEMAPMESHSETEFFECT_H_
#define GGAFDX9CUBEMAPMESHSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9CubeMapMeshsModel�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshSetEffect : public GgafDx9MeshSetEffect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_reflectance;
//    D3DXHANDLE _h_pos_camera;

    GgafDx9CubeMapMeshSetEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDx9CubeMapMeshSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
