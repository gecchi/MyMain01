#ifndef WALLAAPRISMACTOR_H_
#define WALLAAPRISMACTOR_H_

namespace GgafLib {

/**
 * �O�ǃV�[��(WalledSectionScene)�̕ǃu���b�N(�v���Y���^)���N���X .
 * �O�ǃV�[��(WalledSectionScene)�̍\���v�f�̕ǃu���b�N(�v���Y���^)�͖{�N���X���p������K�v������B
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
    /** �v���Y���������ǉ��`��s�v�ʃe�[�u�� */
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
