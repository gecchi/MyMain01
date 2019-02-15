#ifndef GGAF_DX_BASEACTOR_H_
#define GGAF_DX_BASEACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace GgafDx {

/**
 * Core名前空間の基底アクタークラス.
 * GgafCore::MainActorを継承しただけです。<BR>
 * Core名前空間内では、このクラスを基底アクターとします。<BR>
 * @version 1.00
 * @since 2009/09/08
 * @author Masatoshi Tsuge
 */
class BaseActor : public GgafCore::MainActor {

public:
    BaseActor(const char* prm_name);

    virtual ~BaseActor(); //デストラクタ

};

}
#endif /*GGAF_DX_BASEACTOR_H_*/
