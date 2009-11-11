#include "GgafCommonHeader.h"
#define DEBUG
using namespace GgafCore;

int main() {
    GgafLinearOctree* pTree =  NEW GgafLinearOctree(5);
    pTree->setRootSpace(-8000 ,-8000 ,-8000 ,8000 ,8000 ,8000);
    GgafLinearOctree::Elem* pElem1 = NEW GgafLinearOctree::Elem(NEW GgafObject(), 1);
    GgafLinearOctree::Elem* pElem2 = NEW GgafLinearOctree::Elem(NEW GgafObject(), 2);
    GgafLinearOctree::Elem* pElem3 = NEW GgafLinearOctree::Elem(NEW GgafObject(), 4);
    pTree->registElem(pElem1, 10 ,10 ,10, 41 ,51 ,61);
    pTree->registElem(pElem2, 7000 ,7000 ,7000, 7999 ,7999 ,7999);
    pTree->registElem(pElem3, 1 ,1 ,1, 1 ,1 ,1);
    _TRACE_("----------------------------------------------------------------������")

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------������")
     pTree->clearElem();

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------������")

    pElem2->extract();

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------������")

    pElem3->extract();

    pTree->putTree();

    _TRACE_("----------------------------------------------------------------������")





}
