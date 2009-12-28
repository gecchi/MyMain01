#ifndef TESTDISPATCHER_H_
#define TESTDISPATCHER_H_
namespace MyStg2nd {

class TestDispatcher : public GgafDx9LibStg::ActorDispatcher {

public:
    TestDispatcher(const char* prm_name);

    virtual ~TestDispatcher() {
        _TRACE_("TestDispatcher::~TestDispatcher()")
    }
};

}
#endif /*TESTDISPATCHER_H_*/
