#ifndef GGAFDX9WORLDEFFECT_H_
#define GGAFDX9WORLDEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9WorldBoundModel用エフェクトクラス.
 * @version 1.00
 * @since 2015/05/20
 * @author Masatoshi Tsuge
 */
class GgafDx9WorldBoundEffect : public GgafDx9MorphMeshEffect {
    friend class GgafDx9EffectManager;

public:

//    D3DXHANDLE _h_pos_camera;

    GgafDx9WorldBoundEffect(char* prm_effect_name);

//    virtual void setParamPerFrame() override;

    virtual ~GgafDx9WorldBoundEffect(); //デストラクタ

};

}
#endif /*GGAFDX9CUBEMAPMESHEFFECT_H_*/
