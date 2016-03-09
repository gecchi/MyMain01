#ifndef GGAFLIB_WALLAABACTOR_H_
#define GGAFLIB_WALLAABACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

namespace GgafLib {

/**
 * 外壁シーン(WalledSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WalledSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class MassWallAABActor : public MassWallActor {

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _ah_wall_draw_face[16];

public:
    MassWallAABActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    static bool initStatic(MassWallAABActor* prm_pMassWallAABActor);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;

    virtual ~MassWallAABActor();
};

}
#endif /*GGAFLIB_WALLAABACTOR_H_*/
