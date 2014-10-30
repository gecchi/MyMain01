#include "jp/ggaf/core/util/GgafLinearOctreeSpace.h"

#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

using namespace GgafCore;

void GgafLinearOctreeSpace::dump() {
    if (_pElem_first == nullptr) {
        _DTEXT_("x");
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
