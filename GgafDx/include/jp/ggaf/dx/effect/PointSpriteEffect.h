#ifndef GGAF_DX_POINTSPRITEEFFECT_H_
#define GGAF_DX_POINTSPRITEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * PointSprite用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class PointSpriteEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_matWorld;
    D3DXHANDLE _h_colMaterialDiffuse;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;
    D3DXHANDLE _hInvTextureSplitRowcol;
    D3DXHANDLE _hUvFlipPtnNo;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    PointSpriteEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはPointSpriteEffectManagerである<BR>
     */
    virtual ~PointSpriteEffect();

};

}
#endif /*GGAF_DX_POINTSPRITEEFFECT_H_*/
