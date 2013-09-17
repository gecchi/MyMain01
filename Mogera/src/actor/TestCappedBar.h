#ifndef TESTCAPPEDBAR_H_
#define TESTCAPPEDBAR_H_
#include "jp/ggaf/lib/actor/GraphCappedBarActor.h"

namespace Mogera {

class TestCappedBar : public GgafLib::GraphCappedBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    TestCappedBar(const char* prm_name);

    void initialize() override;
    void processBehavior() override;
    void addVal(double prm_val);

    virtual ~TestCappedBar();
};

}
#endif /*TESTCAPPEDBAR_H_*/

