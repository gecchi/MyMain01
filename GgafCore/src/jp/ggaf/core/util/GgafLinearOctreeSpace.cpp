#include "stdafx.h"
using namespace GgafCore;



void GgafLinearOctreeSpace::dump() {
    if (_pElemFirst == NULL) {
        _TEXT_("x");
    } else {
        GgafLinearOctreeElem* pElem = _pElemFirst;
        while (true) {
            pElem->dump();

            if (pElem == _pElemLast) {
                break;
            }
            pElem = pElem -> _pNext;
        }
    }
}

GgafLinearOctreeSpace::~GgafLinearOctreeSpace() {
}
