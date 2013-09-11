#ifndef TESTBAR_H_
#define TESTBAR_H_
#include "jp/ggaf/lib/actor/GraphBarActor.h"

using GgafLib::GraphBarActor;

namespace Mogera {

class TestBar : public GraphBarActor {

public:
    /**
     *
     * @param prm_name
     * @param prm_pAmount config�ς݂� AmountGraph�I�u�W�F�N�g�̎Q��
     */
    TestBar(const char* prm_name, GgafLib::AmountGraph* prm_pAmount);

    void initialize() override;

    void addVal(double prm_val);


    virtual ~TestBar();
};

}
#endif /*TESTBAR_H_*/

