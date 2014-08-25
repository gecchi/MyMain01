#ifndef TESTCAPPEDBAR_H_
#define TESTCAPPEDBAR_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/CappedGraphBarActor.h"

namespace Mogera {

class TestCappedBar : public GgafLib::CappedGraphBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQty config�ς݂� PxQuantity�I�u�W�F�N�g�̎Q��
     */
    TestCappedBar(const char* prm_name);

    void initialize() override;
    void processBehavior() override;
    void addVal(double prm_val);

    virtual ~TestCappedBar();
};

}
#endif /*TESTCAPPEDBAR_H_*/

