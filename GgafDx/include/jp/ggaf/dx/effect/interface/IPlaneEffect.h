#ifndef GGAF_DX_IPLANEEFFECT_H_
#define GGAF_DX_IPLANEEFFECT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/effect/Effect.h"

namespace GgafDx {

/**
 * 平面パネル用エフェクトクラス .
 * @version 1.00
 * @since 2023/06/07
 * @author Masatoshi Tsuge
 */
class IPlaneEffect {
    friend class EffectManager;

public:
    D3DXHANDLE _h_dbd_offset_x;
    D3DXHANDLE _h_dbd_offset_y;


    /**
     * コンストラクタ<BR>
     * @return
     */
    IPlaneEffect(Effect* prm_pEffect);

    /**
     * デストラクタ<BR>
     */
    virtual ~IPlaneEffect();

};

}
#endif /*GGAF_DX_IPLANEEFFECT_H_*/
