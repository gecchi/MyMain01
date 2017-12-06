#ifndef GGAFDXCORE_GGAFDXSCENEMEDIATOR_H_
#define GGAFDXCORE_GGAFDXSCENEMEDIATOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/actor/GgafSceneMediator.h"

namespace GgafDxCore {

/**
 * GgafDxSceneMediator
 * @version 1.00
 * @since 2017/12/05
 * @author Masatoshi Tsuge
 */
class GgafDxSceneMediator : public GgafCore::GgafSceneMediator {

public:
    GgafDxSceneMediator(GgafDxScene* prm_pScene_platform);

    virtual ~GgafDxSceneMediator(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXSCENEMEDIATOR_H_*/
