#ifndef GGAF_LIB_POINTERACTOR_H_
#define GGAF_LIB_POINTERACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/Quantity.hpp"

namespace GgafLib {


/**
 * マウスポインタ（作成中） .
 * @version 1.00
 * @since 2022/08/09
 * @author Masatoshi Tsuge
 */
class PointerActor : public DefaultBoardActor {

protected:

    POINT _mouse_point;

public:

    PointerActor(const char* prm_name, const char* prm_model);

    virtual void processSettlementBehavior() override;

    virtual ~PointerActor();
};

}
#endif /*GGAF_LIB_POINTERACTOR_H_*/

