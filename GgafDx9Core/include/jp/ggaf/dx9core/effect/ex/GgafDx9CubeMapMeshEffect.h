#ifndef GGAFDX9CUBEMAPMESHEFFECT_H_
#define GGAFDX9CUBEMAPMESHEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Mesh用エフェクトクラス.
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9CubeMapMeshEffect : public GgafDx9MeshEffect {
    friend class GgafDx9EffectManager;

public:
    GgafDx9CubeMapMeshEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    virtual ~GgafDx9CubeMapMeshEffect(); //デストラクタ

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
