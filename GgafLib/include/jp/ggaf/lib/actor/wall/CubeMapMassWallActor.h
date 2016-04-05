#ifndef GGAFLIB_CUBEMAPMASSWALLACTOR_H_
#define GGAFLIB_CUBEMAPMASSWALLACTOR_H_
#include "GgafLibCommonHeader.h"
#include "MassWallActor.h"
#include "jp/ggaf/dxcore/actor/interface/GgafDxICubeMapActor.h"

namespace GgafLib {

/**
 * 外壁シーン(WallSectionScene)の壁ブロック基底クラス .
 * 外壁シーン(WallSectionScene)の構成要素の壁ブロックは本クラスを継承する必要がある。
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
