#ifndef GGAFDX9CUBEMAPMORPHMESHEFFECT_H_
#define GGAFDX9CUBEMAPMORPHMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9CubeMapMorphMeshModel用エフェクトクラス.
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

    virtual ~GgafDx9CubeMapMorphMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
