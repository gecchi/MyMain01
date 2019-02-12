#ifndef GGAF_LIB_CUBEMAPMASSWALLACTOR_H_
#define GGAF_LIB_CUBEMAPMASSWALLACTOR_H_
#include "GgafLibCommonHeader.h"
#include "MassWallActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

namespace GgafLib {

/**
 * �O�ǃV�[��(WallSectionScene)�̕ǃu���b�N���N���X .
 * �O�ǃV�[��(WallSectionScene)�̍\���v�f�̕ǃu���b�N�͖{�N���X���p������K�v������B
 * @version 1.00
 * @since 2016/04/04
 * @author Masatoshi Tsuge
 */
class CubeMapMassWallActor : public MassWallActor, public GgafDx::ICubeMapActor {

public:
    CubeMapMassWallActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat=nullptr);

    virtual void processDraw() override;

    virtual ~CubeMapMassWallActor();
};

}
#endif /*GGAF_LIB_CUBEMAPMASSWALLACTOR_H_*/
