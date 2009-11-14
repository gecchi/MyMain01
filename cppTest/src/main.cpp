#include "GgafCommonHeader.h"
#define DEBUG
using namespace GgafCore;

int main() {
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
