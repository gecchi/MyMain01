#include "jp/ggaf/core/util/GgafLinearOctreeOctant.h"

#include "jp/ggaf/core/util/GgafLinearOctreeElem.h"

using namespace GgafCore;

void GgafLinearOctreeOctant::dump() {
    if (_pElem_first == nullptr) {
        _TRACE_N_("x");
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

GgafLinearOctreeOctant::~GgafLinearOctreeOctant() {
}
