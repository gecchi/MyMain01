#ifndef TESTSTORE_H_
#define TESTSTORE_H_
namespace MyStg2nd {

class TestStore : public GgafCore::GgafActorStore {

public:
    TestStore(const char* prm_name);

    virtual ~TestStore() {
        _TRACE_("TestStore::~TestStore()");
    }
};

}
#endif /*TESTSTORE_H_*/
