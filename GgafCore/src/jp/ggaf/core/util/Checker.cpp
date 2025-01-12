#include "jp/ggaf/core/util/Checker.h"
#include "jp/ggaf/core/actor/Actor.h"

using namespace GgafCore;

Checker::Checker(Actor* prm_pActor, kind_t prm_kind) : Object(), ITreeNodeElem(prm_kind),
_pActor(prm_pActor),
_pNextExChecker(nullptr)
{
}
Checker* Checker::addExChecker(kind_t prm_kind) {
#ifdef MY_DEBUG
    if (_pNextExChecker != nullptr) {
        throwCriticalException("Checker::addExChecker() _pNextExChecker�����ɑ��݂��Ă܂��Bthis="<<this<<" _pActor="<<_pActor->getName());
    }
#endif
    _pNextExChecker = _pActor->createChecker(prm_kind);
}
Checker::~Checker() {
    GGAF_DELETE_NULLABLE(_pNextExChecker);
}
