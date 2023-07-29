#ifndef GGAF_DX_SCENECHIEF_H_
#define GGAF_DX_SCENECHIEF_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/actor/SceneChief.h"

namespace GgafDx {

/**
 * SceneChief
 * @version 1.00
 * @since 2017/12/05
 * @author Masatoshi Tsuge
 */
class SceneChief : public GgafCore::SceneChief {

public:
    SceneChief(Scene* prm_pScene_platform);

    virtual ~SceneChief();

};

}
#endif /*GGAF_DX_SCENECHIEF_H_*/
