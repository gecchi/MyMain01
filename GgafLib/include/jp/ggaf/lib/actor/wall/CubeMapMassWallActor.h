#ifndef GGAF_LIB_CUBEMAPMASSWALLACTOR_H_
#define GGAF_LIB_CUBEMAPMASSWALLACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "MassWallActor.h"
#include "jp/ggaf/dx/actor/interface/ICubeMapActor.h"

namespace GgafLib {

/**
 * 外壁シーン(WallSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WallSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
 * @version 1.00
 * @since 2016/04/04
 * @author Masatoshi Tsuge
 */
class CubeMapMassWallActor : public MassWallActor, public GgafDx::ICubeMapActor {

public:
    CubeMapMassWallActor(const char* prm_name, const char* prm_model);

    virtual void processDraw() override;

    virtual ~CubeMapMassWallActor();
};

}
#endif /*GGAF_LIB_CUBEMAPMASSWALLACTOR_H_*/
