#ifndef WALLAABACTOR_H_
#define WALLAABACTOR_H_
#include "jp/ggaf/lib/actor/WallPartsActor.h"

namespace GgafLib {

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
    D3DXHANDLE _ah_wall_draw_face[16];

public:
    WallAABActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_prism, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;

    virtual ~WallAABActor();
};

}
#endif /*WALLAABACTOR_H_*/
