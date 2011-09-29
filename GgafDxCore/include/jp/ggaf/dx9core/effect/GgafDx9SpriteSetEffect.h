#ifndef GGAFDX9SPRITESETEFFECT_H_
#define GGAFDX9SPRITESETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteSet用エフェクトクラス .
 * @version 1.00
 * @since 2009/07/14
 * @author Masatoshi Tsuge
 */
class GgafDx9SpriteSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _ah_matWorld[18];
    D3DXHANDLE _ahOffsetU[18];
    D3DXHANDLE _ahOffsetV[18];
    D3DXHANDLE _ahAlpha[18];

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9SpriteSetEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9EffectManagerである<BR>
     */
    virtual ~GgafDx9SpriteSetEffect(); //デストラクタ

};

}
#endif /*GGAFDX9SPRITESETEFFECT_H_*/
