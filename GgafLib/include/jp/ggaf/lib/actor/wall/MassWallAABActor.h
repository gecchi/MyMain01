#ifndef GGAFLIB_WALLAABACTOR_H_
#define GGAFLIB_WALLAABACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/wall/MassWallActor.h"

namespace GgafLib {

/**
 * �O�ǃV�[��(WalledSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WalledSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
 * @version 1.00
 * @since 2010/10/18
 * @author Masatoshi Tsuge
 */
class MassWallAABActor : public MassWallActor {

public:
    static D3DXHANDLE _h_distance_AlphaTarget;
    static D3DXHANDLE _ah_wall_draw_face[16];

public:
    MassWallAABActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    static bool initStatic(MassWallAABActor* prm_pMassWallAABActor);

    virtual void processDraw() override;

    virtual void config(WalledSectionScene* prm_pWalledSectionScene,
                        int prm_pos_info, int prm_wall_draw_face, int* prm_aColliBoxStretch) override;

    virtual ~MassWallAABActor();
};

}
#endif /*GGAFLIB_WALLAABACTOR_H_*/
