#ifndef GGAFDX9SPRITEEFFECT_H_
#define GGAFDX9SPRITEEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9Sprite用モデルクラス.
 */
class GgafDx9SpriteEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatWorld;
    D3DXHANDLE _hOffsetU;
    D3DXHANDLE _hOffsetV;
    D3DXHANDLE _hAlpha;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDx9SpriteEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9SpriteEffectManagerである<BR>
     */
    virtual ~GgafDx9SpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDX9SPRITEEFFECT_H_*/
