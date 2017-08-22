#ifndef GGAFDXCORE_GGAFDXMASSPOINTSPRITEEFFECT_H_
#define GGAFDXCORE_GGAFDXMASSPOINTSPRITEEFFECT_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dxcore/effect/GgafDxMassEffect.h"

namespace GgafDxCore {

/**
 * GgafDxMassPointSpriteEffect用エフェクトクラス .
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDxMassPointSpriteEffect : public GgafDxMassEffect {
    friend class GgafDxEffectManager;

public:
    D3DXHANDLE _h_matView;
    D3DXHANDLE _hTexSize;
    D3DXHANDLE _hTextureSplitRowcol;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    GgafDxMassPointSpriteEffect(const char* prm_effect_name);


    virtual void setParamPerFrame() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxPointSpriteEffectManagerである<BR>
     */
    virtual ~GgafDxMassPointSpriteEffect(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXPOINTSPRITEEFFECT_H_*/
