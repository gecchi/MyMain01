#ifndef MPBAR_H_
#define MPBAR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace VioletVreath {

class MpBar : public GgafLib::GraphBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    MpBar(const char* prm_name);

    void initialize() override;

    void addVal(double prm_val);


    virtual ~MpBar();
};

}
#endif /*MPBAR_H_*/

