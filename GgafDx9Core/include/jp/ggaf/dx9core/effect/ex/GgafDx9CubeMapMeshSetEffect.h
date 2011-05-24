#ifndef GGAFDX9CUBEMAPMESHSETEFFECT_H_
#define GGAFDX9CUBEMAPMESHSETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9CubeMapMeshsModel用エフェクトクラス.
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

    virtual ~GgafDx9CubeMapMeshSetEffect(); //デストラクタ

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
