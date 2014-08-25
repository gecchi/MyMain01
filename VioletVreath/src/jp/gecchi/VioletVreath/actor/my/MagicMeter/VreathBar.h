#ifndef VREATHBAR_H_
#define VREATHBAR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"

namespace VioletVreath {

/**
 * VreathBar .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class VreathBar : public GgafLib::CappedGraphBarActor {

public:

    VreathBar(const char* prm_name);

    void initialize() override;

    virtual ~VreathBar();
};

}
#endif /*VREATHBAR_H_*/

