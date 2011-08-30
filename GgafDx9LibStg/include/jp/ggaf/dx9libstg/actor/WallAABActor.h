#ifndef WALLAABACTOR_H_
#define WALLAABACTOR_H_

namespace GgafDx9LibStg {

/**
 * �O�ǃV�[��(WalledSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WalledSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
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
     * �ǃu���b�N��ݒ肷��
     * @param prm_wall_draw_face �ǃu���b�N�\���ʏ��
     * @param prm_aColliBoxStretch �ǃu���b�N�����蔻����
     */
    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;


    virtual ~WallAABActor();
};

}
#endif /*WALLAABACTOR_H_*/
