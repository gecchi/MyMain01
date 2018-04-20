#ifndef GGAFLIB_WALLAABACTOR_H_
#define GGAFLIB_WALLAABACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"

namespace GgafLib {

/**
 * ＜削除予定＞
 * 外壁シーン(WalledSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WalledSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WallAABActor : public WallPartsActor {

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _ah_wall_draw_face[16];

public:
    WallAABActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    static bool initStatic(WallAABActor* prm_pWallAABActor);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        pos_t prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;

    virtual ~WallAABActor();
};

}
#endif /*GGAFLIB_WALLAABACTOR_H_*/
