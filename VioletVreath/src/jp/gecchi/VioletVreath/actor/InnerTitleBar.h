#ifndef INNERTITLEBAR_H_
#define INNERTITLEBAR_H_
#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"

namespace VioletVreath {


/**
 * åªç›ñ¢égóp .
 */
class InnerTitleBar : public GgafLib::CappedGraphBarActor {

public:
    InnerTitleBar(const char* prm_name);
    void initialize() override;
    void processBehavior() override;
    void addVal(double prm_val);
    virtual ~InnerTitleBar();
};

}
#endif /*INNERTITLEBAR_H_*/

