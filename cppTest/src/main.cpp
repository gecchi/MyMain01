#include "GgafCommonHeader.h"
#define DEBUG
using namespace GgafCore;

class MeshSub;
class SpriteSub;
class Status;


class Parent {
public:
    int _p;
    void *pSt;
};
class Parent2  : public Parent  {
public:
};




class Status {
public:
    int _point;
};




class MMM :  public Parent2  {
public:
    int _X;
};
class Mesh : public MMM, public Status {
public:
    int _m;
    virtual Status* getSub() {
        return this;
    }

};
class MeshSub : public Mesh {
public:
    int _v;

};

class SSS : public Parent2  {
public:
    int _X;
};
class Sprite : public SSS,  public Status {
public:
    int _s;
};
class SpriteSub : public Sprite {
public:
    int _a;

};



void putPoint(Parent2* p) {
    Status* s = (Status*)(p->pSt);
    _TRACE_("Status="<<(s->_point));

}

int main() {

    class Z {
    public:
        static void xx() {
        }
    };

    SpriteSub* sprite_sub  = new SpriteSub();
    MeshSub* mesh_sub  = new MeshSub();

    sprite_sub -> _point = 100;
    mesh_sub -> _point = 500;

    sprite_sub->pSt = (Status*)sprite_sub;
    mesh_sub->pSt = (Status*)mesh_sub;

    Parent2* pA = (Parent2*)sprite_sub;
    Parent2* pB = (Parent2*)mesh_sub;

//    Status* statusA;
//    Status* statusB;
//
//    statusA = (Status*)sprite_sub;
//    statusB = (Status*)mesh_sub;

    putPoint(pA);
    putPoint(pB);

//    delete statusA;
//    delete statusB;
}





int main_old() {
    GgafLinearOctree* pTree =  NEW GgafLinearOctree(0);
    pTree->setRootSpace(-8000 ,-8000 ,-8000 ,8000 ,8000 ,8000);
    GgafLinearOctreeElem* pElem1 = NEW GgafLinearOctreeElem(NEW GgafObject(), 1);
    GgafLinearOctreeElem* pElem2 = NEW GgafLinearOctreeElem(NEW GgafObject(), 2);
    GgafLinearOctreeElem* pElem3 = NEW GgafLinearOctreeElem(NEW GgafObject(), 4);
    //pTree->registElem(pElem1, 10 ,10 ,10, 41 ,51 ,61);
    pTree->registElem(pElem2, -7999 ,-7999 ,-7999, -7000 ,-7000 ,-7000);
    pTree->registElem(pElem3, 5000 ,-7000 ,3000, 5000 ,-7000 ,3000);
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")
     pTree->clearElem();

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pTree->registElem(pElem2, -7999 ,-7999 ,-7999, -7000 ,-7000 ,-7000);
    pTree->registElem(pElem3, 5000 ,-7000 ,3000, 5000 ,-7000 ,3000);

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pElem3->extract();

    pTree->putTree();

    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")





}
int APIENTRY _tWinMain(HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPTSTR lpCmdLine,
        int nCmdShow)
{
    return main();
}
