#ifndef TESTBAR_H_
#define TESTBAR_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/GraphBarActor.h"

namespace Mogera {

class TestBar : public GgafLib::GraphBarActor {

public:


    /**
     *
     * @param prm_name
     * @param prm_pPxQty config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    TestBar(const char* prm_name);

    void initialize() override;
    void processBehavior() override;
    void addVal(double prm_val);

    virtual ~TestBar();
};

}
#endif /*TESTBAR_H_*/

