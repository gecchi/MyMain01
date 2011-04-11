#ifndef WALLAAPRISMACTOR_H_
#define WALLAAPRISMACTOR_H_

namespace GgafDx9LibStg {

/**
 * 外壁シーン(WalledSectionScene)の壁ブロック(プリズム型)基底クラス .
 * 外壁シーン(WalledSectionScene)の構成要素の壁ブロック(プリズム型)は本クラスを継承する必要がある。
 * @version 1.00
 * @since 2011/01/09
 * @author Masatoshi Tsuge
 */
class WallAAPrismActor : public WallActor {

public:
    D3DXHANDLE _h_distance_AlphaTarget;
    D3DXHANDLE _h_wall_dep;
    D3DXHANDLE _h_wall_height;
    D3DXHANDLE _h_wall_width;
//    D3DXHANDLE _h_pos_prism;
    static bool init;
    /** プリズム無条件追加描画不要面テーブル */
    static _MAP_<int, UINT> _delface;
//    int _aAddFace[12];


    WallAAPrismActor(const char* prm_name, const char* prm_model);

    virtual void processDraw() override;
    /**
     * 壁ブロックを設定する
     * @param prm_wall_draw_face 壁ブロック表示面情報
     * @param prm_aColliBoxStretch 壁ブロック当たり判定情報
     */
    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAAPrismActor();
};

}
#endif /*WALLAAPRISMACTOR_H_*/
