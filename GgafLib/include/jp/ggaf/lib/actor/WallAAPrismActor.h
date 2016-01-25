#ifndef GGAFLIB_WALLAAPRISMACTOR_H_
#define GGAFLIB_WALLAAPRISMACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"

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
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _h_wall_dep;
    static D3DXHANDLE _h_wall_height;
    static D3DXHANDLE _h_wall_width;
    /** �v���Y���������ǉ��`��s�v�ʃe�[�u�� */
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
