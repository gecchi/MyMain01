#ifndef GGAFDXCUBEMAPMESHSETEFFECT_H_
#define GGAFDXCUBEMAPMESHSETEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxCubeMapMeshsModel用エフェクトクラス.
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

    virtual ~GgafDxCubeMapMeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDXCUBEMAPMESHEFFECT_H_*/
