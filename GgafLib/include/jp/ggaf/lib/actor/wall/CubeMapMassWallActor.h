#ifndef GGAFLIB_CUBEMAPMASSWALLACTOR_H_
#define GGAFLIB_CUBEMAPMASSWALLACTOR_H_
#include "GgafLibCommonHeader.h"
#include "MassWallActor.h"
#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

namespace GgafLib {

/**
 * �O�ǃV�[��(WallSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WallSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
 * @version 1.00
 * @since 2016/04/04
 * @author Masatoshi Tsuge
 */
class CubeMapMassWallActor : public MassWallActor, public GgafDxCore::GgafDxICubeMapActor {

public:
    CubeMapMassWallActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void processDraw() override;

    virtual ~CubeMapMassWallActor();
};

}
#endif /*GGAFLIB_CUBEMAPMASSWALLACTOR_H_*/
