#ifndef TESTDEPOSITORY_H_
#define TESTDEPOSITORY_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/actor/ex/ActorDepository.h"

namespace VioletVreath {

class TestDepository : public GgafCore::ActorDepository {

public:
    TestDepository(const char* prm_name);

    virtual ~TestDepository() {
        _TRACE_("TestDepository::~TestDepository()");
    }
};

}
#endif /*TESTDEPOSITORY_H_*/
