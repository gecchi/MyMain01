#ifndef GGAFLIB_WALLAAPRISMACTOR_H_
#define GGAFLIB_WALLAAPRISMACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"

namespace GgafLib {

/**
 * 外壁シーン(WalledSectionScene)の壁ブロック(プリズム型)基底クラス .
 * 外壁シーン(WalledSectionScene)の構成要素の壁ブロック(プリズム型)は本クラスを継承する必要がある。
 * @version 1.00
 * @since 2011/01/09
 * @author Masatoshi Tsuge
 */
class WallAAPrismActor : public WallPartsActor {

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _h_wall_dep;
    static D3DXHANDLE _h_wall_height;
    static D3DXHANDLE _h_wall_width;
    /** プリズム無条件追加描画不要面テーブル */
    static std::map<int, UINT> _delface;

public:
    WallAAPrismActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    static bool initStatic(WallAAPrismActor* prm_pWallAAPrismActor);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAAPrismActor();
};

}
#endif /*GGAFLIB_WALLAAPRISMACTOR_H_*/
