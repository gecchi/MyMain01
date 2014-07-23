#ifndef INNERTITLEBAR_H_
#define INNERTITLEBAR_H_
#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"

namespace VioletVreath {

class InnerTitleBar : public GgafLib::CappedGraphBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQty config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    InnerTitleBar(const char* prm_name);

    void initialize() override;
    void processBehavior() override;
    void addVal(double prm_val);

    virtual ~InnerTitleBar();
};

}
#endif /*INNERTITLEBAR_H_*/

