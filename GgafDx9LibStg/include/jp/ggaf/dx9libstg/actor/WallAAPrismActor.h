#ifndef WALLAAPRISMACTOR_H_
#define WALLAAPRISMACTOR_H_

namespace GgafDx9LibStg {

/**
 * �O�ǃV�[��(WalledSectionScene)�̕ǃu���b�N(�v���Y���^)���N���X .
 * �O�ǃV�[��(WalledSectionScene)�̍\���v�f�̕ǃu���b�N(�v���Y���^)�͖{�N���X���p������K�v������B
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
    /** �v���Y���������ǉ��`��s�v�ʃe�[�u�� */
    static _MAP_<int, UINT> _delface;
//    int _aAddFace[12];


    WallAAPrismActor(const char* prm_name, const char* prm_model);

    virtual void processDraw() override;
    /**
     * �ǃu���b�N��ݒ肷��
     * @param prm_wall_draw_face �ǃu���b�N�\���ʏ��
     * @param prm_aColliBoxStretch �ǃu���b�N�����蔻����
     */
    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAAPrismActor();
};

}
#endif /*WALLAAPRISMACTOR_H_*/
