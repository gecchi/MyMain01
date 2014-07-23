#ifndef MPBAR_H_
#define MPBAR_H_
#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"

namespace VioletVreath {

/**
 * MpBar .
 * @version 1.00
 * @since 2013/09/12
 * @author Masatoshi Tsuge
 */
class MpBar : public GgafLib::CappedGraphBarActor {

public:

    MpBar(const char* prm_name);

    void initialize() override;

    void addVal(double prm_val);


    virtual ~MpBar();
};

}
#endif /*MPBAR_H_*/

