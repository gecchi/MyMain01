#ifndef WALLAAPRISMACTOR_H_
#define WALLAAPRISMACTOR_H_

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
    D3DXHANDLE _h_distance_AlphaTarget;
    D3DXHANDLE _h_wall_dep;
    D3DXHANDLE _h_wall_height;
    D3DXHANDLE _h_wall_width;
    static bool _init;
    /** プリズム無条件追加描画不要面テーブル */
    static std::map<int, UINT> _delface;

public:
    WallAAPrismActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAAPrismActor();
};

}
#endif /*WALLAAPRISMACTOR_H_*/
