#ifndef GGAFDXCUBEMAPMESHEFFECT_H_
#define GGAFDXCUBEMAPMESHEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxCubeMapMeshModel用エフェクトクラス.
 * @version 1.00
 * @since 2010/12/21
 * @author Masatoshi Tsuge
 */
class GgafDxCubeMapMeshEffect : public GgafDxMeshEffect {
    friend class GgafDxEffectManager;

public:

//    D3DXHANDLE _h_pos_camera;
    D3DXHANDLE _h_reflectance;
    GgafDxCubeMapMeshEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDxCubeMapMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDXCUBEMAPMESHEFFECT_H_*/
