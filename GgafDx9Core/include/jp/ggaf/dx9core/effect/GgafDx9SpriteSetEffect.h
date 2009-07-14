#ifndef GGAFDX9SPRITESETEFFECT_H_
#define GGAFDX9SPRITESETEFFECT_H_
namespace GgafDx9Core {

/**
 * GgafDx9SpriteSet用モデルクラス.
 */
class GgafDx9SpriteSetEffect : public GgafDx9Effect {
    friend class GgafDx9EffectManager;

public:
    D3DXHANDLE _hMatView;
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
    GgafDx9SpriteSetEffect(char* prm_effect_name);


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9EffectManagerである<BR>
     */
    virtual ~GgafDx9SpriteSetEffect(); //デストラクタ

};

}
#endif /*GGAFDX9SPRITESETEFFECT_H_*/
