#include "jp/ggaf/core/util/Checker.h"
#include "jp/ggaf/core/actor/Actor.h"

using namespace GgafCore;

Checker::Checker(Actor* prm_pActor) : Object(), ITreeNodeElem(),
_pActor(prm_pActor)
{
}

Checker::~Checker() {
}
