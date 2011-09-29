#ifndef GGAFDXCUBEMAPMESHSETEFFECT_H_
#define GGAFDXCUBEMAPMESHSETEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxCubeMapMeshsModel�p�G�t�F�N�g�N���X.
 * @version 1.00
 * @since 2010/12/24
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshSetEffect : public GgafDxMeshSetEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_reflectance;
//    D3DXHANDLE _h_pos_camera;

    GgafDxCubeMapMeshSetEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDxCubeMapMeshSetEffect(); //�f�X�g���N�^

};

}
#endif /*GGAFDXCUBEMAPMESHEFFECT_H_*/
