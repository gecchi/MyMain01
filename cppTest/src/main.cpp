//#include "../../MyStg2nd/src/MyStg2ndHeader.h"
#include "../../GgafCore/include/GgafCommonHeader.h"
using namespace std;

using namespace GgafCore;
//using namespace GgafDx9Core;
//using namespace GgafDx9LibStg;
//using namespace MyStg2nd;


class Base {
public:

};
class Base2 : public Base {
public:
};

class Base3 : public Base2 {
public:
};


class SuperActor {
public:
    virtual void addSub(Base* b) {
        _TRACE_("Super::addSub");
    }

};

class SuperActor2 : public SuperActor {
public:
    void addSub(Base2* b) {
        _TRACE_("Super2::addSub");
    }
};

class SuperActor3 : public SuperActor2 {
public:

};



int main() {

    Base* base = new Base2();
    SuperActor* pSuperActor = new SuperActor3();
    pSuperActor->addSub((Base*)base);

    //super->hoge(((Base* )base));

 }




int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
    return main();
}
