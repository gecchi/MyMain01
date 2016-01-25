#ifndef GGAFLIB_WALLAAPYRAMIDACTOR_H_
#define GGAFLIB_WALLAAPYRAMIDACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"

namespace GgafLib {

/**
 * 外壁シーン(WalledSectionScene)の壁ブロック(ピラミッド型)基底クラス .
 * @version 1.00
 * @since 2016/01/20
 * @author Masatoshi Tsuge
 */
class WallAAPyramidActor : public WallPartsActor {

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _h_wall_dep;
    static D3DXHANDLE _h_wall_height;
    static D3DXHANDLE _h_wall_width;
    /** プリズム無条件追加描画不要面テーブル */
    static std::map<int, UINT> _delface;

public:
    WallAAPyramidActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    static bool initStatic(WallAAPyramidActor* prm_pWallAAPyramidActor);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_pyramid, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAAPyramidActor();
};

}
#endif /*GGAFLIB_WALLAAPYRAMIDACTOR_H_*/
