#ifndef TESTDISPATCHER_H_
#define TESTDISPATCHER_H_
namespace MyStg2nd {

class TestDispatcher : public GgafCore::GgafActorDispatcher {

public:
    TestDispatcher(const char* prm_name);

    virtual ~TestDispatcher() {
        _TRACE_("TestDispatcher::~TestDispatcher()")
    }
};

}
#endif /*TESTDISPATCHER_H_*/
