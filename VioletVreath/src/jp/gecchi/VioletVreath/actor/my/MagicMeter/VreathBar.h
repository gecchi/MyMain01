#ifndef VREATHBAR_H_
#define VREATHBAR_H_
#include "jp/ggaf/lib/actor/GraphCappedBarActor.h"

namespace VioletVreath {

/**
 * VreathBar .
 * @version 1.00
 * @since 2012/05/11
 * @author Masatoshi Tsuge
 */
class VreathBar : public GgafLib::GraphCappedBarActor {

public:

    VreathBar(const char* prm_name);

    void initialize() override;

    virtual ~VreathBar();
};

}
#endif /*VREATHBAR_H_*/

