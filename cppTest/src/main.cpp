#include "GgafCommonHeader.h"
#define DEBUG


int main() {
    GgafLinearOctree<int>* pTree =
            NEW GgafLinearOctree<int>
                (
                    5,
                    -8000 ,-8000 ,-8000 ,8000 ,8000 ,8000
                );
    int* xxx = NEW int(2);

    GgafLinearOctree<int>::Elem* pElem1 = NEW GgafLinearOctree<int>::Elem(xxx);
    GgafLinearOctree<int>::Elem* pElem2 = NEW GgafLinearOctree<int>::Elem(xxx);
    GgafLinearOctree<int>::Elem* pElem3 = NEW GgafLinearOctree<int>::Elem(xxx);

    pTree->registElem(pElem1, 10 ,10 ,10, 41 ,51 ,61);
    pTree->registElem(pElem2, 7000 ,7000 ,7000, 7999 ,7999 ,7999);
    pTree->registElem(pElem3, 1 ,1 ,1, 1 ,1 ,1);
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pElem2->moveToSpace(pTree->_papSpace[1]);

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pTree->registElem(pElem2, 1000,1000,1000,4000,4000,4000);

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pTree->registElem(pElem2, 1 ,1 ,1, 1 ,1 ,1);

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pElem1->extract();

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pElem2->extract();

    pTree->putTree();
    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")

    pElem3->extract();

    pTree->putTree();

    _TRACE_("----------------------------------------------------------------”ª•ª–Ø")





}
