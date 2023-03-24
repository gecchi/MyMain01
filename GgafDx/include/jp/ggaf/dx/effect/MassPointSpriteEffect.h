#ifndef GGAF_DX_MASSPOINTSPRITEEFFECT_H_
#define GGAF_DX_MASSPOINTSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/effect/MassEffect.h"

namespace GgafDx {

/**
 * MassPointSpriteEffect用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class MassPointSpriteEffect : public MassEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_matView;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hInvTextureSplitRowcol;
public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassPointSpriteEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはPointSpriteEffectManagerである<BR>
     */
    virtual ~MassPointSpriteEffect();

};

}
#endif /*GGAF_DX_POINTSPRITEEFFECT_H_*/
