//#include "../../MyStg2nd/src/MyStg2ndHeader.h"
#include "../../GgafCore/include/GgafCommonHeader.h"
using namespace std;

using namespace GgafCore;
//using namespace GgafDx9Core;
//using namespace GgafDx9LibStg;
//using namespace MyStg2nd;
class Base4;
class Base5;
class Base6;

class Base {
public:
    virtual void chk(Base* p) {
        logic(p);
    }
    virtual Base* logic(Base* p) = 0;
};
class Base2 : public Base {
public:
    virtual Base* logic(Base* p) {
        _TRACE_("Base2‚Ìlogic");
        return p;
    }
};

class Base3 : public Base2 {
private:
    virtual Base* logic(Base* p) {
        _TRACE_("Base3‚ÌlogicB");
        return p;
    }

};

class Base4 : public Base3 {
private:
    virtual Base* logic(Base* p) {
        _TRACE_("Base4‚Ìlogic");
        return p;
    }
};

class Base5 : public Base4 {
public:
};

class Base6 : public Base5 {
public:
};

int main() {

    Base* pBase = new Base3();
    Base* prm_pB = new Base6();
    pBase->logic(prm_pB);

    //super->hoge(((Base* )base));

 }




int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
    return main();
}
