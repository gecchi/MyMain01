#ifndef GGAF_DX_SCENEMEDIATOR_H_
#define GGAF_DX_SCENEMEDIATOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/actor/SceneMediator.h"

namespace GgafDx {

/**
 * SceneMediator
 * @version 1.00
 * @since 2017/12/05
 * @author Masatoshi Tsuge
 */
class SceneMediator : public GgafCore::SceneMediator {

public:
    SceneMediator(Scene* prm_pScene_platform);

    virtual ~SceneMediator(); //�f�X�g���N�^

};

}
#endif /*GGAF_DX_SCENEMEDIATOR_H_*/
