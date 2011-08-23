#ifndef TESTDEPOSITORY_H_
#define TESTDEPOSITORY_H_
namespace MyStg2nd {

class TestDepository : public GgafCore::GgafActorDepository {

public:
    TestDepository(const char* prm_name);

    virtual ~TestDepository() {
        _TRACE_("TestDepository::~TestDepository()");
    }
};

}
#endif /*TESTDEPOSITORY_H_*/
