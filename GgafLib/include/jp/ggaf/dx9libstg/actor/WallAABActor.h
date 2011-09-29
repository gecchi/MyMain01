#ifndef WALLAABACTOR_H_
#define WALLAABACTOR_H_

namespace GgafDx9LibStg {

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

    WallAABActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void processDraw() override;
    /**
     * 壁ブロックを設定する
     * @param prm_wall_draw_face 壁ブロック表示面情報
     * @param prm_aColliBoxStretch 壁ブロック当たり判定情報
     */
    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAABActor();
};

}
#endif /*WALLAABACTOR_H_*/
