#ifndef GGAFDXSPRITEEFFECT_H_
#define GGAFDXSPRITEEFFECT_H_
namespace GgafDxCore {

/**
 * GgafDxSprite用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteEffect : public GgafDxEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_offset_u;
    D3DXHANDLE _h_offset_v;
    D3DXHANDLE _h_alpha;
    D3DXHANDLE _h_far_rate;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxSpriteEffect(char* prm_effect_name);

    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxSpriteEffectManagerである<BR>
     */
    virtual ~GgafDxSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDXSPRITEEFFECT_H_*/
