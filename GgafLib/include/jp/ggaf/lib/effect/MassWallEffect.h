#ifndef GGAF_LIB_MASSWALLEFFECT_H_
#define GGAF_LIB_MASSWALLEFFECT_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/effect/MassMeshEffect.h"

namespace GgafLib {

/**
 * MassWall用エフェクトクラス .
 * @version 1.00
 * @since 2018/04/26
 * @author Masatoshi Tsuge
 */
class MassWallEffect : public GgafDx::MassMeshEffect {
    friend class DefaultEffectManager;
    friend class DefaultModelManager;
public:
    D3DXHANDLE _h_distance_AlphaTarget;
    D3DXHANDLE _h_wall_dep;
    D3DXHANDLE _h_wall_height;
    D3DXHANDLE _h_wall_width;
    D3DXHANDLE _h_ah_POS_ZX;
    D3DXHANDLE _h_fh_POS_ZX;
    D3DXHANDLE _h_ah_POS_YZ;
    D3DXHANDLE _h_fh_POS_YZ;
    D3DXHANDLE _h_ah_POS_XY;
    D3DXHANDLE _h_fh_POS_XY;
    D3DXHANDLE _h_reflectance;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name エフェクト識別名。".fx"を追加するとエフェクトファイル名になる。
     * @return
     */
    MassWallEffect(const char* prm_effect_name);

    virtual ~MassWallEffect();

};

}
#endif /*GGAF_LIB_MASSWALLEFFECT_H_*/
