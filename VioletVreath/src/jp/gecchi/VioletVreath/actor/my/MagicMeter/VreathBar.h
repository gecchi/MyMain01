#ifndef VREATHBAR_H_
#define VREATHBAR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

using GgafLib::GraphBarActor;

namespace VioletVreath {

/**
 * VreathBar .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class VreathBar :  public GraphBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    VreathBar(const char* prm_name);

    void initialize() override;

    virtual ~VreathBar();
};

}
#endif /*VREATHBAR_H_*/

