#ifndef MPBAR_H_
#define MPBAR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FramedHorizontalBarActor.h"

namespace VioletVreath {

/**
 * MpBar .
 * @version 1.00
 * @since 2013/09/12
 * @author Masatoshi Tsuge
 */
class MpBar : public GgafLib::FramedHorizontalBarActor {

public:

    MpBar(const char* prm_name);

    void initialize() override;

    virtual ~MpBar();
};

}
#endif /*MPBAR_H_*/

