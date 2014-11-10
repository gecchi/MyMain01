#ifndef TESTDEPOSITORY_H_
#define TESTDEPOSITORY_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"

namespace VioletVreath {

class TestDepository : public GgafCore::GgafActorDepository {

public:
    TestDepository(const char* prm_name, GgafCore::GgafStatus* prm_pStat);

    virtual ~TestDepository() {
        _TRACE_("TestDepository::~TestDepository()");
    }
};

}
#endif /*TESTDEPOSITORY_H_*/
