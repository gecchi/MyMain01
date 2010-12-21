#ifndef GGAFDX9POINTSPRITEEFFECT_H_
#define GGAFDX9POINTSPRITEEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9PointSprite用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _h_tex_blink_power;
    D3DXHANDLE _h_tex_blink_threshold;
    D3DXHANDLE _h_matView;
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hAlpha;
    D3DXHANDLE _h_dist_VpFrontPlane;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9PointSpriteEffect(char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9PointSpriteEffectManagerである<BR>
     */
    virtual ~GgafDx9PointSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDX9POINTSPRITEEFFECT_H_*/
