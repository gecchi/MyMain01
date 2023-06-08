#ifndef GGAF_DX_POINTSPRITESETEFFECT_H_
#define GGAF_DX_POINTSPRITESETEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "World3DimEffect.h"
#include "interface/IPlaneEffect.h"

namespace GgafDx {

/**
 * PointSpriteSet用エフェクトクラス .
 * @version 1.00
 * @since 2016/06/09
 * @author Masatoshi Tsuge
 */
class PointSpriteSetEffect : public World3DimEffect, public IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _ah_matWorld[32];
    D3DXHANDLE _ah_colMaterialDiffuse[32];
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
    PointSpriteSetEffect(const char* prm_effect_name);

    /**
     * デストラクタ<BR>
     * deleteするのはPointSpriteSetEffectManagerである<BR>
     */
    virtual ~PointSpriteSetEffect();

};

}
#endif /*GGAF_DX_POINTSPRITESETEFFECT_H_*/
