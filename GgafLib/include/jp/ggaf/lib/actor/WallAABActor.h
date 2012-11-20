#ifndef WALLAABACTOR_H_
#define WALLAABACTOR_H_

namespace GgafLib {

/**
 * 外壁シーン(WalledSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WalledSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class WallAABActor : public WallPartsActor {

public:
    D3DXHANDLE _h_distance_AlphaTarget;

    WallAABActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;

    virtual ~WallAABActor();
};

}
#endif /*WALLAABACTOR_H_*/
