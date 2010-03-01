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
    D3DXHANDLE _hPowerBlink;
    D3DXHANDLE _hBlinkThreshold;
    D3DXHANDLE _hMatView;
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hAlpha;
    D3DXHANDLE _hDist_VpPlnFront;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9PointSpriteEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9PointSpriteEffectManagerである<BR>
     */
    virtual ~GgafDx9PointSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDX9POINTSPRITEEFFECT_H_*/
