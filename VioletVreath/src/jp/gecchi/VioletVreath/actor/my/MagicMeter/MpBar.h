#ifndef MPBAR_H_
#define MPBAR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace VioletVreath {

class MpBar : public GgafLib::GraphBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    MpBar(const char* prm_name);

    void initialize() override;

    void addVal(double prm_val);


    virtual ~MpBar();
};

}
#endif /*MPBAR_H_*/

