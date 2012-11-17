#include "stdafx.h"
using namespace GgafCore;



void GgafLinearOctreeSpace::dump() {
    if (_pElem_first == NULL) {
        _TEXT_("x");
    } else {
        GgafLinearOctreeElem* pElem = _pElem_first;
        while (true) {
            pElem->dump();

            if (pElem == _pElem_last) {
                break;
            }
            pElem = pElem -> _pNext;
        }
    }
}

GgafLinearOctreeSpace::~GgafLinearOctreeSpace() {
}
